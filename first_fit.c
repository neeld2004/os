#include<stdio.h>
 
int main(){
    int np,nb;
    printf("enter number of process :");
    scanf("%d",&np);
    printf("enter number of blocks :");
    scanf("%d",&nb);
    int frag[np], b[nb],p[np];
    printf("enter process size :");
    for(int i=0;i<np;i++){
        scanf("%d",&p[i]);
        }
    
    printf("enter block size :");
    for(int i=0;i<nb;i++){
    scanf("%d",&b[i]);
    }
  
    int bf[4]={0,0,0,0};
    int bn[3]={0,0,0};
    for(int i=0;i<np;i++){
        for(int j=0;j<nb;j++){
            if(b[j]>=p[i]&&bf[j]==0){
             bn[i]=j;
             frag[i]=b[j]-p[i];
             bf[j]=1;
             break;

            }
            
        }
    }
    printf("Process no.\tprocess size\tblock number\tblock size\tfragment size\n");
    for(int i = 0; i < np; i++) {
        printf("%d\t%d\t%d\t%d\t%d\n", i,p[i],bn[i],b[bn[i]],frag[i]);
    }
}