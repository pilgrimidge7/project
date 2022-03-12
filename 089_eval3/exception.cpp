#include "exception.hpp"

void err_exit(const char* msg){
    std::cerr << msg << std::endl;
    exit(EXIT_FAILURE);
}

