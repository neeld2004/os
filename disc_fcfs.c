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
    for(int i=0;i<n;i++){
        distance+=abs(head-dis_req[i]);
        head=dis_req[i];
        printf("%d->",head);
    }
    printf("total distance: %d",distance);


}