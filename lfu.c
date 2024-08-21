#include <stdio.h>

struct frame_LFU
{
    int content;
    int frequency;
    int count;
} frame_LFU[10];

int main()
{
    int i, j, n, m, pages[50];
    printf("enter the no of pages");
    scanf("%d", &n);
    printf("enter the reference string");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &pages[i]);
    }
    printf("enter the size of frame");
    scanf("%d", &m);

    LRU(pages, n, m);
}


void LRU(int pages[],int n,int f){
    int i,j,id=0,cnt=1,min,pf=0;
    for(i=0;i<n;i++){
        frame_LFU[i].content=-1;
        frame_LFU[i].count=0;
        frame_LFU[i].frequency=0;
    }

    for(i=0;i<n;i++){
        for(j=0;j<f;j++){
            if(frame_LFU[j].content==pages[i]){
                printf("hit\t");
                frame_LFU[i].frequency++;
                break;
            }
        }
        if(j==f){
            printf("miss\t");
            if(id<f){
                frame_LFU[i].content=pages[i];
                frame_LFU[i].frequency++;
                frame_LFU[i].count=cnt++;
                id++;
            }
            else{
                min=0;
                for(j=0;j<f;j++){
                    if(frame_LFU[j].frequency<frame_LFU[min].frequency){
                        min=j;
                    }
                    else if(frame_LFU[j].frequency<frame_LFU[min].frequency && frame_LFU[min].count>frame_LFU[j].count){
                        min=j;
                    }
                }
                frame_LFU[min].content=pages[i];
                frame_LFU[min].frequency=1;
                frame_LFU[min].count=cnt++;
            }
            pf++;
        }
    }
}