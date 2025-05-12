#include<stdio.h>
#include <stdlib.h>
int smallest=1000;
int main(){
    int np, nb;
    printf("enter number of process: ");
    scanf("%d",&np);
    printf("enter number of blocks: ");
    scanf("%d",&nb);
    int b[nb],p[np];
    printf("enter size of each process: ");
    for(int i=0;i<np;i++){
        scanf("%d",&p[i]);

    }
    printf("enter size of each block: ");
    for(int i=0;i<nb;i++){
        scanf("%d",&b[i]);
        
    }
    int bf[4]={0,0,0,0},frag[np],bn[np],i,j;

    for( i=0;i<np;i++){
        for( j=0;j<nb;j++){
            if(bf[j]==0&&b[j]>=p[i]){
                if(b[j]<smallest){
                    smallest=b[j];
                    bn[i]=j;
                }
            }
        }
        
        bf[bn[i]]=1;
        frag[i]=smallest-p[i];
        smallest=1000;
    }
    printf("Process no.\tprocess size\tblock number\tblock size\tfragment size\n");
    for(int i = 0; i < np; i++) {
        printf("\t%d\t%d\t%d\t%d\t%d\n", i,p[i],bn[i],b[bn[i]],frag[i]);
    }
    
}