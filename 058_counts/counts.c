#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"
counts_t * createCounts(void) {
  //WRITE ME
  counts_t * answer = malloc(sizeof(*answer));
    if (answer == NULL) {
        return NULL;
    }
    answer->array = NULL;
    answer->size = 0;
    answer->unknown = 0;
    return answer;
}
void addCount(counts_t * c, const char * name) {
  //WRITE ME
  if (name == NULL) {
        c->unknown++;
    }
    else {
        int check = 1;
        for (int i = 0; i < c->size; i++) {
            if (strcmp(c->array[i]->string, name) == 0) {
                c->array[i]->time++;
                check = 0;
            }
        }
        if (check == 1) {
            c->size++;
            c->array = realloc(c->array, c->size * sizeof(*c->array));
            one_count_t * onecount = malloc(sizeof(*onecount));
            c->array[c->size - 1] = onecount;
            c->array[c->size - 1]->string = name;
            c->array[c->size - 1]->time = 1;
        }
    }
}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  for (int i = 0; i < c->size; i++) {
        fprintf(outFile, "%s:%d\n", c->array[i]->string, c->array[i]->time);
    }
    if (c->unknown > 0) {
        fprintf(outFile, "<unknown>:%d\n", c->unknown);
    }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  for (int i = 0; i < c->size; i++) {
        free(c->array[i]);
    }
    free(c->array);
    free(c);
}
