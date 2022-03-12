#include <iostream>
#include <cstdlib>
#include <utility>
#include <vector>
#include <set>
#include <fstream>

void err_exit(const char* msg);

class invalid_pages : public std::exception {
public:
    virtual const char * what() const throw() { return "Pages Invalid!"; }
};

class unreachable_file : public invalid_pages {};



