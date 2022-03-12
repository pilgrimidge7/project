#include <stdio.h>
#include <cstdlib>
#include "readFreq.h"


void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256 ) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
uint64_t * readFrequencies(const char * fname) {
  //WRITE ME!
  std::ifstream ifs;
    ifs.open(fname, std::ifstream::in);
    if(ifs.fail()){
        std::cerr<<"Can't open the file\n"<<std::endl;
    }
    uint64_t * arr = new uint64_t[257]();
    int c;
    //count the frequency
    while ((c = ifs.get()) != EOF){
        arr[c]++;
    }
    arr[256]=1;
    ifs.close();
    return arr;
}
