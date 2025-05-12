#include<stdio.h>
#include<stdlib.h>

int main(){
    int n, head,tracks,distance=0;
    printf("enter number of requests: ");
    scanf("%d",&n);
    printf("\n");
    int dis_req[n];
    for(int i=0;i<n;i++){
        printf("enter %dth distance request: ",i);
        scanf("%d",&dis_req[i]);
        printf("\n");
    }
    printf("enter head value: ");
    scanf("%d",&head);
    printf("\n");
    printf("enter number of tracks");
    scanf("%d",&tracks);
    printf("\n");
   int min=1000;
   int index;
int finish[n];
for(int i=0;i<n;i++){
    finish[i]=0;
}
int pending=n;
printf("\n\nSequence: %d", head);
    while(pending>0){
    for(int i=0;i<n;i++){
        int diff=abs(head-dis_req[i]);
        if(finish[i]==0&&diff<min){
            min=diff;
            index=i;
        }
       
    }
    distance = distance + abs(head - dis_req[index]);
    finish[index] = 1;
    head = dis_req[index];
    printf("-> %d", head);
    pending --;
    min=1000;
    }
    printf("\n\nTotal Distance: %d", distance);
}