 #include <stdio.h>
int main() { 
int num_processes, num_resources; 
printf("Enter the number of processes: "); 
scanf("%d", &num_processes); 
printf("Enter the number of resources: "); 
scanf("%d", &num_resources); 

int available[num_resources]; 
int max[num_processes][num_resources]; 
int allocation[num_processes][num_resources]; 
int need[num_processes][num_resources]; 
int work[num_resources]; 
int finish[num_processes]; 
printf("Enter the available resources: "); 
for (int i = 0; i < num_resources; i++) { 
scanf("%d", &available[i]); 
 } 
printf("Enter the maximum resources for each process:\n"); 
for (int i = 0; i < num_processes; i++) { 
for (int j = 0; j < num_resources; j++) { 
scanf("%d", &max[i][j]); 
 } 
 } 
printf("Enter the allocated resources for each process:\n"); 
for (int i = 0; i < num_processes; i++) { 
for (int j = 0; j < num_resources; j++) { 
scanf("%d", &allocation[i][j]); 
need[i][j] = max[i][j] - allocation[i][j]; 
 } 
finish[i] = 0; 
 } 
// Initialize the work vector to be the available vector
for (int i = 0; i < num_resources; i++) { 
work[i] = available[i]; 
 } 
int safe_sequence[num_processes]; 
int count = 0;
 
printf("allocatoed resources for each process:\n"); 
for (int i = 0; i < num_processes; i++) { 
for (int j = 0; j < num_resources; j++) { 
printf("%d " , allocation[i][j]); 
 } 
printf("\n") ;
 } 
printf("the Need resources for each process:\n"); 
for (int i = 0; i < num_processes; i++) { 
for (int j = 0; j < num_resources; j++) { 
printf("%d " , need[i][j]); 
 } 
printf("\n") ;
 } 

printf("the maximum resources for each process:\n"); 
for (int i = 0; i < num_processes; i++) { 
for (int j = 0; j < num_resources; j++) { 
printf("%d ",  max[i][j]); 
 } 
printf("\n") ;
 } 

for (int i = 0; i < num_processes; i++) { 
//for (int j = 0; j < num_resources; j++) { 
printf("%d ",  available[i]); 
  
 }
printf("\n") ;

return 0; 
}
