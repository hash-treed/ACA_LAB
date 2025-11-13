#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <iomanip>
#include <vector>

using namespace std;

// Simple 2-bit saturating counter
class SaturatingCounter {
public:
    SaturatingCounter() : value(2) {} // weakly taken
    void update(bool taken) {
        if (taken) {
            if (value < 3) ++value;
        } else {
            if (value > 0) --value;
        }
    }
    int get() const { return value; }
    string state() const {
        switch (value) {
            case 0: return "Strongly Not Taken";
            case 1: return "Weakly Not Taken";
            case 2: return "Weakly Taken";
            case 3: return "Strongly Taken";
            default: return "Unknown";
        }
    }
private:
    int value;
};

int main() {
    vector<int> A = {1, 2, 4, 8, 16, 32};

    for (int i = 0; i < (int)A.size(); i++) {
        string trace_file = "BHT-" + to_string(A[i]) + "x.txt";
        ifstream trace(trace_file);
        if (!trace) {
            cerr << "Could not open " << trace_file << "\n";
            continue;
        }

        string out_file = "branch_sm_states_" + to_string(A[i]) + ".txt";
        ofstream out(out_file);
        if (!out) {
            cerr << "Could not open output file " << out_file << "\n";
            return 1;
        }

        unordered_map<unsigned int, SaturatingCounter> branch_sm;
        string line;
        while (getline(trace, line)) {
            istringstream iss(line);
            unsigned long idx;
            string pc_hex, pred_str, actual_str, match_str;
            int pred, actual;
            unsigned int pc;

            iss >> idx >> pc_hex >> pred_str >> actual_str >> match_str;
            pc = stoul(pc_hex.substr(5), nullptr, 16);
            pred = stoi(pred_str.substr(5));
            actual = stoi(actual_str.substr(7));
            bool taken = actual;

            SaturatingCounter& sm = branch_sm[pc];
            sm.update(taken);

            out << "Event #" << idx << " | Branch PC=0x"
                << hex << setw(8) << setfill('0') << pc
                << " | ACTUAL=" << actual
                << " | SM state: " << sm.state()
                << " (" << sm.get() << ")\n";
        }

        out.close();
        trace.close();
    }

    return 0;
}
