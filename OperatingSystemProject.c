/*. In Round Robin Scheduling, each process is assigned a fixed time slot in the CPU
scheduling queue, known as a time quantum. If a process does not complete within its assigned
time quantum, the CPU context switches to the next process in the queue. This ensures that each
process gets a fair share of the CPU time and prevents any process from monopolizing the CPU.
Suppose there are 4 processes: P1, P2, P3, and P4. The time quantum for the scheduling algorithm
is 2 units of time.
1. At time = 0, the CPU starts executing process P1.
2. After 2 units of time, the CPU context switches to process P2.
3. After 2 units of time, the CPU context switches to process P3.
4. After 2 units of time, the CPU context switches to process P4.
5. After 2 units of time, the CPU context switches back to process P1.
This cycle continues until all the processes have completed execution.
A) Design and implement the simulation program using C programming language.
B) Generate a set of "processes" with random arrival times and CPU burst times using a random
number generator.
C) Implement the Round Robin Scheduling algorithm in the simulation program.
D) Have the simulation program run for a set amount of time (e.g. 100 time units) and record the
average waiting time and response time for each process.
E) Compare the results of the simulation with the ideal scenario of a perfect scheduler.
F) Write a report of the findings and conclusion with the comparison of the results of the Round
Robin algorithm with Priority (preemptive). ( write atleast 500 words at the end of the code and
comment it).*/



#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_PROCESSES 4
#define TIME_QUANTUM 2
#define SIMULATION_TIME 100

// Define a structure to represent a process.
typedef struct Process {
    char name;          // Process name (e.g., 'P0', 'P1', ...)
    int arrival_time;   // Time at which the process arrives in the queue
    int burst_time;     // Total time required to complete the process
    int remaining_time; // Time remaining to complete the process
} Process;

int main() {
    // Initialize an array of Process structures to store information about the processes.
    Process processes[MAX_PROCESSES];
    int current_time = 0;     // Current time during the simulation
    int total_waiting_time = 0; // Total waiting time for all processes
    int total_response_time = 0; // Total response time for all processes

    // Initialize processes (you can generate these randomly)
    for (int i = 0; i < MAX_PROCESSES; i++) {
        processes[i].name = 'P' + i;
        processes[i].arrival_time = i * 3;  // Set arrival times as an example
        processes[i].burst_time = 4 + rand() % 7;  // Random burst times
        processes[i].remaining_time = processes[i].burst_time;
    }

    printf("Time\tProcess\tRemaining Time\n");

    // Main loop to simulate the execution of processes.
    while (current_time < SIMULATION_TIME) {
        bool all_processes_completed = true;

        for (int i = 0; i < MAX_PROCESSES; i++) {
            Process *p = &processes[i];

            if (p->remaining_time > 0) {
                all_processes_completed = false;

                // Determine the time slice for this process based on the time quantum.
                int time_slice = (p->remaining_time > TIME_QUANTUM) ? TIME_QUANTUM : p->remaining_time;

                // Print the current status of the process.
                printf("%d\t%c\t%d\n", current_time, p->name, p->remaining_time);

                // Update waiting time for other processes that are in the queue.
                for (int j = 0; j < MAX_PROCESSES; j++) {
                    if (j != i && processes[j].arrival_time <= current_time && processes[j].remaining_time > 0) {
                        total_waiting_time++;
                    }
                }

                // Update the current time and the remaining time for the process.
                current_time += time_slice;
                p->remaining_time -= time_slice;

                // If the process has completed, calculate response time.
                if (p->remaining_time == 0) {
                    total_response_time += current_time - p->arrival_time;
                }
            }
        }

        if (all_processes_completed) {
            break;
        }
    }

    // Calculate and print the average waiting time and average response time.
    printf("\nAverage Waiting Time: %.2f\n", (float)total_waiting_time / MAX_PROCESSES);
    printf("Average Response Time: %.2f\n", (float)total_response_time / MAX_PROCESSES);

    return 0;
}


