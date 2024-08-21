#include <stdio.h>

void firstFit(int blockSize[], int process[], int totalProcess, int totalBlocks){
	int i, j;
	
	int newBlockSize[totalBlocks], isAllocated[totalProcess];
	for(i=0; i<totalBlocks; i++){
		newBlockSize[i] = blockSize[i];
	}
	for(i=0; i<totalProcess; i++){
		isAllocated[i] = 0;
	}
	
	printf("\nFIRST FIT\n");
	for(i=0; i<totalProcess; i++){
		for(j=0; j<totalBlocks; j++){
			if(process[i] <= newBlockSize[j]){
				printf("%dKB => %dKB\n", process[i], newBlockSize[j]);
				newBlockSize[j] -= process[i];
				isAllocated[i] = 1;
				break;
			}
		}
		if(isAllocated[i] == 0){
			printf("%dKB => CANNOT ALLOCATE\n", process[i]);
		}
	}
}

void bestFit(int blockSize[], int process[], int totalProcess, int totalBlocks){
	int i, j, temp;
	
	int newBlockSize[totalBlocks], isAllocated[totalProcess];
	for(i=0; i<totalBlocks; i++){
		newBlockSize[i] = blockSize[i];
	}
	for(i=0; i<totalProcess; i++){
		isAllocated[i] = 0;
	}
	
	for(i=0; i<totalBlocks-1; i++){
		for(j=0; j<totalBlocks-i-1; j++){
			if(newBlockSize[j] > newBlockSize[j+1]){
				temp = newBlockSize[j];
				newBlockSize[j] = newBlockSize[j+1];
				newBlockSize[j+1] = temp;
			}
	 	}
	}
	
	printf("\nBEST FIT\n");
	for(i=0; i<totalProcess; i++){
		for(j=0; j<totalBlocks; j++){
			if(process[i] <= newBlockSize[j]){
				printf("%dKB => %dKB\n", process[i], newBlockSize[j]);
				newBlockSize[j] -= process[i];
				isAllocated[i] = 1;
				break;
			}
		}
		if(isAllocated[i] == 0){
			printf("%dKB => CANNOT ALLOCATE\n", process[i]);
		}
	}
}

void worstFit(int blockSize[], int process[], int totalProcess, int totalBlocks){
	int i, j, temp;
	
	int newBlockSize[totalBlocks], isAllocated[totalProcess];
	for(i=0; i<totalBlocks; i++){
		newBlockSize[i] = blockSize[i];
	}
	for(i=0; i<totalProcess; i++){
		isAllocated[i] = 0;
	}
	
	for(i=0; i<totalBlocks-1; i++){
		for(j=0; j<totalBlocks-i-1; j++){
			if(newBlockSize[j] < newBlockSize[j+1]){
				temp = newBlockSize[j];
				newBlockSize[j] = newBlockSize[j+1];
				newBlockSize[j+1] = temp;
			}
	 	}
	}
	
	printf("\nWORST FIT\n");
	for(i=0; i<totalProcess; i++){
		for(j=0; j<totalBlocks; j++){
			if(process[i] <= newBlockSize[j]){
				printf("%dKB => %dKB\n", process[i], newBlockSize[j]);
				newBlockSize[j] -= process[i];
				isAllocated[i] = 1;
				break;
			}
		}
		if(isAllocated[i] == 0){
			printf("%dKB => CANNOT ALLOCATE\n", process[i]);
		}
	}
}

int main(){	
	int i, j, totalProcess, totalBlocks;
	
	printf("Enter total number of Processes:");
	scanf("%d", &totalProcess);
	
	printf("Enter total number of Blocks:");
	scanf("%d", &totalBlocks);
	
	int blockSize[totalBlocks], process[totalProcess], isAllocated[totalProcess];
	
	printf("Enter Block Size:\n");
	for(i=0; i<totalBlocks; i++){
		scanf("%d", &blockSize[i]);
	}
	
	printf("Enter Process Size:\n");
	for(i=0; i<totalProcess; i++){
		scanf("%d", &process[i]);
	}
	
	firstFit(blockSize, process, totalProcess, totalBlocks);
	bestFit(blockSize, process, totalProcess, totalBlocks);
	worstFit(blockSize, process, totalProcess, totalBlocks);

	return 0;
}
