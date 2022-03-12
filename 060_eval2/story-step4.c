#include "rand_story.h"
#define OPTION "-n"

int main(int argc, char ** argv){
    if (argc != 3 && argc != 4){
        error("usage: number of parameters\n");
    }
    //the same as in step 3
    if (argc == 3){
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

        //print the story, free all on the heap and exit
        for (size_t i = 0; i < s->sty_sz; i++) {
            printf("%s", s->lines[i]);
        }
        free_s(s);
        free_arr(cats);
        free_cat(&pre);
        return EXIT_SUCCESS;
    }
    if (argc == 4){
        if (strcmp(OPTION, argv[1]) != 0){
            error("usage: only '-n' or filename is acceptable\n");
        }
        catarray_t * cats = read_cats(argv[2]);
        sty_t * s = read_temp(argv[3]);
        category_t pre;
        pre.name = strdup("previous");
        pre.words = NULL;
        pre.n_words = 0;
        //process the temp with substitution, 1 for not allowing the repeated words
        process_temp(s, cats, &pre, 1);
        //print the story, free all on the heap and exit
        for (size_t i = 0; i < s->sty_sz; i++) {
            printf("%s", s->lines[i]);
        }
        free_s(s);
        free_arr(cats);
        free_cat(&pre);
        return EXIT_SUCCESS;
    }

}
