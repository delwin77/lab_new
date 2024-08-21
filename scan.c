
#include<stdio.h>
#include<stdlib.h>

int frames[20];

int sort(int frames[],int n){
    int i,j,temp;
    for ( i = 0; i < n-1; i++)
    {
        for ( j = 0; j < n-1-i; j++)
        {
            if(frames[j]>frames[j+1]){
                temp=frames[j+1];
                frames[j+1]=frames[j];
                frames[j]=temp;
            }
        }
        
    }
    for (int i = 0; i < n; i++)
    {
            printf("sorted array:%d",frames[i]);

    }
        
}


int main(){
    int n,direction,disk,dr,i,j,lc=0,rc=0,h,cr,left[10],right[10],distance,sum=0;
    printf("enter the no of frames:");
    scanf("%d",&n);
    printf("enter disk size:");
    scanf("%d",&disk);
    printf("requested frames:");
    for (int i = 0; i < n; i++)
    {
        scanf("%d",&frames[i]);
    }
    printf("enter the current head");
    scanf("%d",&h);
    cr=h;

    sort(frames,n);

    printf("enter the direction:\n1.right (1)\n2.left(0)");
    scanf("%d",&direction);

    for ( i = 0; i < n; i++)
    {
        if(frames[i] < h){
            left[lc++]=frames[i];
        }
        else{
            right[rc++]=frames[i];
        }
    }


    printf("%d=>",h);
    if(direction == 1){
        for ( i = 0; i < rc; i++)
        {
            distance = abs(cr-right[i]);
            sum+=distance;
            cr=right[i];
            printf("%d=>",cr);
        }

        if(lc>0){
            distance = abs(cr-disk);
            sum+=distance;
            cr=disk;
            printf("%d=>",cr);

            for ( i = lc-1; i >=0 ; i--)
            {
            distance = abs(cr-left[i]);
            sum+=distance;
            cr=left[i];
            printf("%d=>",cr);
            }
            
        }
        
    }

    else{
        for ( i = lc-1; i >=0 ; i--)
            {
            distance = abs(cr-left[i]);
            sum+=distance;
            cr=left[i];
            printf("%d=>",cr);
            }
        if(rc>0){
            distance = abs(cr-0);
            sum+=distance;
            cr=0;
            printf("%d=>",cr);

        for ( i = 0; i < rc; i++)
            {
                distance = abs(cr-right[i]);
                sum+=distance;
                cr=right[i];
                printf("%d=>",cr);
            }
        }
    }
    printf("sum is %d",sum);

}
