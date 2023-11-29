// Round robin scheduling with arrivial time is 0 for every process:

#include <stdio.h>
#include <stdlib.h>

// Structure for Process
typedef struct Process
{
    int p_num; // Process ID
    int bt;    // Burst Time
    int at;    // Arrival Time
    int wt;    // Waiting Time
    int tat;   // Turnaround Time
} process;

// Function to swap two processes
void swap(process *xp, process *yp)
{
    process temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// // Function to sort processes by arrival time using Bubble Sort
// void sort_by_at(process *p, int n)
// {
//     for (int i = 0; i < n - 1; i++)
//     {
//         for (int j = 0; j < n - i - 1; j++)
//         {
//             if (p[j].at > p[j + 1].at)
//                 swap(&p[j], &p[j + 1]);
//         }
//     }
// }

// Function implementing the Round Robin algorithm
void roundRobin(process *p, int n, int quantum)
{
    int rt[n], t = 0;

    // Copy burst times to remaining burst times
    for (int i = 0; i < n; i++)
        rt[i] = p[i].bt;

    while (1)
    {
        int check = 0;

        // Traverse all processes one by one repeatedly
        for (int i = 0; i < n; i++)
        {
            if (rt[i] > 0)
            {
                check = 1; // There is a pending process

                if (rt[i] > quantum)
                {
                    t += quantum;
                    rt[i] -= quantum;
                }
                else
                {
                    t = t + rt[i];
                    p[i].wt = t - p[i].bt;
                    rt[i] = 0;
                }
            }
            p[i].tat = p[i].bt + p[i].wt;
        }

        // If all processes are check
        if (check == 0)
            break;
    }
}

// Function to calculate average waiting time and average turnaround time
void findavgTime(process *p, int n, int quantum)
{
    int total_wt = 0, total_tat = 0;
    // sort_by_at(p, n);
    roundRobin(p, n, quantum);

    // Display processes along with all details
    printf(" P\t\tAT\t\tBT\t\tWT\t\tTAT\t\t\n");

    for (int i = 0; i < n; i++)
    {
        total_wt += p[i].wt;
        total_tat += p[i].tat;
        printf(" p%d\t\t%d\t\t%d\t\t %d\t\t %d\n", p[i].p_num, p[i].at, p[i].bt, p[i].wt, p[i].tat);
    }

    printf("\nAverage waiting time = %.2f", (float)total_wt / (float)n);
    printf("\nAverage turnaround time = %.2f", (float)total_tat / (float)n);
}

// Main function
int main()
{
    int n, quantum;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    process *p;
    p = (process *)malloc(sizeof(process) * n);

    for (int i = 0; i < n; i++)
    {
        printf("Process %d (Burst Time): ", i + 1);
        scanf("%d", &p[i].bt);
        p[i].p_num = i + 1;
        p[i].at = 0;
    }

    printf("Enter the time quantum for Round Robin: ");
    scanf("%d", &quantum);

    findavgTime(p, n, quantum);

    // Free dynamically allocated memory
    free(p);

    return 0;
}
