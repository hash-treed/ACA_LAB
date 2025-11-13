#include <bits/stdc++.h>
using namespace std;

// Configuration for aggressive unrolling
struct UnrollConfig {
    bool aggressive_mode = false;
    int max_unroll_factor = 8;  
    int aggressive_max_factor = 16;  
    float register_pressure_multiplier = 1.0f;  
    float memory_bandwidth_multiplier = 1.0f; 
    float cache_multiplier = 1.0f;  
        bool ignore_register_pressure = false;  
    bool ignore_memory_bandwidth = false; 
    bool ignore_cache_limits = false; 
};

struct Instruction {
    uint32_t address;
    string mnemonic;
    int rs, rt, rd, imm;
    uint32_t target;
    bool is_branch;
    bool is_memory_op;
    bool is_arith;
    string raw_text;
};

struct LoopInfo {
    uint32_t loop_start;
    uint32_t loop_end;
    uint32_t branch_target;
    vector<Instruction> instructions;
    int live_registers;
    int memory_accesses;
    int load_count;
    int store_count;
    int arith_instr_count;
    int branch_instr_count;
};

class DisassemblyAnalyzer {
private:
    vector<string> disassembly_lines;
    map<uint32_t, Instruction> instructions;
    map<uint32_t, string> address_to_function;
    uint32_t main_start = 0;
    uint32_t main_end = 0;
    UnrollConfig config;

public:
    DisassemblyAnalyzer(const UnrollConfig& cfg = UnrollConfig()) : config(cfg) {}

    void set_config(const UnrollConfig& cfg) {
        config = cfg;
    }

    bool load_disassembly(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error: Cannot open file " << filename << endl;
            return false;
        }

        string line;
        while (getline(file, line)) {
            disassembly_lines.push_back(line);
        }

