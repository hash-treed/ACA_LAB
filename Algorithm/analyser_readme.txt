# Compile
g++ -std=c++17 -o asm_analyser_agg asm_analyser_aggressive.cpp

# Run with different modes:
./asm_analyser_agg program.disas                      # Conservative (factor 2/1)
./asm_analyser_agg program.disas --aggressive         # 2× multipliers (factor 4/2)
./asm_analyser_agg program.disas --very-aggressive    # 4× multipliers (factor 8/4)
./asm_analyser_agg program.disas --max-factor 4       # Custom max (factor 4)
./asm_analyser_agg program.disas --no-cache-limit     # Ignore I-cache limits

