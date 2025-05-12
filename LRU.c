#include<stdio.h>
#include<stdlib.h>

int main(){
    int np,nf,recent=0,hit=0,fault=0,flag;
    printf("enter number of pages: ");
    scanf("%d",&np);
    printf("enter number of frames: ");
    scanf("%d",&nf);
    int p[np],f[nf],time[nf];
    printf("enter page reference string: \n");
    for(int i=0;i<np;i++){
        scanf("%d",&p[i]);
    }
    for(int i=0;i<nf;i++){
        f[i]=-1;
        time[i]=0;
    }
    printf("pages\t");
    for(int k=0;k<nf;k++){
        printf("F%d\t",k);
    }
    printf("status\t\n");

    for(int i=0;i<np;i++){
        flag=0;
        for(int j=0;j<nf;j++){
            if(p[i]==f[j]){
                hit++;
                recent++;
                time[j]=recent;
                flag=1;
                break;
            }
        }
        if(flag==0){
            fault++;
            int lru=0;
            for(int j=0;j<nf;j++){
                if(time[j]<time[lru]){
                    lru=j;
                }

            }
            f[lru]=p[i];
            recent++;
            time[lru]=recent;
        }
       
printf("%d\t",p[i]);
for(int k=0;k<nf;k++){
    printf("%d\t",f[k]);
}
if(flag==0){
    printf("miss\n");
}
else{
    printf("hit\n");
}

    }
    

}