#include <stdio.h>
int main(){
    int num_processes, num_resources;

    printf("Number of Process: ");
    scanf("%d", &num_processes);

    printf("Number of Resources: ");
    scanf("%d", &num_resources);

    int available[num_resources];
    int max[num_processes][num_resources];
    int allocation[num_processes][num_resources];
    int need[num_processes][num_resources];
    int work[num_resources];
    int finish[num_processes];

    printf("Enter Available Resources: \n");
    for(int i=0; i<num_resources; i++){
        scanf("%d", &available[i]);
    }

    printf("Enter Max Resources of each process: \n");
    for(int i=0; i<num_processes; i++){
        for(int j=0; j<num_resources; j++){
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter Allocatied Resource of each process: \n");
    for(int i=0; i<num_processes; i++){
        for(int j=0; j<num_resources; j++){
            scanf("%d", &allocation[i][j]);

            need[i][j] = max[i][j] - allocation[i][j];
        }
        finish[i] = 0;
    }

    for(int i=0; i< num_resources; i++){
        work[i] = available[i];
    }

    int safe_sequence[num_processes];
    int count=0;

    
    while(count < num_processes){
        int found=0;
        for(int i=0; i<num_processes; i++){
            if(finish[i]==0){
                int j;
                for(j=0;j<num_resources;j++){
                    if(need[i][j]>work[j]){
                        break;
                    }
                }

                if(j == num_resources){
                    for(int k=0; k<num_resources; k++){
                        work[k]+=allocation[i][k];
                    }

                    safe_sequence[count] = i;
                    count++;

                    finish[i]=1;
                    found=1;
                }
            }
        }
        if(!found){
            printf("System is not in safe sequence\n");
            break;
        }
    }

    if(count == num_processes){
        printf("System is in safe state\n");
        for(int i=0; i<num_processes; i++){
            printf("p%d->",safe_sequence[i]);
        }
        printf("\n");
    }

    return 0;
}
