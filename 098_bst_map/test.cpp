#include <cstdlib>
#include <iostream>
#include <string>
#include "bstmap.h"
int main(void) {
  BstMap<int, std::string> myTree;
  myTree.add(6, "hello");
  myTree.add(1, "world");
  myTree.add(5, "bye");
  myTree.add(4, "test");
  std::cout << "find 6 " << myTree.lookup(6) << "\n";
  std::cout << "find 1 " << myTree.lookup(1) << "\n";
  std::cout << "find 5 " << myTree.lookup(5) << "\n";
  BstMap<int, std::string> t2(myTree);
  t2.add(10, "xxxx10");
  BstMap<int, std::string> t3 = t2;
  std::cout << "t3 find 10 " << t3.lookup(10) << "\n";
  t3 = myTree;
  std::cout << "t3 find 1 " << t3.lookup(1) << "\n";
  std::cout << "t3 find 10 " << t3.lookup(10) << "\n";
  myTree.remove(6);
  return EXIT_SUCCESS;
}
