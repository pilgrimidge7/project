#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "provided.h"


//any functions you want your main to use

typedef struct sty_tag{
    char ** lines;
    size_t sty_sz;
}sty_t;

//print error messages and exit
void error(const char * errmsg);
//close the input file and print error messages and exit if can't
void close(FILE * file);
//read the input story and store in struct sty_t
sty_t * read_temp(const char * file);
//this function process the temp with substitution
void process_temp(sty_t * s, catarray_t * cats, category_t * pre, int mode);
//this function get the words we want to substitute
const char * get_words(char * orig_word, catarray_t * cats, category_t * pre, int mode);
//this function substitute the words line by line with recursion, find the "_ _" and substitute them one by one
char * sub_words(char * line, catarray_t * cats, category_t * pre, int mode);
//free the struct
void free_s(sty_t * s);
//read cats and words from file and store them in catarray
catarray_t * read_cats(const char * file);
//store words into the correct category in the catarray
catarray_t * store_line(char * line, catarray_t * cats);
//delete one word from the catarray in non-repeated mode
void del_word(catarray_t * cats, size_t i, char * word);
//free the cat array
void free_arr(catarray_t * cats);
//free a category
void free_cat(category_t * cat);


#endif
