// Shortest JOb First scheduling with arrivial time is different for each process:
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

void sort_bt_at(process *p, int n)
{
    // Sort processes by arrival time and burst time
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (p[j].at > p[j + 1].at || (p[j].at == p[j + 1].at && p[j].bt > p[j + 1].bt))
            {
                swap(&p[j], &p[j + 1]);
            }
        }
    }
}

void sjf(process *p, int n)
{

    int completion_time = 0;

    for (int i = 0; i < n; i++)
    {
        p[i].wt = completion_time - p[i].at;
        p[i].tat = p[i].wt + p[i].bt;
        completion_time += p[i].bt;
    }
}

void findavgTime(process *p, int n)
{
    int total_wt = 0, total_tat = 0;

    sjf(p, n);

    printf(" P\t\tAT\t\tBT\t\tWT\t\tTAT\n");

    for (int i = 0; i < n; i++)
    {
        total_wt += p[i].wt;
        total_tat += p[i].tat;
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
        printf("Process %d (Arrival Time, Burst Time): ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].p_num = i + 1;
    }
    sort_bt_at(p, n); // Sort processes by burst time and arrival time
    findavgTime(p, n);

    free(p); // Free dynamically allocated memory

    return 0;
}
