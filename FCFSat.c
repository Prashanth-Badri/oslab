//First Come First Serve with arivial time is different
#include <stdio.h>
#include <stdlib.h>

typedef struct Process
{
    int p_num;
    int bt;
    int at;
    int wt;
    int tat;
} Process;

void swap(Process *xp, Process *yp)
{
    Process temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void sort_by_at(Process *p, int n)
{
    // Bubble sort
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (p[j].at > p[j + 1].at)
            {
                swap(&p[j], &p[j + 1]);
            }
        }
    }
}

void fcfs(Process *p, int n)
{
    int completion_time = 0;

    for (int i = 0; i < n; i++)
    {
        if (p[i].at > completion_time)
        {
            // If the process hasn't arrived yet, wait for it to arrive
            completion_time = p[i].at;
        }

        p[i].wt = completion_time - p[i].at;
        p[i].tat = p[i].wt + p[i].bt;
        completion_time += p[i].bt;
    }
}

void findAvgTime(Process *p, int n)
{
    fcfs(p, n);

    int total_wt = 0;
    int total_tat = 0;

    for (int i = 0; i < n; i++)
    {
        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }

    printf("P\tAT\tBT\tWT\tTAT\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\n", p[i].p_num, p[i].at, p[i].bt, p[i].wt, p[i].tat);
    }

    printf("\nAverage waiting time = %.2f", (float)total_wt / (float)n);
    printf("\nAverage turnaround time = %.2f", (float)total_tat / (float)n);
}

int main()
{
    int n;
    printf("Enter the number of processes:");
    scanf("%d", &n);
    Process *p;
    p = (Process *)malloc(sizeof(Process) * n);
    for (int i = 0; i < n; i++)
    {
        printf("Process %d (Arrival Time, Burst Time):", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].p_num = i + 1;
    }

    sort_by_at(p, n);
    findAvgTime(p, n);

    free(p);
    return 0;
}
