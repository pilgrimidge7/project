#include "rand_story.h"

int main(int argc, char ** argv) {
    //check number of parameters
    if (argc != 3) {
        error("usage: number of parameters\n");
    }
    //read catarray and temp from file
    catarray_t * cats = read_cats(argv[1]);
    sty_t * s =  read_temp(argv[2]);
    //initialize a category_t to store previous word
    category_t pre;
    pre.name = strdup("previous");
    pre.words = NULL;
    pre.n_words = 0;
    //process the temp with substitution, 0 for allowing for repeated words
    process_temp(s, cats, &pre, 0);

    //print the story, free things on the heap and exit
    for (size_t i = 0; i < s->sty_sz; i++) {
        printf("%s", s->lines[i]);
    }
    free_s(s);
    free_arr(cats);
    free_cat(&pre);
    return EXIT_SUCCESS;

}
