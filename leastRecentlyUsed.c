#include <stdio.h>

struct LRU{
    int pageContent, count;
};

void lru(int refString[], int pageSize, int frames, struct LRU lruFrame[]){
    int i, j, contain=0, pageFault=0;

    for(i=0; i<pageSize; i++){
        lruFrame[i].pageContent = -1;
        lruFrame[i].count = 0;
    }

    for(i=0; i<pageSize; i++){
        printf("\n%d\t", refString[i]);
        for(j=0; j<frames; j++){
            if(lruFrame[j].pageContent == refString[i]){
                printf("HIT");
                lruFrame[j].count++;
                break;
            }
        }
        if(j == frames){
            printf("MISS");
            if(contain < frames){
                lruFrame[contain].pageContent = refString[i];
                lruFrame[contain].count++;
                contain++;  
            }
            else{
                int min = 0;
                for(int k=0; k<frames; k++){
                    if(lruFrame[k].count < lruFrame[min].count){
                        min = k;
                    }
                }
                lruFrame[min].pageContent = refString[i];
                lruFrame[min].count++;
            }
            pageFault++;
        }
    }
    printf("\nPAGE FAULT:%d\n", pageFault);
}

int main(){
    int pageSize, frames;

    printf("Enter page size:");
    scanf("%d", &pageSize);

    int referrenceString[pageSize];
    struct LRU lruFrame[pageSize];

    printf("Enter frame size:");
    scanf("%d", &frames);

    printf("Enter referrence string:");
    for(int i=0; i<pageSize; i++){
        scanf("%d", &referrenceString[i]);
    }

    lru(referrenceString, pageSize, frames, lruFrame);
    return 0;
}