#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
#include <assert.h>


kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  FILE * f = fopen(fname, "r");
    if (f == NULL) {
        perror("Could not open the file\n");
        return NULL;
    }
    kvarray_t * answer = malloc(sizeof(*answer));
    if (answer == NULL) {
        perror("Could not malloc\n");
        return NULL;
    }
    answer->numparray = 0;
    answer->parray = NULL;
    char * store = NULL;
    size_t size = 0;
    size_t count = 0;
    while (getline(&store, &size, f) >= 0) {
        answer->numparray++;
        answer->parray = realloc(answer->parray, answer->numparray * sizeof(*answer->parray));
        if (answer->parray == NULL) {
            perror("Could not realloc\n");
            return NULL;
        }
        kvpair_t * kv = malloc(sizeof(*kv));
        kv->key = store;
        char * p = strchr(kv->key, '=');
        if (p != NULL) {
            *p = '\0';
        }
        kv->value = p + 1;
        char * q = strchr(kv->value, '\n');
        if (q != NULL) {
            *q = '\0';
        }
        answer->parray[count++] = kv;
        //new memory location for array
        store = NULL;
    }
    int result = fclose(f);
    assert(result == 0);
    free(store);
    return answer;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  for (int i = 0; i < pairs->numparray; i++) {
        free(pairs->parray[i]->key);
        free(pairs->parray[i]);
    }
    free(pairs->parray);
    free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  for (int i = 0; i < (pairs->numparray); i++) {
        printf("key = '%s' value = '%s'\n", pairs->parray[i]->key, pairs->parray[i]->value);
    }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  char * v = NULL;
    for (int i = 0; i < pairs->numparray; i++) {
        if (strcmp(pairs->parray[i]->key, key) == 0) {
            v = pairs->parray[i]->value;
        }
    }
    return v;
}
