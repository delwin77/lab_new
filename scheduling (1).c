#include <stdio.h>
#include <math.h>

struct process {
    int processID, burstTime, arrivalTime, turnAroundTime, waitingTime, priority, responseTime, remaining;
};

void timeCalculation(struct process p[], int totalProcess){
    p[0].responseTime = p[0].arrivalTime;
    for (int i=1; i<totalProcess; i++) {
        p[i].responseTime = (p[i-1].responseTime + p[i-1].burstTime) > p[i].arrivalTime ? (p[i-1].responseTime + p[i-1].burstTime) : p[i].arrivalTime;
    }

	for(int i=0; i<totalProcess; i++){
		p[i].waitingTime = p[i].responseTime - p[i].arrivalTime;
	}

    for (int i=0; i<totalProcess; i++) {
        p[i].turnAroundTime = p[i].waitingTime + p[i].burstTime;
    }
}

void displayTable(struct process p[], int totalProcess){
    printf("\nPROCESS ID\tARRIVAL TIME\tBURST TIME\tPRIORITY\tRESPONSE TIME\tWAITING TIME\tTURN AROUND TIME\n");
	for(int i=0; i<totalProcess; i++){
		printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i].processID, p[i].arrivalTime, p[i].burstTime, p[i].priority, p[i].responseTime, p[i].waitingTime, p[i].turnAroundTime);
	}
	
	float WTime=0, TTime=0;
	for(int i=0; i<totalProcess; i++){
		WTime += p[i].waitingTime;
		TTime += p[i].turnAroundTime;
	}
	
	float avgWaitingTime = WTime / totalProcess;
	float avgTurnAroundTime = TTime / totalProcess;
	printf("\nAverage Waiting Time:%.3f", avgWaitingTime);
	printf("\nAverage Turn Around Time:%.3f", avgTurnAroundTime);
}

void ganttChart(struct process p[], int totalProcess){
    printf("\n\nGANTT CHART\n");
    for(int i=0; i<totalProcess; i++){
        printf("P%d\t", p[i].processID);
    }
    printf("\n");
    for(int i=0; i<totalProcess; i++){
        printf("%d\t", p[i].responseTime);
    }
}

void fcfs(struct process p[], int totalProcess){
    int i, j;
    struct process temp, copy[totalProcess];
    
    for(int i=0; i<totalProcess; i++){
        copy[i] = p[i];
    }

    for(i=0; i<totalProcess-1; i++){
		for(j=0; j<totalProcess-i-1; j++){
			if(copy[j].arrivalTime > copy[j+1].arrivalTime){
				temp = copy[j];
				copy[j] = copy[j+1];
				copy[j+1] = temp;
			}
		}
	}

    timeCalculation(copy, totalProcess);
    displayTable(copy, totalProcess);
    ganttChart(copy, totalProcess);
}

void sjf(struct process p[], int totalProcess){
    int i;
    struct process temp, copy[totalProcess], shortJob[totalProcess];
  
    for(i=0; i<totalProcess; i++){
        copy[i] = p[i];
        copy[i].remaining = copy[i].burstTime;
    }
    int currentTime = 0, complete = 0, j = 0;

    while(complete < totalProcess){
        int shortestJob = -1;
        int shortestBurst = 99999;

        for(i=0; i<totalProcess; i++){
            if(copy[i].arrivalTime <= currentTime && copy[i].remaining < shortestBurst && copy[i].remaining > 0){
                shortestJob = i;
                shortestBurst = copy[i].remaining;
            }
        }

        if(shortestJob == -1){
            int minArrival = 99999;
            for(i=0; i<totalProcess; i++){
                if(copy[i].remaining > 0 && copy[i].arrivalTime < minArrival){
                    minArrival = copy[i].arrivalTime;
                }
            }
            currentTime = minArrival;
            continue;
        }

        currentTime += copy[shortestJob].remaining;
        copy[shortestJob].remaining = 0;
        complete++;

        shortJob[j] = copy[shortestJob];
        j++;
    }

    timeCalculation(shortJob, totalProcess);
    displayTable(shortJob, totalProcess);
    ganttChart(shortJob, totalProcess);
}

void priority(struct process p[], int totalProcess){
    int i;
    struct process temp, copy[totalProcess], maxPriority[totalProcess];
  
    for(i=0; i<totalProcess; i++){
        copy[i] = p[i];
        copy[i].remaining = copy[i].priority;
    }
    int currentTime = 0, complete = 0, j = 0;

    while(complete < totalProcess){
        int priorityJob = -1;
        int priorityOfProcesses = 99999;

        for(i=0; i<totalProcess; i++){
            if(copy[i].arrivalTime <= currentTime && copy[i].remaining < priorityOfProcesses && copy[i].remaining > -1){
                priorityJob = i;
                priorityOfProcesses = copy[i].remaining;
            }
        }

        if(priorityJob == -1){
            int minArrival = 99999;
            for(i=0; i<totalProcess; i++){
                if(copy[i].remaining > -1 && copy[i].arrivalTime < minArrival){
                    minArrival = copy[i].arrivalTime;
                }
            }
            currentTime = minArrival;
            continue;
        }

        currentTime += copy[priorityJob].burstTime;
        copy[priorityJob].remaining = -1;
        complete++;

        maxPriority[j] = copy[priorityJob];
        j++;
    }

    timeCalculation(maxPriority, totalProcess);
    displayTable(maxPriority, totalProcess);
    ganttChart(maxPriority, totalProcess);
}

