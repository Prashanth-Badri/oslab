// Shortest Remaining Time First scheduling with arrivial time is different for process:
#include <stdio.h>
#include <stdlib.h>

typedef struct Process
{
    int p_num; // Process ID
    int bt;    // Burst Time
    int at;    // Arrival Time
    int wt;    // Waiting Time
    int tat;   // Turnaround Time
} process;

void swap(process *xp, process *yp)
{
    process temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void sort_by_bt(process *p, int n)
{
    // Bubble sort to sort processes by burst time
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (p[j].bt > p[j + 1].bt)
                swap(&p[j], &p[j + 1]);
        }
    }
}

void srtf(process *p, int n)
{
    int rt[n]; // remaining time

    // Copy the burst time into rt[]
    for (int i = 0; i < n; i++)
        rt[i] = p[i].bt;

    // complete is counter to track the no.of processes that have been completed.
    // t is the current time.
    // check is a flag to check if any process is eligible for execution.
    // Completion time refers to the time at which a process finishes execution.
    int complete = 0, t = 0, minm = 999999; // minimum remaining time
    int shortest = 0, completion_time;
    int check = 0;

    // Process until all processes get completed
    while (complete != n)
    {
        // Find the process with the minimum remaining time
        // among the processes that arrive till the current time
        for (int j = 0; j < n; j++)
        {
            if ((p[j].at <= t) && (rt[j] < minm) && rt[j] > 0)
            {
                minm = rt[j];
                shortest = j;
                check = 1;
            }
        }

        if (check == 0)
        {
            t++;
            continue;
        }

        // Reduce remaining time by one
        rt[shortest]--;

        // Update minimum
        minm = rt[shortest];
        if (minm == 0)
            minm = 999999;

        // If a process gets completely executed
        if (rt[shortest] == 0)
        {
            // Increment complete
            complete++;
            check = 0;

            // Find completion time of the current process
            completion_time = t + 1;

            // Calculate waiting time
            p[shortest].wt = completion_time - p[shortest].bt - p[shortest].at;

            // Calculating turnaround time by adding bt[i] + wt[i]
            p[shortest].tat = p[shortest].bt + p[shortest].wt;
        }
        // Increment time
        t++;
    }
}

void findavgTime(process *p, int n)
{
    int total_wt = 0, total_tat = 0;

    // Function to find waiting time of all processes
    srtf(p, n);

    // Display processes along with all details
    printf(" P\t\tAT\t\tBT\t\tWT\t\tTAT\t\t\n");

    // Calculate total waiting time and total turnaround time
    for (int i = 0; i < n; i++)
    {
        total_wt = total_wt + p[i].wt;
        total_tat = total_tat + p[i].tat;
        printf(" p%d\t\t%d\t\t%d\t\t %d\t\t %d\n", p[i].p_num, p[i].at, p[i].bt, p[i].wt, p[i].tat);
    }

    printf("\nAverage waiting time = %.2f", (float)total_wt / (float)n);
    printf("\nAverage turnaround time = %.2f", (float)total_tat / (float)n);
}

int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    process *p;
    p = (process *)malloc(sizeof(process) * n);

    for (int i = 0; i < n; i++)
    {
        printf("Process %d (Arrival Time Burst Time): ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].p_num = i + 1;
    }

    sort_by_bt(p, n);

    findavgTime(p, n);

    // Free dynamically allocated memory
    free(p);

    return 0;
}
