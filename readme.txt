root directory contents:
files:
final_report.pdf : contains idea for optmisation through algorithm
Report_from_simulations : optimal factor analysis from simplescalar simulations
Report_algo.pdf: analyser approach and analysis of the test file in algorithm folder
readme.txt : this file 
.png images of trends extracted from simulation

folders:
simulations : contains simple scalar simulation results for hardcoded unrolling factors to support the algorithm prediction
algorithm : contains test results from the algorithm and src code

===============================================================
simulations folder contents:

assembly : assembly instructions built from the bencmark.c file
benchmarks : c files with different unroll factors
binaries : compiled benchmarks 
branch : txt files of branch simulations and behaviour file BHT after every access
branch_comps : modified bpred.c bpred.h sim-outrder.c files
cache : cache simulated files with sim out-order
obj : dis-assembled binaries 
profile : sim-profile simulated files
test : test files
=============================================================

algorithm folder contents:

analyser.cpp : source code to predict optimal factor from obj file // project
analyser : executable
analyser_readme.txt : commands to run the cpp file 
uroll.txt : not unrolled benchmark obj file // input : obj file from the first compilation
result.txt: output file


