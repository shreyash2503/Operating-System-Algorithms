## Operating Systems
- This repository contains the implementation of the following operating system algorithms:
    - Banker's Algorithm
    - Disk Scheduling Algorithms -> FCFS, SSTF, SCAN, C-SCAN, LOOK, C-LOOK
    - Page Replacement Algorithms -> FIFO, LRU, Optimal
    - Process Scheduling Algorithms -> FCFS, SJF, SRTF, Priority (Both premptive and non-premptive), Round Robin
    - Reader-Writer Problem
    - Dining Philosopher's Problem
    - Producer-Consumer Problem
    - System Calls

- The code can be compiled using the following command:
    - `c++ -std=c++11 <filename>.cpp -o <filename>`
    - Some files require input from .txt files which can be provided using the following command:
        - `./<filename> < <inputfile>.txt` in the command prompt in windows
        - `./<filename> < <inputfile>.txt` in the terminal in linux
