#include "rand_story.h"


int main(int argc, char ** argv){
    //check number of parameters
    if (argc != 2){
        error("usage: number of parameters\n");
    }
    //read from input story and store in struct s
    sty_t * s =  read_temp(argv[1]);
    process_temp(s, NULL, NULL, 0);
    //print the story
    for (size_t i = 0; i < s->sty_sz; i++){
        printf("%s\n", s->lines[i]);
    }
    free_s(s);
    return(EXIT_SUCCESS);
}
