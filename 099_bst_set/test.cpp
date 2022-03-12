#include <cstdlib>
#include <iostream>
#include <string>

#include "bstset.h"
int main(void) {
  BstSet<int> myTree;
  myTree.add(6);
  myTree.add(1);
  myTree.add(5);
  myTree.add(4);
  std::cout << "find 6 " << myTree.contains(6) << "\n";
  std::cout << "find 1 " << myTree.contains(1) << "\n";
  std::cout << "find 5 " << myTree.contains(4) << "\n";
  BstSet<int> t2(myTree);
  t2.add(10);
  BstSet<int> t3 = t2;
  std::cout << "t3 find 10 " << t3.contains(10) << "\n";
  t3 = myTree;
  std::cout << "t3 find 1 " << t3.contains(1) << "\n";
  std::cout << "t3 find 10 " << t3.contains(10) << "\n";
  //  std::cout << "find 7 " << myTree.lookup(7) << "\n";
  // myTree.remove(3);
  myTree.remove(6);
  return EXIT_SUCCESS;
}
