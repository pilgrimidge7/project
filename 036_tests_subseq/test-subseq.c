#include<stdio.h>
#include<stdlib.h>
size_t maxSeq(int * array, size_t n);
void run_check(int * array, size_t n, size_t expected_ans){
    if(expected_ans != maxSeq(array, n)){
        printf("failure");
        exit(EXIT_FAILURE);
    }
}

int main(void){
    int array1[5] = {0,0,0,0,0};
    run_check(array1, 5, 1);
    int array2[5] = {0,1,2,3,4};
    run_check(array2,5,5);
    run_check(array2,2,2);
    run_check(array2,6,5);
    int array3[3] = {1234567,2345678,3456789};
    run_check(array3,3,3);
    int array4[5] = {-2,2,4,6,6};
    run_check(array4,5,4);
    int array5[5]={3,2,1,0,-1};
    run_check(array5,5,1);
    int array6[9] = {123,-2,234,345,456,567,789,1234,2345};
    run_check(array6,9,8);
    run_check(NULL, 0, 0);
    return EXIT_SUCCESS;
}
