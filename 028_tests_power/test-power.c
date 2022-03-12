#include<stdio.h>
#include<stdlib.h>


int power(unsigned x, unsigned y);
void run_check(unsigned x, unsigned y, unsigned expected_ans){
  
  if (expected_ans != power(x, y)){
    printf("failure");
    exit(EXIT_FAILURE);
  }
  
  
}
  
int main(void){
  run_check(1234567, 1, 1234567);
  run_check(3,4,81);  
  run_check(1, 0, 1);
  run_check(5, 2, 25);
  run_check(0, 0, 1);
  run_check(1, 50, 1);
  run_check(0, 2, 0);
  
  return EXIT_SUCCESS;
}
