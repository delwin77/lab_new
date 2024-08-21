#include <stdio.h>
#include <stdlib.h>

void sort(int reqDisk[], int frames){
    for(int i=0; i<frames-1; i++){
        for(int j=0; j<frames-i-1; j++){
            if(reqDisk[j] > reqDisk[j+1]){
                int temp = reqDisk[j];
                reqDisk[j] = reqDisk[j+1];
                reqDisk[j+1] = temp;
            }
        }
    }
}

int main(){
    int i, j, frames, diskSize, startingHead, direction, leftDiskSize=0, rightDiskSize=0, sum=0, distance;

    printf("Enter the no of frames:");
    scanf("%d", &frames);

    int reqDisk[frames], leftDisk[frames], rightDisk[frames];

    printf("Enter total size of the disk:");
    scanf("%d", &diskSize);

    printf("Enter the requested disk:\n");
    for(i=0; i<frames; i++){
        scanf("%d", &reqDisk[i]);
    }

    printf("Enter the current head:");
    scanf("%d", &startingHead);

    int currentDisk = startingHead;

    sort(reqDisk, frames);

    printf("Enter the direction\n1:Right\n2:Left");
    scanf("%d", &direction);

    for(i=0; i<frames; i++){
        if(reqDisk[i] < startingHead){
            leftDisk[leftDiskSize++] = reqDisk[i];
        }else{
            rightDisk[rightDiskSize++] = reqDisk[i];
        }
    }

    printf("%d=>", startingHead);

    if(direction == 1){
        for(i=0; i<rightDiskSize; i++){
            distance = abs(currentDisk - rightDisk[i]);
            sum += distance;
            currentDisk = rightDisk[i];
            printf("%d=>", currentDisk);
        }
        if(leftDiskSize > 0){
            distance = abs(currentDisk - diskSize);
            sum += distance;
            currentDisk = diskSize;
            printf("%d=>", currentDisk);
            
            for(i=leftDiskSize-1; i>=0; i--){
                distance = abs(currentDisk - leftDisk[i]);
                sum += distance;
                currentDisk = leftDisk[i];
                printf("%d=>", currentDisk);
            }
        }
    }else if(direction == 2){
        for(i=leftDiskSize-1; i>=0; i--){
            distance = abs(currentDisk - leftDisk[i]);
            sum += distance;
            currentDisk = leftDisk[i];
            printf("%d=>", currentDisk);
        }

        if(rightDiskSize > 0){
            distance = abs(currentDisk - 0);
            sum += distance;
            currentDisk = 0;
            printf("%d=>", currentDisk);

            for(i=0; i<rightDiskSize; i++){
                distance = abs(currentDisk - rightDisk[i]);
                sum += distance;
                currentDisk = rightDisk[i];
                printf("%d=>", currentDisk);
            }
        }


    }else{
        printf("INVALID INPUT");
    }
    
    printf("\nSum=>%d\n", sum);
    
    return 0;
}