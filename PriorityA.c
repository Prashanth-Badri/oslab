// Prt_value scheduling with arrivial time is 0 for each process:
#include <stdio.h>
#include <stdlib.h>

typedef struct Process
{
    int p_num;    // Process ID
    int bt;       // Burst Time
    int at;       // Arrival Time
    int wt;       // Waiting Time
    int tat;      // Turnaround Time
    int prt_value; // Prt_value
} process;

void swap(process *xp, process *yp)
{
    process temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void sort_by_prt_value(process *p, int n)
{
    // Bubble sort to sort processes by prt_value
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            // If priorities are equal, consider process number
            if (p[j].prt_value > p[j + 1].prt_value || (p[j].prt_value == p[j + 1].prt_value && p[j].p_num > p[j + 1].p_num))
                swap(&p[j], &p[j + 1]);
        }
    }
}

void prt_valueScheduling(process *p, int n)
{
    int rt[n], complete = 0, t = 0, check = 0;
    int completion_time;

    // Copy the burst time into rt[]
    for (int i = 0; i < n; i++)
        rt[i] = p[i].bt;

    // Process until all processes are completed
    while (complete != n)
    {
        int highest_prt_value = -1, index = -1;

        // Find the process with the highest prt_value among the processes that arrive till the current time
        for (int j = 0; j < n; j++)
        {
            if (p[j].at <= t && p[j].prt_value > highest_prt_value && rt[j] > 0)
            {
                highest_prt_value = p[j].prt_value;
                index = j;
                check = 1;
            }
        }

        if (check == 0)
        {
            t++;
            continue;
        }

        // Reduce remaining time by one
        rt[index]--;

        // If a process gets completely executed
        if (rt[index] == 0)
        {
            // Increment complete
            complete++;
            check = 0;

            // Find completion time of the current process
            completion_time = t + 1;

            // Calculate waiting time
            p[index].wt = completion_time - p[index].bt - p[index].at;

            // Calculating turnaround time by adding bt[i] + wt[i]
            p[index].tat = p[index].bt + p[index].wt;
        }
        // Increment time
        t++;
    }
}

void findavgTime(process *p, int n)
{
    int total_wt = 0, total_tat = 0;

    // Function to find waiting time of all processes
    prt_valueScheduling(p, n);

    // Display processes along with all details
    printf(" P\t\tAT\t\tBT\t\tPrt_value\tWT\t\tTAT\t\t\n");

    // Calculate total waiting time and total turnaround time
    for (int i = 0; i < n; i++)
    {
        total_wt = total_wt + p[i].wt;
        total_tat = total_tat + p[i].tat;
        printf(" p%d\t\t%d\t\t%d\t\t%d\t\t %d\t\t %d\n", p[i].p_num, p[i].at, p[i].bt, p[i].prt_value, p[i].wt, p[i].tat);
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
        printf("Process %d (Arrival Time Burst Time Prt_value): ", i + 1);
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].prt_value);
        p[i].p_num = i + 1;
    }

    sort_by_prt_value(p, n);

    findavgTime(p, n);

    // Free dynamically allocated memory
    free(p);

    return 0;
}
