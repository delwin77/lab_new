#include <stdio.h>

int main(){
	int i, j, n, m;
	
	printf("Enter total number of processes:");
	scanf("%d", &n);
	printf("Enter total number of resources:");
	scanf("%d", &m);
	
	int allocMatrix[n][m], maxMatrix[n][m], available[m], need[n][m], finish[n];
	
	printf("Enter allocation matrix:\n");
	for(i=0; i<n; i++){
		for(j=0; j<m; j++){
			scanf("%d", &allocMatrix[i][j]);
		}
	}

	printf("Enter max matrix:\n");
	for(i=0; i<n; i++){
		for(j=0; j<m; j++){
			scanf("%d", &maxMatrix[i][j]);
		}
	}
	
	printf("Enter available matrix:\n");
	for(i=0; i<m; i++){
		scanf("%d", &available[i]);
	}
	
	for(i=0; i<n; i++){
		for(j=0; j<m; j++){
			need[i][j] = maxMatrix[i][j] - allocMatrix[i][j];
		}
	}

	for(i=0; i<n; i++){
		finish[i] = 0;
	}

    int safeSequence[n];
    int work[m];
    for (int i = 0; i < m ; i++){
        work[i] = available[i];
	}
    int count = 0;
    while (count < n) {
        int found = 0;
        for (int p = 0; p < n; p++) {
            if (!finish[p]) {
                int j;
                for (j = 0; j < m; j++)
                    if (need[p][j] > work[j])
                        break;
                if (j == m) {
                    for (int k = 0 ; k < m ; k++)
                        work[k] += allocMatrix[p][k];
                    safeSequence[count++] = p;
                    finish[p] = 1;
                    found = 1;
                }
            }
        }
        if (found == 0) {
            printf("Caution! System is not in safe state\n");
            return 0;
        }
    }
    
	printf("\nPrinting allocation matrix:\n");
	for(i=0; i<n; i++){
		for(j=0; j<m; j++){
			printf("%d\t", allocMatrix[i][j]);
		}
		printf("\n");
	}
	
	printf("\nPrinting Max matrix:\n");
	for(i=0; i<n; i++){
		for(j=0; j<m; j++){
			printf("%d\t", maxMatrix[i][j]);
		}
		printf("\n");
	}
	
	printf("\nPrinting Need matrix:\n");
	for(i=0; i<n; i++){
		for(j=0; j<m; j++){
			printf("%d\t", need[i][j]);
		}
		printf("\n");
	}
	
	printf("System is in safe state.\n");
	printf("<\t");
    for (int i=0; i<n; i++){
        printf("P%d\t", safeSequence[i]);
	}
	printf(">\n");
	return 0;
}
