#include "page.hpp"

int main(int argc, const char** argv) {
    if (argc != 2) {
        err_exit("Invalid Usage\n");
    }
    try{Page page(argv[1]);
        page.printPage();
    }
    catch(const unreachable_file & e) {
        err_exit("Can't open the file\n");
    }
    return EXIT_SUCCESS;
}
