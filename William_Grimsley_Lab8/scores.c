#include <stdio.h>
#include <stdbool.h>
int main(void){
    int n=0;
    while (n!=1){
        int n;
        printf("Enter the NFL score (Enter 1 to stop): ");
        scanf("%d", &n);
        if (n==1){
            break;
        }
        printf("Possible combinations is a team's score is %d:\n", n);

        for (int td2pt=0; td2pt*8<=n; td2pt++){
            for (int td1pt=0; td1pt*7<=n; td1pt++){
                for (int td=0; td*6<=n; td++){
                    for (int fdg=0; fdg*3<=n; fdg++){
                        for (int sft=0; sft*2<=n; sft++){
                            if(td2pt*8+td1pt*7+td*6+fdg*3+sft*2==n){
                                printf("%2d TD+2pt, %2d TD+FG, %2d TD, %2d 3pt FG, %2d Safety\n", td2pt, td1pt, td, fdg, sft);
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}