#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Process {
	int pid;
	int arrivalTime;
	int burstTime;
	int turnaroundTime;
	int waitingTime;
	int responseTime;
	int completed;
};


void fcfs(struct Process p[], int n);
void sjf(struct Process p[], int n);
void bubbleSortByArrival(struct Process p[], int n);
void print(struct Process p[], int n, const char* algorithm, int order[], int orderLen);


int
main()
{
	int n;
	printf("Enter the number of processes: ");
    scanf("%d", &n);

	struct Process p[n];

    for (int i = 0; i < n; ++i) {
        p[i].pid = i + 1;
        printf("Enter the arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &p[i].arrivalTime, &p[i].burstTime);
        p[i].completed = 0;
    }

    fcfs(p, n);
    sjf(p, n);

    return 0;
}

void
bubbleSortByArrival(struct Process p[], int n)
{
	struct Process temp;
	bool swapped;
	for (int i = 0; i < n - 1; ++i) {
		swapped = false;
		for (int j = 0; j < n - i - 1; ++j) {
			if (p[j].arrivalTime > p[j + 1].arrivalTime) {
				temp = p[j];
				p[j] = p[j + 1];
				p[j + 1] = temp;
				swapped = true;
			}
			if (!swapped) break;
		}
	}
}

void
fcfs(struct Process p[], int n)
{
	struct Process proc[n];
	for(int i = 0; i < n; ++i) proc[i] = p[i];
	bubbleSortByArrival(proc, n);

	int currentTime = 0;
	int order[n];
	double totalWT = 0, totalTAT = 0, totalRT = 0;

	for (int i = 0; i < n; ++i) {
		if (currentTime < proc[i].arrivalTime)
			currentTime = proc[i].arrivalTime;

		proc[i].responseTime = currentTime - proc[i].arrivalTime;
		proc[i].waitingTime = currentTime - proc[i].arrivalTime;
		currentTime += proc[i].burstTime;
		proc[i].turnaroundTime = currentTime - proc[i].arrivalTime;

		totalWT += proc[i].waitingTime;
		totalRT += proc[i].responseTime;
		totalTAT += proc[i].turnaroundTime;
		order[i] = proc[i].pid;
	}

	print(proc, n, "First Come First Served (FCFS)", order, n);
	printf("\nAverage Waiting Time: %.2f", totalWT / n);
    printf("\nAverage Turnaround Time: %.2f", totalTAT / n);
    printf("\nAverage Response Time: %.2f\n\n", totalRT / n);
}

void
sjf(struct Process p[], int n)
{
	struct Process proc[n];
    for (int i = 0; i < n; ++i) {
        proc[i] = p[i];
        proc[i].completed = 0;
    }

	int completed = 0, currentTime = 0;
	int order[n], orderLen = 0;
	double totalWT = 0, totalTAT = 0, totalRT = 0;


	while (completed < n) {
		int index = -1;
		int minBT = 1e9;

		for (int i = 0; i < n; ++i) {
			if (!proc[i].completed && proc[i].arrivalTime <= currentTime) {
				if (proc[i].burstTime < minBT || (proc[i].burstTime == minBT || proc[i].arrivalTime < proc[index].arrivalTime)) {
					index = i;
					minBT = proc[i].burstTime;
				}
			}
		}
		if (index == -1) {
			++currentTime;
			continue;
		}

		proc[index].responseTime = currentTime - proc[index].arrivalTime;
		proc[index].waitingTime = currentTime - proc[index].arrivalTime;
		currentTime += proc[index].burstTime;
		proc[index].turnaroundTime = currentTime - proc[index].arrivalTime;
		proc[index].completed = 1;
		order[orderLen++] = proc[index].pid;

		totalWT += proc[index].waitingTime;
		totalTAT +=  proc[index].turnaroundTime;
		totalRT += proc[index].responseTime;
		++completed;
	}

	print(proc, n, "Shortest Job First (SJF)", order, orderLen);
	printf("\nAverage Waiting Time: %.2f", totalWT / n);
    printf("\nAverage Turnaround Time: %.2f", totalTAT / n);
    printf("\nAverage Response Time: %.2f\n\n", totalRT / n);

}

void
print(struct Process p[], int n, const char* algorithm, int order[], int orderLen)
{
	printf("\n=== %s ===\n", algorithm);
    printf("Gantt Chart: ");

    for (int i = 0; i < orderLen; i++)
        printf("| P%d ", order[i]);
    printf("|\n");

    printf("PID\tAT\tBT\tWT\tTAT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].arrivalTime, p[i].burstTime, p[i].waitingTime, p[i].turnaroundTime, p[i].responseTime);
	}
}


