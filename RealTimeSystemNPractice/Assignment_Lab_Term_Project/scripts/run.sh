#!/bin/bash

rm -rf cmake-build-release bin
cmake -DCMAKE_BUILD_TYPE=Release -G 'CodeBlocks - Unix Makefiles' -S . -B cmake-build-release
cd cmake-build-release
make
cd -

# mps
bin/mps -n 4 -a "M RM" -s FCFS -t 5 -i tests/example3.txt -m 3 -o results/N_4^A_M-RM^S_FCFS^I-example3.txt
bin/mps -n 4 -a "M LM" -s FCFS -t 5 -i tests/example3.txt -m 3 -o results/N_4^A_M_LM^S_FCFS^I-example3.txt
bin/mps -n 4 -a "S" -s FCFS -t 5 -i tests/example3.txt -m 3 -o results/N_4^A_S^S_FCFS^I-example3.txt

bin/mps -n 4 -a "M RM" -s SJF -t 5 -i tests/example3.txt -m 3 -o results/N_4^A_M-RM^S_SJF^I-example3.txt
bin/mps -n 4 -a "M LM" -s SJF -t 5 -i tests/example3.txt -m 3 -o results/N_4^A_M_LM^S_SJF^I-example3.txt
bin/mps -n 4 -a "S" -s SJF -t 5 -i tests/example3.txt -m 3 -o results/N_4^A_S^S_SJF^I-example3.txt

bin/mps -n 4 -a "M RM" -s "RR 20" -t 5 -i tests/example3.txt -m 3 -o results/N_4^A_M-RM^S_RR-20^I-example3.txt
bin/mps -n 4 -a "M LM" -s "RR 20" -t 5 -i tests/example3.txt -m 3 -o results/N_4^A_M_LM^S_RR-20^_I-example3.txt
bin/mps -n 4 -a "S" -s "RR 20" -t 5 -i tests/example3.txt -m 3 -o results/N_4^A_S^S_RR-20^I-example3.txt

# mps_cv
bin/mps_cv -n 4 -a "M RM" -s FCFS -t 5 -i tests/example3.txt -m 3 -o results/CV_N_4^A_M-RM^S_FCFS^I-example3.txt
bin/mps_cv -n 4 -a "M LM" -s FCFS -t 5 -i tests/example3.txt -m 3 -o results/CV_N_4^A_M_LM^S_FCFS^I-example3.txt
bin/mps_cv -n 4 -a "S" -s FCFS -t 5 -i tests/example3.txt -m 3 -o results/CV_N_4^A_S^S_FCFS^I-example3.txt

bin/mps_cv -n 4 -a "M RM" -s SJF -t 5 -i tests/example3.txt -m 3 -o results/CV_N_4^A_M-RM^S_SJF^I-example3.txt
bin/mps_cv -n 4 -a "M LM" -s SJF -t 5 -i tests/example3.txt -m 3 -o results/CV_N_4^A_M_LM^S_SJF^I-example3.txt
bin/mps_cv -n 4 -a "S" -s SJF -t 5 -i tests/example3.txt -m 3 -o results/CV_N_4^A_S^S_SJF^I-example3.txt

bin/mps_cv -n 4 -a "M RM" -s "RR 20" -t 5 -i tests/example3.txt -m 3 -o results/CV_N_4^A_M-RM^S_RR-20^I-example3.txt
bin/mps_cv -n 4 -a "M LM" -s "RR 20" -t 5 -i tests/example3.txt -m 3 -o results/CV_N_4^A_M_LM^S_RR-20^_I-example3.txt
bin/mps_cv -n 4 -a "S" -s "RR 20" -t 5 -i tests/example3.txt -m 3 -o results/CV_N_4^A_S^S_RR-20^I-example3.txt