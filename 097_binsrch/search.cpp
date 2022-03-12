#include <iostream>
#include <cstdlib>
#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high) {
  if(low==high || low ==high-1){
    return low;
  }
  int mid = (low+high)/2;
  int res = f->invoke(mid);
  if (res==0){
    return mid;
  }
  else if (res>0){
    return binarySearchForZero(f, low, mid);
  }
  else if (res<0){
    return binarySearchForZero(f, mid, high);
  }
  std::cout << "Unepected circumstances!" << std::endl;
  return low;


  

}
