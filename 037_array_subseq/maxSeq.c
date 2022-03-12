#include<stdio.h>
#include <stdlib.h>
size_t maxSeq(int * array, size_t n){
    size_t best_ans = 1;
    if (array==NULL){return 0;}
    if (n==0){return 0;}
    size_t answer=1 ;
    for (int i = 0;i<n-1;i++) {
        if (array[i + 1] > array[i]) {answer++;}
        if (array[i + 1] <= array[i] && best_ans < answer) {best_ans = answer;}
        if (array[i + 1] <= array[i]) {answer = 1;}

        if (best_ans < answer) {
            best_ans = answer;
        }
    }
    return best_ans;
}


