#include<stdio.h>

struct frame_LRU
{
    int content;
    int count;
}frame_LRU[50];

int LRU(int pages[],int n,int f){
    int i,j,cnt=1,id=0,pf=0;
    for (i = 0; i < n; i++)
    {
        frame_LRU[i].content=-1;
        frame_LRU[i].count=0;
    }

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < f; j++)
        {
            if(frame_LRU[j].content == pages[i]){
                printf("hit\t");
                frame_LRU[j].count=cnt++;
                break;
            }
        }
        if(j==f){
            printf("miss\t");
            if(id<f){
                frame_LRU[id].content=pages[i];
                frame_LRU[id].count=cnt++;
                id++;
            }
            else{
                int min=0;
                for(int k=0;k<f;k++){
                    if(frame_LRU[k].count < frame_LRU[min].count){
                        min=k;
                    }
                }
                frame_LRU[min].content=pages[i];
                frame_LRU[min].count=cnt++;
            }
            pf++;
        }
        for(i=0; i<f; i++){
            printf("\n%d\n", frame_LRU[i].content);
        }
    }
    printf("\n%d page faults",pf);
}



int main(){

int i,j,n,m,pages[50];
printf("enter the no of pages");
scanf("%d",&n);
printf("enter the reference string");
for ( i = 0; i < n; i++)
{
    scanf("%d",&pages[i]);
}
printf("enter the size of frame");
scanf("%d",&m);

LRU(pages,n,m);


}
