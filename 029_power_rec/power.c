#include<stdio.h>
#include<stdlib.h>
unsigned ans = 1;
unsigned power(unsigned x, unsigned y){
  if (y==0){
    ans =  1;
  }
  else{
    ans =  x*power(x, y-1);
  }
  return ans;
}

  
