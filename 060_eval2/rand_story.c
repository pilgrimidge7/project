#include "rand_story.h"

//this function print the error message and exit
void error(const char * errmsg){
    fprintf(stderr, "%s\n", errmsg);
    exit(EXIT_FAILURE);
}

//this function close the file, print the error message and exit when can't close the input file
void close(FILE * file){
    if (fclose(file) != 0) {
        error("can't close the file\n");
    }
}

//this function read the input story and store in sty_t struct
sty_t * read_temp(const char * file) {
    //read from file story temp and check whether it is NULL
    FILE * f = fopen(file, "r");
    if (f == NULL) {
        error("can't open the file\n");
    }
    //initialize for getline
    char * line = NULL;
    size_t sz = 0;
    //initialize a sty_t struct and malloc to store lines and sty_sz
    sty_t * s = malloc(sizeof(*s));
    s->lines = NULL;
    s->sty_sz = 0;
    while (getline(&line, &sz, f) >= 0) {
        s->lines = realloc(s->lines, (s->sty_sz + 1) * sizeof(*s->lines));
        s->lines[s->sty_sz] = strdup(line);
        //strdup will malloc automatically, we will free those in free_s function
        free(line);
        line = NULL;
        s->sty_sz++;
    }
    free(line);
    close(f);
    return s;
}

//this function process the temp with substitution
void process_temp(sty_t * s, catarray_t * cats, category_t * pre, int mode){
    for (size_t i = 0; i < s->sty_sz; i++){
        s->lines[i] = sub_words(s->lines[i], cats, pre, mode);
    }
}

//this function get the words we want to substitute, mode=0 for repeated and mode = 1 for not repeated words
const char * get_words(char * orig_word, catarray_t * cats, category_t * pre, int mode) {
    if (cats == NULL) {
        return chooseWord(orig_word, cats);
    }
    //check all categories in the catarray, if there is no category name exists, go to the next step
    for (size_t i = 0; i < cats->n; i++){
        //if there is matched category, choose the random word and store it in the pre category
        if (strcmp(orig_word, cats->arr[i].name) == 0){
            const char * result = chooseWord(orig_word, cats);
            if (pre != NULL){
                pre->n_words++;
                pre->words = realloc(pre->words, pre->n_words * sizeof(*pre->words));
                pre->words[pre->n_words - 1] = strdup(result);
            }
            //for mode = 1, we should delete the chosen word in category
            if (mode == 1){
                del_word(cats, i, pre->words[pre->n_words - 1]);
            }
            return pre->words[pre->n_words - 1];
        }
    }
    //check the orig_word is greater than 0, if not, exit, if so, get the word
    if (atoi(orig_word) >= 1){
        if (pre != NULL){
            int index = pre->n_words - atoi(orig_word);
            if (index < 0){
                error("not enough previous words to refer to\n");
            }
            const char * result = pre->words[index];
            pre->n_words++;
            pre->words = realloc(pre->words, pre->n_words * sizeof(*pre->words));
            pre->words[pre->n_words-1] = strdup(result);
            return result;
        }
        error("valid integer but there is no previous words available\n");
    }
    //if the orig_word is neither a category name nor a valid integer, print different error msgs for different mode and exit
    else{
        if (mode == 0){
            error("there is neither category word nor valid integer\n");
        }
        if (mode == 1){
            error("there is neither category word nor valid integer or enough words in certain category\n");
        }
    }
    return NULL;
}

//delete one word from the catarray
void del_word(catarray_t * cats, size_t i, char * word) {
    cats->arr[i].n_words--;
    //if ths category is then empty, verify whether catarray is empty, if so, free all
    if (cats->arr[i].n_words == 0){
        cats->n--;
        if(cats->n == 0) {
            //if the cat array is empty, free the only category, but do not free cats->arr and cats themselves
            // since they will be freed together at the end of the program
            free(cats->arr[0].words[0]);
            free(cats->arr[0].words);
            free(cats->arr[0].name);
        }
        //if the category is empty but there are other categories left, make a deep copy of the cats->arr except the arr[i]
        else{
            category_t * new_arr = malloc(cats->n * sizeof (* new_arr));
            //deep copy from 0 to arr[i-1]
            for (size_t j = 0; j < i; j++){
                category_t new_cate;
                new_cate.name = strdup(cats->arr[j].name);
                new_cate.n_words = cats->arr[j].n_words;
                new_cate.words = malloc(new_cate.n_words * sizeof(*new_cate.words));
                for (size_t k = 0; k < new_cate.n_words; k++){
                    new_cate.words[k] = strdup(cats->arr[j].words[k]);
                }
                new_arr[j] = new_cate;
            }
            //deep copy from arr[i+1] to arr[n], we need add one on original cats->n b/c we cats->n-- before
            for (size_t j = i + 1; j < cats->n + 1; j++) {
                category_t new_cate;
                new_cate.name =strdup(cats->arr[j].name);
                new_cate.n_words = cats->arr[j].n_words;
                new_cate.words = malloc(new_cate.n_words * sizeof(*new_cate.words));
                for (size_t k = 0; k < new_cate.n_words; k++) {
                    new_cate.words[k] = strdup(cats->arr[j].words[k]);
                }
                new_arr[j - 1] = new_cate;
            }
            //free the arrs
            for (size_t j = 0; j < cats->n + 1; j++) {
                if (i == j) {
                    free(cats->arr[j].name);
                    free(cats->arr[j].words[0]);
                    free(cats->arr[j].words);
                }
                else {
                    for (size_t n = 0; n < cats->arr[j].n_words; n++) {
                        free(cats->arr[j].words[n]);
                    }
                    free(cats->arr[j].words);
                    free(cats->arr[j].name);
                }
            }
            //free cats->arr and assign the deep copy to it
            free(cats->arr);
            cats->arr = new_arr;
        }
    }
    //if the category is not empty either, make a deep copy of arr[i].words, free and assign words to new_words
    else {
        char ** new_words = malloc(cats->arr[i].n_words * sizeof(*new_words));
        size_t counter = 0;
        for (size_t j = 0; j < cats->arr[i].n_words + 1; j++) {
            if (strcmp(cats->arr[i].words[j], word) != 0) {
                new_words[counter] = strdup(cats->arr[i].words[j]);
                counter++;
            }
            free(cats->arr[i].words[j]);
        }
        free(cats->arr[i].words);
        cats->arr[i].words = new_words;
    }
}

