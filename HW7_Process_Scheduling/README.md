# Process Scheduling Simulator (FCFS & SJF)

This project is a **CPU Process Scheduling Simulator** written in **C** for Linux.  
It implements and compares two classic scheduling algorithms:

- **First Come First Served (FCFS)**
- **Shortest Job First (SJF)** (Non-preemptive)

The simulator calculates and displays the following for each process:
- **Waiting Time (WT)**
- **Turnaround Time (TAT)**
- **Response Time (RT)**
- **Gantt Chart** of execution order

## Features

- Accepts user input for any number of processes.  
- Calculates individual and average time metrics.  
- Displays formatted Gantt charts for each algorithm.  
- Provides a clear comparison of algorithm performance.

## Compilation & Execution

### 1. Compile the program
```bash
gcc process_scheduling.c -o scheduler

Then run:
./scheduler

Sample Input: 
Enter the number of processes: 4
Enter the arrival time and burst time for process 1: 0 8
Enter the arrival time and burst time for process 2: 1 4
Enter the arrival time and burst time for process 3: 2 9
Enter the arrival time and burst time for process 4: 3 5

Sample Output:
=== First Come First Served (FCFS) ===
Gantt Chart: | P1 | P2 | P3 | P4 |
PID     AT     BT     WT     TAT    RT
1       0      8      0      8      0
2       1      4      7      11     7
3       2      9      10     19     10
4       3      5      18     23     18

Average Waiting Time: 8.75
Average Turnaround Time: 15.25
Average Response Time: 8.75

=== Shortest Job First (SJF) ===
Gantt Chart: | P2 | P4 | P1 | P3 |
PID     AT     BT     WT     TAT    RT
1       0      8      0      8      0
2       1      4      7      11     7
4       3      5      9      14     9
3       2      9      15     24     15

Average Waiting Time: 7.75
Average Turnaround Time: 14.25
Average Response Time: 7.75




