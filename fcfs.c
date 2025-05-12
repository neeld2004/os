#include<stdio.h>
#include<stdlib.h>

struct process{
    int  at,bt,ct,tat,wt,rt,start_time;
};

int main(){
    int n;
    printf("enter number of proccess: ");
    scanf("%d",&n);
    struct process p[n];
    printf("enter arrival time of each process: ");
    for (int i=0;i<n;i++){
        scanf("%d",&p[i].at);
    }
    printf("enter burst time of each process: ");
    for (int i=0;i<n;i++){
        scanf("%d",&p[i].bt);
    }
    
    p[0].start_time = (p[0].at == 0) ? 0 : p[0].at;

        p[0].ct=p[0].start_time+p[0].bt;
        p[0].tat=p[0].ct-p[0].at;
        p[0].wt=p[0].tat-p[0].bt;
        p[0].rt=p[0].wt;
    


    for(int i=1;i<n;i++){
      
        if(p[i-1].ct>p[i].at){
            p[i].start_time=p[i-1].ct;
        }
        if(p[i-1].ct==p[i].at){
            p[i].start_time=p[i-1].ct;
        }
        if(p[i-1].ct<p[i].at){
            p[i].start_time=p[i].at;
        }
        p[i].ct=p[i].start_time+p[i].bt;
        p[i].tat=p[i].ct-p[i].at;
        p[i].wt=p[i].tat-p[i].bt;
        p[i].rt=p[i].wt;
    }
    printf("Process No.\tArrival Time\tBurst Time\tCompletion Time\tTAT\tWaiting Time\tResponse Time\n");

for(int i = 0; i < n; i++) {
    printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t%d\t\t%d\n", 
           i, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt, p[i].rt);
}

printf("gant chart: \n");

for(int i=0;i<n;i++){
    printf(" | ");
    printf("P%d",i);
}
printf(" | ");
printf("\n");
printf(" 0");
for(int i=0;i<n;i++){
    printf("    %d",p[i].ct);
    
}

}