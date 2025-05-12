#include<stdio.h>

int main(){
    int n, pagesize,pagetable[100],logical_addresss,physical_address,pagenum,framenum,offset;
    printf("enter number of pages :");
    scanf("%d",&n);
    printf("enter pagesize :");
    scanf("%d",&pagesize);
    printf("enter logical address :");
    scanf("%d",&logical_addresss);
    for(int i=0;i<n;i++){
        printf("enter %dth page frame :",i);
        scanf("%d",&pagetable[i]);
    }
    pagenum=logical_addresss/pagesize;
    if(pagenum<=n){
        framenum=pagetable[pagenum];
        offset=logical_addresss%pagesize;
        physical_address=framenum*pagesize+offset;
        printf("physical adresss is: %d",physical_address);

    }
    else{
        printf("invalid logical address");
    }
    return 0;
}