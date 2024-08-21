#include <stdio.h>

int main(){
    int i, j, process, resource;

    printf("Enter total no of process:");
    scanf("%d", &process);

    printf("Enter total no of resource:");
    scanf("%d", &resource);

    int alloc[process][resource], max[process][resource], need[process][resource], finish[process], avail[resource];

    printf("Enter max matrix:");
    for(i=0; i<process; i++){
        for(j=0; j<resource; j++){
            scanf("%d", &max[i][j]);
        }
    }
    printf("Enter allocation matrix:");
    for(i=0; i<process; i++){
        for(j=0; j<resource; j++){
            scanf("%d", &alloc[i][j]);
        }
    }
    printf("Enter available matrix:");
    for(i=0; i<resource; i++){
            scanf("%d", &avail[i]);
    }

    for(i=0; i<process; i++){
        for(j=0; j<resource; j++){
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
    
    for(i=0; i<process; i++){
        finish[i] = 0;
    }

    int work[resource];
    int safeSeq[process];

    for(i=0; i<resource; i++){
        work[i] = avail[i];
    }

    int count = 0;
    while(count < process){
        int found = 0;
        for(int i=0; i<process; i++){
            if(!finish[i]){
                for(j=0; j<resource; j++){
                    if(need[i][j] > work[j]){
                        break;
                    }
                }
                if(j == resource){
                    for(int k=0; k<resource; k++){
                        work[k] += alloc[i][k];
                    }
                    safeSeq[count++] = i;
                    found = 1;
                    finish[i] = 1;
                }
            }
        }
        if(found == 0){
            printf("Not in safe state!");
        }
    }



    return 0;
}