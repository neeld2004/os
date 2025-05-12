#include<stdio.h>

int main(){
    int np, nf, fault = 0, hit = 0, recent = 0;
    printf("enter number of pages: \n");
    scanf("%d", &np);
    printf("enter number of frames: \n");
    scanf("%d", &nf);

    int p[np], f[nf], time[nf];
    printf("enter page reference string: \n");
    for(int i = 0; i < np; i++){
        scanf("%d", &p[i]);
    }

    for(int i = 0; i < nf; i++){
        f[i] = -1;
        time[i] = 0;
    }

    printf("page\t");
    for(int i = 0; i < nf; i++){
        printf("F%d\t", i);
    }
    printf("status\t\n");

    for(int i = 0; i < np; i++){
        int flag = 0;

        for(int j = 0; j < nf; j++){
            if(f[j] == p[i]){
                hit++;
                recent++;
                time[j] = recent;
                flag = 1;
                break;
            }
        }

        if(flag == 0){
            fault++;
            int lru = 0;
            for(int j = 1; j < nf; j++){
                if(time[j] < time[lru]){
                    lru = j;
                }
            }
            f[lru] = p[i];
            recent++;
            time[lru] = recent;
        }

        printf("%d\t", p[i]);
        for(int j = 0; j < nf; j++){
            if(f[j] != -1)
                printf("%d\t", f[j]);
            else
                printf("-\t");
        }

        if(flag == 0){
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