/*
void roundRobin(struct process p[], int totalProcess){
    int i, j, quantumTime, slot = 0, time = 0;
    struct process temp, copy[totalProcess];
    
    printf("Enter quantum time:");
    scanf("%d", &quantumTime);

    for(int i=0; i<totalProcess; i++){
        copy[i] = p[i];
        copy[i].remaining = copy[i].burstTime;
        slot += ceil((float)copy[i].burstTime / quantumTime);
    }

    for(i=0; i<totalProcess-1; i++){
		for(j=0; j<totalProcess-i-1; j++){
			if(copy[j].arrivalTime > copy[j+1].arrivalTime){
				temp = copy[j];
				copy[j] = copy[j+1];
				copy[j+1] = temp;
			}
		}
	}

    struct process rr[slot];
    int remainingProcesses = totalProcess;
    j = 0;
    while(remainingProcesses > 0) {
        for(i = 0; i < totalProcess; i++) {
            if(copy[i].remaining > 0) {
                if(copy[i].remaining > quantumTime) {
                    rr[j] = copy[i];
                    time += quantumTime;
                    copy[i].remaining -= quantumTime;
                } else {
                    rr[j] = copy[i];
                    time += copy[i].remaining;
                    copy[i].remaining = 0;
                    remainingProcesses--;
                }
                j++;
            }
        }
    }
    timeCalculation(rr, slot);
    displayTable(rr, slot);
    ganttChart(rr, slot);

}
*/

void roundRobin(struct process p[], int totalProcess){
    int i, j, quantumTime, slot = 0, time = 0;
    struct process temp, copy[totalProcess];
    
    printf("Enter quantum time:");
    scanf("%d", &quantumTime);

    for(int i=0; i<totalProcess; i++){
        copy[i] = p[i];
        copy[i].remaining = copy[i].burstTime;
        slot += ceil((float)copy[i].burstTime / quantumTime);
    }

    for(i=0; i<totalProcess-1; i++){
		for(j=0; j<totalProcess-i-1; j++){
			if(copy[j].arrivalTime > copy[j+1].arrivalTime){
				temp = copy[j];
				copy[j] = copy[j+1];
				copy[j+1] = temp;
			}
		}
	}

    struct process rr[slot];
    int remainingProcesses = totalProcess;
    j = 0;
    while(remainingProcesses > 0) {
        for(i = 0; i < totalProcess; i++) {
            if(copy[i].remaining > 0) {
                if(copy[i].remaining > quantumTime) {
                    rr[j] = copy[i];
                    if(j == 0){
                        rr[0].responseTime = rr[0].arrivalTime;
                    }else{
                        rr[j].responseTime = time;
                    }
                    time += quantumTime;
                    copy[i].remaining -= quantumTime;
                } else {
                    rr[j] = copy[i];
                    rr[j].responseTime = time;
                    time += copy[i].remaining;
                    copy[i].remaining = 0;
                    remainingProcesses--;
                }
                j++;
            }
        }
    }
    timeCalculation(copy, totalProcess);
    displayTable(copy, totalProcess);
    
    printf("\n\nGANTT CHART\n");
    for(int i=0; i<slot; i++){
        printf("P%d\t", rr[i].processID);
    }
    printf("\n");
    for(int i=0; i<slot; i++){
        printf("%d\t", rr[i].responseTime);
    }
}

int main(){
    int totalProcess, option, flag=1;

    printf("Enter total number of process:");
    scanf("%d", &totalProcess);
    
    struct process p[totalProcess];
    for(int i=0; i<totalProcess; i++){
        p[i].processID = i + 1;
        printf("Enter Burst time:");
        scanf("%d", &p[i].burstTime);
        printf("Enter Arrival time:");
        scanf("%d", &p[i].arrivalTime);
        printf("Enter Priority:");
        scanf("%d", &p[i].priority);
        printf("\n");
    }
    while(flag){
        printf("\n\n1:FIRST COME FIRST SERVE (FCFS)\n2:SHORTEST JOB FIRST (SJF)\n3:PRIORITY\n4:ROUND ROBIN\n5:EXIT\nYou Choose:");
        scanf("%d", &option);
        switch (option){
            case 1:
                fcfs(p, totalProcess);
                break;
            case 2:
                sjf(p, totalProcess);
                break;
            case 3:
                priority(p, totalProcess);
                break;
            case 4:
                roundRobin(p, totalProcess);
                break;
            case 5:
                printf("Exiting...");
                flag = 0;
                break;
            default:
                printf("\nEnter a valid number\n");
        }
    }
    return 0;
}