//this function substitute the words line by line with recursion, find the "_ _" and substitute them one by one
char * sub_words(char * line, catarray_t * cats, category_t * pre, int mode){
    //find the "_" in double one pair by one pair by recursion until there is no "_" exists
    char * pos = strchr(line, '_');
    if (pos == NULL){
        //if there's no _, return the line
        return line;
    }
    //if there is a single "_", exit with error message
    char * pos1 = strchr(pos+1, '_');
    if (pos1 == NULL){
        error("single _, no second _ exists\n");
    }
    //get the category name's size
    size_t orig_word_sz = pos1 - pos - 1;
    //get the category name or integer
    char * orig_word = strndup(pos + 1, orig_word_sz);
    const char * sub_word  = get_words(orig_word, cats, pre, mode);
    //don't need the orig_word anymore
    free(orig_word);
    size_t sub_word_sz = strlen(sub_word);
    size_t line_sz = strlen(line);
    size_t result_length = line_sz - orig_word_sz + sub_word_sz - 2;
    //one more position to put '\0'
    char * result = malloc((result_length + 1) * sizeof(* result));
    //put \0 at the end in result
    memset(result,'\0', result_length + 1);
    //get the first part's size we want to copy by position difference
    size_t first  = pos - line;
    for (size_t i = 0; i < first; i++){
        result[i] = line[i];
    }
    for (size_t i = first; i < first + sub_word_sz; i++){
        result[i] = sub_word[i-first];
    }
    for (size_t i = first + sub_word_sz; i < result_length; i++) {
        result[i] = line[i - sub_word_sz + orig_word_sz + 2];
    }
    free(line);
    return sub_words(result, cats, pre ,mode);
}

//free the struct
void free_s(sty_t * s){
    for (size_t i=0; i<s->sty_sz; i++){
        free(s->lines[i]);
    }
    free(s->lines);
    free(s);
}

//read cats and words from file and store them in catarray
catarray_t * read_cats(const char * file){
    FILE * f = fopen(file, "r");
    if (f == NULL) {
        error("can't open the file\n");
    }
    char * line = NULL;
    size_t sz = 0;
    //initialize a cat array
    catarray_t * cats = malloc(sizeof(*cats));
    cats->n = 0;
    cats->arr = NULL;
    while(getline(&line, &sz, f)>=0){
        cats = store_line(line, cats);
        free(line);
        line = NULL;
    }
    free(line);
    close(f);
    return cats;
}

//this function stores words into the correct category in the catarray
catarray_t * store_line(char * line, catarray_t * cats){
    char * colon = strchr(line, ':');
    char * new_line = strchr(line, '\n');
    if (colon == NULL || new_line == NULL){
        error("input words are in incorrect format\n");
    }
    size_t cat_sz = colon - line;
    char * cat_word = strndup(line, cat_sz);
    size_t word_sz = new_line - colon - 1;
    char * word = strndup(colon + 1, word_sz);
    //check each category in the catarray to see if the category already exists
    for (size_t i = 0; i < cats->n; i++){
        //if exists, realloc cats->arr[i].words and store the word into words
        if (strcmp(cat_word, cats->arr[i].name)==0){
            cats->arr[i].n_words++;
            cats->arr[i].words = realloc(cats->arr[i].words, (cats->arr[i].n_words) * sizeof (*cats->arr[i].words));
            cats->arr[i].words[cats->arr[i].n_words-1] = word;
            free(cat_word);
            return cats;
        }
    }
    //if the cat name is not existing, add the cat name and word in a new category_t struct
    cats->n++;
    cats->arr = realloc(cats->arr, cats->n * sizeof (* cats->arr));
    category_t new_cat;
    new_cat.name = cat_word;
    new_cat.n_words = 1;
    new_cat.words = malloc(sizeof (*new_cat.words));
    new_cat.words[0] = word;
    cats->arr[cats->n-1] = new_cat;
    return cats;
}

//free the cat array
void free_arr(catarray_t * cats){
    if (cats != NULL){
        for (size_t i = 0; i < cats->n; i++){
            free_cat(&cats->arr[i]);
        }
        if (cats->arr != NULL){
            free(cats->arr);
        }
        free(cats);
    }
}

//free a category
void free_cat(category_t * cat){
    for (size_t i = 0; i < cat->n_words; i++){
        free(cat->words[i]);
    }
    free(cat->name);
    free(cat->words);
}