        return !disassembly_lines.empty();
    }

    bool parse_disassembly() {
        regex instr_regex(R"(^\s+([0-9a-f]+):\s+([0-9a-f\s]+)\t([a-z]+)\s*(.*))");
        regex func_regex(R"(^([0-9a-f]+)\s+<(.+)>:)");

        for (const auto& line : disassembly_lines) {
            smatch match;
            if (regex_match(line, match, func_regex)) {
                uint32_t addr = stoul(match[1].str(), nullptr, 16);
                string func_name = match[2].str();
                address_to_function[addr] = func_name;
                if (func_name == "main") {
                    main_start = addr;
                }
                continue;
            }

            if (regex_match(line, match, instr_regex)) {
                uint32_t addr = stoul(match[1].str(), nullptr, 16);
                string mnemonic = match[3].str();
                string operands = match[4].str();
                Instruction inst = decode_instruction(addr, mnemonic, operands, line);
                instructions[addr] = inst;
            }
        }

        auto main_it = address_to_function.find(main_start);
        if (main_it != address_to_function.end()) {
            auto next_it = next(main_it);
            if (next_it != address_to_function.end()) {
                main_end = next_it->first;
            } else {
                main_end = instructions.rbegin()->first;
            }
        }

        return true;
    }

    Instruction decode_instruction(uint32_t addr, const string& mnemonic,
                                   const string& operands, const string& raw) {
        Instruction inst;
        inst.address = addr;
        inst.mnemonic = mnemonic;
        inst.rs = inst.rt = inst.rd = inst.imm = 0;
        inst.target = 0;
        inst.is_branch = false;
        inst.is_memory_op = false;
        inst.is_arith = false;
        inst.raw_text = raw;

        parse_operands(operands, inst);

        if (mnemonic == "add" || mnemonic == "addu" || mnemonic == "sub" ||
            mnemonic == "subu" || mnemonic == "and" || mnemonic == "or" ||
            mnemonic == "xor" || mnemonic == "slt" || mnemonic == "sltu" ||
            mnemonic == "mul" || mnemonic == "mult" || mnemonic == "div" ||
            mnemonic == "addi" || mnemonic == "addiu" || mnemonic == "andi" ||
            mnemonic == "ori" || mnemonic == "xori" || mnemonic == "slti" ||
            mnemonic == "sltiu" || mnemonic == "sll" || mnemonic == "srl" ||
            mnemonic == "sra") {
            inst.is_arith = true;
        } else if (mnemonic == "lw" || mnemonic == "lb" || mnemonic == "lh" ||
                   mnemonic == "lu" || mnemonic == "sw" || mnemonic == "sb" ||
                   mnemonic == "sh" || mnemonic == "lwc1" || mnemonic == "swc1") {
            inst.is_memory_op = true;
        } else if (mnemonic == "beq" || mnemonic == "bne" || mnemonic == "blez" ||
                   mnemonic == "bgez" || mnemonic == "bltz" || mnemonic == "bgtz" ||
                   mnemonic == "j" || mnemonic == "jal" || mnemonic == "jr" ||
                   mnemonic == "jalr") {
            inst.is_branch = true;
        }

        return inst;
    }

    void parse_operands(const string& operands, Instruction& inst) {
        regex reg_regex(R"(\$(\d+)|r(\d+))");
        sregex_iterator iter(operands.begin(), operands.end(), reg_regex);
        sregex_iterator end;
        vector<int> regs;

        for (; iter != end; ++iter) {
            int reg_num = -1;
            if (iter->size() > 1 && iter->str(1).length() > 0) {
                reg_num = stoi(iter->str(1));
            } else if (iter->size() > 2 && iter->str(2).length() > 0) {
                reg_num = stoi(iter->str(2));
            }

            if (reg_num >= 0) {
                regs.push_back(reg_num);
            }
        }

        if (regs.size() >= 1) inst.rs = regs[0];
        if (regs.size() >= 2) inst.rt = regs[1];
        if (regs.size() >= 3) inst.rd = regs[2];

        regex imm_regex(R"((-?\d+)\(|(-?\d+)\s*$)");
        sregex_iterator imm_iter(operands.begin(), operands.end(), imm_regex);
        if (imm_iter != end) {
            inst.imm = stoi(imm_iter->str(1).length() > 0 ? imm_iter->str(1) : imm_iter->str(2));
        }

        regex target_regex(R"(([0-9a-f]+)\s+<)");
        sregex_iterator target_iter(operands.begin(), operands.end(), target_regex);
        if (target_iter != end) {
            try {
                inst.target = stoul(target_iter->str(1), nullptr, 16);
            } catch (...) {
                inst.target = 0;
            }
        }
    }

    vector<LoopInfo> detect_loops() {
        vector<LoopInfo> loops;

        if (main_start == 0) {
            cerr << "Error: main function not found" << endl;
            return loops;
        }

        for (auto& [addr, inst] : instructions) {
            if (addr < main_start || addr >= main_end) continue;
            if (inst.is_branch && inst.target != 0 && inst.target < addr && inst.target >= main_start) {
                LoopInfo loop;
                loop.loop_start = inst.target;
                loop.loop_end = addr;
                loop.branch_target = inst.target;

                for (auto& [loop_addr, loop_inst] : instructions) {
                    if (loop_addr >= loop.loop_start && loop_addr <= loop.loop_end) {
                        loop.instructions.push_back(loop_inst);
                    }
                }

                if (!loop.instructions.empty()) {
                    sort(loop.instructions.begin(), loop.instructions.end(),
                         [](const Instruction& a, const Instruction& b) {
                             return a.address < b.address;
                         });
                    analyze_loop_characteristics(loop);
                    loops.push_back(loop);
                }
            }
        }

        return loops;
    }

    void analyze_loop_characteristics(LoopInfo& loop) {
        loop.live_registers = 0;
        loop.memory_accesses = 0;
        loop.load_count = 0;
        loop.store_count = 0;
        loop.arith_instr_count = 0;
        loop.branch_instr_count = 0;

        map<int, bool> live_regs;

        for (const auto& inst : loop.instructions) {
            if (inst.is_memory_op) {
                loop.memory_accesses++;
                if (inst.mnemonic == "lw" || inst.mnemonic == "lb" ||
                    inst.mnemonic == "lh" || inst.mnemonic == "lwc1") {
                    loop.load_count++;
                } else if (inst.mnemonic == "sw" || inst.mnemonic == "sb" ||
                           inst.mnemonic == "sh" || inst.mnemonic == "swc1") {
                    loop.store_count++;
                }
            }

            if (inst.is_arith) {
                loop.arith_instr_count++;
            }

            if (inst.is_branch) {
                loop.branch_instr_count++;
            }

            if (inst.rs != 0) live_regs[inst.rs] = true;
            if (inst.rt != 0) live_regs[inst.rt] = true;
            if (inst.rd != 0) live_regs[inst.rd] = true;
        }

        loop.live_registers = live_regs.size();
    }

    int estimate_optimal_unroll_factor(const LoopInfo& loop) {
        int loop_size = loop.instructions.size();
        if (loop_size == 0) return 1;

        int max_unroll_by_regs = INT_MAX;
        int max_unroll_by_memory = INT_MAX;
        int max_unroll_by_size = INT_MAX;
        int max_unroll_by_intensity = INT_MAX;

        // Register pressure constraint
        if (!config.ignore_register_pressure) {
            max_unroll_by_regs = (int)(32 / max(1, loop.live_registers) * config.register_pressure_multiplier);
        }

        // Memory bandwidth constraint
        if (!config.ignore_memory_bandwidth) {
            int memory_weight = (loop.load_count + loop.store_count) * 2;
            max_unroll_by_memory = (int)(max(1, 16 / max(1, memory_weight)) * config.memory_bandwidth_multiplier);
        }

        // Instruction cache constraint
        if (!config.ignore_cache_limits) {
            max_unroll_by_size = (int)(max(1, 16 / loop_size) * config.cache_multiplier);
        }

        // Arithmetic intensity constraint
        float arith_intensity = (float)(loop.arith_instr_count) / max(1, loop.memory_accesses + 1);
        max_unroll_by_intensity = (arith_intensity > 0.5f) ? 8 : 4;

        // Find minimum constraint (bottleneck)
        int optimal = min({max_unroll_by_regs, max_unroll_by_memory,
                           max_unroll_by_size, max_unroll_by_intensity,
                           config.aggressive_mode ? config.aggressive_max_factor : config.max_unroll_factor});

        // Round down to nearest power of 2
        int unroll_factor = 1;
        while (unroll_factor * 2 <= optimal) {
            unroll_factor *= 2;
        }

        return max(1, unroll_factor);
    }

    void print_results(const vector<LoopInfo>& loops) {
        if (loops.empty()) {
            cout << "No loops detected in main function" << endl;
            return;
        }

        cout << "\n=== LOOP ANALYSIS REPORT ===" << endl;
        cout << "Main function: 0x" << hex << main_start << " - 0x" << main_end << dec << endl;
        cout << "Total loops found: " << loops.size() << endl;
        
        if (config.aggressive_mode) {
            cout << "[AGGRESSIVE MODE ENABLED]" << endl;
            cout << "Register Multiplier: " << config.register_pressure_multiplier << endl;
            cout << "Memory Multiplier: " << config.memory_bandwidth_multiplier << endl;
            cout << "Cache Multiplier: " << config.cache_multiplier << endl;
            cout << "Max Factor: " << config.aggressive_max_factor << endl << endl;
        }

        for (size_t i = 0; i < loops.size(); i++) {
            const LoopInfo& loop = loops[i];

            cout << "\nLoop #" << (i + 1) << ":" << endl;
            cout << "  Address Range: 0x" << hex << loop.loop_start << " - 0x"
                 << loop.loop_end << dec << endl;
            cout << "  Loop Size: " << loop.instructions.size() << " instructions" << endl;
            cout << "  Live Registers: " << loop.live_registers << endl;
            cout << "  Memory Accesses: " << loop.memory_accesses << endl;
            cout << "    - Loads: " << loop.load_count << endl;
            cout << "    - Stores: " << loop.store_count << endl;
            cout << "  Arithmetic Instructions: " << loop.arith_instr_count << endl;
            cout << "  Branch Instructions: " << loop.branch_instr_count << endl;

            float arith_intensity = (float)loop.arith_instr_count / max(1, loop.memory_accesses + 1);
            cout << "  Arithmetic Intensity: " << fixed << setprecision(2) << arith_intensity << endl;

            int optimal_unroll = estimate_optimal_unroll_factor(loop);

            cout << "  === OPTIMAL UNROLL FACTOR: " << optimal_unroll << " ===" << endl;

            cout << "\n  Constraint Analysis:" << endl;

            int reg_constraint = INT_MAX;
            if (!config.ignore_register_pressure) {
                reg_constraint = (int)(32 / max(1, loop.live_registers) * config.register_pressure_multiplier);
                cout << "  Register Pressure Limit: " << reg_constraint;
                if (config.aggressive_mode) cout << " (aggressive: ×" << config.register_pressure_multiplier << ")";
                cout << endl;
            } else {
                cout << "  Register Pressure Limit: IGNORED" << endl;
            }

            int mem_weight = (loop.load_count + loop.store_count) * 2;
            int mem_constraint = INT_MAX;
            if (!config.ignore_memory_bandwidth) {
                mem_constraint = (int)(max(1, 16 / max(1, mem_weight)) * config.memory_bandwidth_multiplier);
                cout << "  Memory Bandwidth Limit: " << mem_constraint;
                if (config.aggressive_mode) cout << " (aggressive: ×" << config.memory_bandwidth_multiplier << ")";
                cout << endl;
            } else {
                cout << "  Memory Bandwidth Limit: IGNORED" << endl;
            }

            int cache_constraint = INT_MAX;
            if (!config.ignore_cache_limits) {
                cache_constraint = (int)(max(1, 16 / (int)loop.instructions.size()) * config.cache_multiplier);
                cout << "  Instruction Cache Limit: " << cache_constraint;
                if (config.aggressive_mode) cout << " (aggressive: ×" << config.cache_multiplier << ")";
                cout << endl;
            } else {
                cout << "  Instruction Cache Limit: IGNORED" << endl;
            }

            int intensity_constraint = (arith_intensity > 0.5f) ? 8 : 4;
            cout << "  Arithmetic Intensity Limit: " << intensity_constraint << endl;
            cout << "  Final (min of active constraints): " << optimal_unroll << endl;

            cout << "\n  Instructions in Loop:" << endl;
            for (const auto& inst : loop.instructions) {
                cout << "    0x" << hex << inst.address << dec << ": " << inst.mnemonic;
                if (inst.is_memory_op) cout << " (MEMORY)";
                if (inst.is_arith) cout << " (ARITHMETIC)";
                if (inst.is_branch) cout << " (BRANCH)";
                cout << endl;
            }
        }

        cout << endl;
    }
};

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <disassembly_file> [options]" << endl;
        cerr << "\nOptions:" << endl;
        cerr << "  --aggressive           Enable aggressive unrolling (×2 multipliers)" << endl;
        cerr << "  --very-aggressive      Enable very aggressive unrolling (×4 multipliers)" << endl;
        cerr << "  --max-factor <N>       Set maximum unroll factor (default: 8)" << endl;
        cerr << "  --no-register-limit    Ignore register pressure constraints" << endl;
        cerr << "  --no-memory-limit      Ignore memory bandwidth constraints" << endl;
        cerr << "  --no-cache-limit       Ignore instruction cache constraints" << endl;
        cerr << "\nExample:" << endl;
        cerr << "  objdump -d program.o > program.disas" << endl;
        cerr << "  " << argv[0] << " program.disas --aggressive" << endl;
        return 1;
    }

    UnrollConfig config;

    // Parse command-line options
    for (int i = 2; i < argc; i++) {
        string arg = argv[i];
        if (arg == "--aggressive") {
            config.aggressive_mode = true;
            config.aggressive_max_factor = 16;
            config.register_pressure_multiplier = 2.0f;
            config.memory_bandwidth_multiplier = 2.0f;
            config.cache_multiplier = 2.0f;
        } else if (arg == "--very-aggressive") {
            config.aggressive_mode = true;
            config.aggressive_max_factor = 32;
            config.register_pressure_multiplier = 4.0f;
            config.memory_bandwidth_multiplier = 4.0f;
            config.cache_multiplier = 4.0f;
        } else if (arg == "--max-factor" && i + 1 < argc) {
            config.aggressive_max_factor = stoi(argv[++i]);
            config.aggressive_mode = true;
        } else if (arg == "--no-register-limit") {
            config.ignore_register_pressure = true;
        } else if (arg == "--no-memory-limit") {
            config.ignore_memory_bandwidth = true;
        } else if (arg == "--no-cache-limit") {
            config.ignore_cache_limits = true;
        }
    }

    DisassemblyAnalyzer analyzer(config);

    if (!analyzer.load_disassembly(argv[1])) {
        return 1;
    }

    if (!analyzer.parse_disassembly()) {
        cerr << "Error: Failed to parse disassembly" << endl;
        return 1;
    }

    vector<LoopInfo> loops = analyzer.detect_loops();
    analyzer.print_results(loops);

    return 0;
}
