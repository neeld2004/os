#include<stdio.h>

int main(){
    int np,nf,pos=0,fault=0,hit=0,flag;
    
    printf("enter number of pages: \n");
    scanf("%d",&np);
    printf("enter number of frames: \n");
    scanf("%d",&nf);
    int p[np],f[nf];
    printf("enter page reference string: \n");
    for(int i=0;i<np;i++){
        scanf("%d",&p[i]);
    }
    printf("page\t");
    for(int i=0;i<nf;i++){
        printf("F%d\t",i);
    }
    printf("status\t\n");

    for(int i=0;i<np;i++){
        flag=0;
        for(int j=0;j<nf;j++){
            if(p[i]==f[j]){
                hit++;
                flag=1;
                break;
            }

        }
        if(flag==0){
        fault++;
        f[pos]=p[i];
        pos++;
        if(pos==nf){
            pos=0;
        }
        }

    printf("%d\t",p[i]);

    for(int i=0;i<nf;i++){
        printf("%d\t",f[i]);
    }

    if(flag==0){
        printf("miss\t\n");
    }
    else{
        printf("hit\t\n");
    }
    }
    printf("\nTotal Page Faults: %d\n", fault);
    printf("Total Page Hits: %d\n", hit);
    printf("Hit Ratio: %.2f\n", (float)hit / np);
    printf("Miss Ratio: %.2f\n", (float)fault / np);
    return 0;
}