#include "rand_story.h"

int main(int argc, char ** argv) {
    //check number of parameters
    if (argc != 2) {
        error("usage: number of parameters\n");
    }
    catarray_t * cats = read_cats(argv[1]);
    printWords(cats);
    free_arr(cats);
    return EXIT_SUCCESS;
}
