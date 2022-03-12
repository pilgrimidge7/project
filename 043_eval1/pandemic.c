#include "pandemic.h"
#include <stdlib.h>
#include "ctype.h"
#include <stdio.h>
country_t parseLine(char * line) {
    country_t ans;
    //fill in the country's name
    ans.name[0] = '\0';
    const char * temp = line;
    char * con = ans.name;
    char * stop = ans.name + 64;
    /*read the name maximized at largest length 64 given in pandemic.h and before ',',
    we can ignore ' ' until stop but the name must be any sequence of characters. */
    while(con != stop && *temp != ','){
        if (*temp==' ' || isalpha(*temp)){
            *con = *temp;
            temp++;
            con++;
        }
        else {
            fprintf(stderr, "There is no country name or no ',' or other invalid form!\n");
            exit(EXIT_FAILURE);
        }
    }
    //for country name length is larger than 64
    if (con != stop) {
        *con = '\0';
    }
    else {
        fprintf(stderr, "The name is too long for this program!\n");
        exit(EXIT_FAILURE);
    }
    //fill in the population part, convert the type into integer
    temp++;
    ans.population = 0;
    if (isdigit(*temp)) {
        ans.population = atoi(temp);
    }
    else {
        fprintf(stderr, "There is no population!\n");
        exit(EXIT_FAILURE);
    }
    return ans;
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
    //if the data is NULL, the program will exit and print "Data is NULL!"
    if (data == NULL) {
        fprintf(stderr, "Data is NULL!\n");
        exit(EXIT_FAILURE);
    }
    //if the number of days is less than 7, the program will exit and print "Data is not enough!"
    if (n_days < 7) {
        fprintf(stderr, "Data is not enough!\n");
        exit(EXIT_FAILURE);
    }
    //if the avg is NULL, the program will exit and print "Avg is NULL!"
    if (avg == NULL) {
        fprintf(stderr, "Avg is NULL!\n");
        exit(EXIT_FAILURE);
    }
    /*to store the data to double precision, we can use 'a' to convert the type unsigned and size_t
    because the program will choose high precision of the types, the data will be stored in double */
    double a = 1;
    double sum = 0;
    //whatever the number of n_days, first get the sum of first 7 numbers from data[0] to data[6]
    for (size_t i = 0; i < 7; i++) {
        sum = sum + *(data + i) * a;
    }
    //get the avg of first 7 numbers from data[0] to data[6] and put it in avg[0]
    *avg = sum / 7;
    /*for n_days larger than 7, delete the first data in 7 in previous avg calculation and add one more data in order in data array
     then calculate the avg and put it in avg array in order
     */
    //the types of del and add need to correspond to data array, which is unsigned
    unsigned * del = data;
    unsigned * add = data + 7;
    if (n_days > 7) {
        for (size_t j = 1; j < n_days - 6; j++) {
            sum = sum - *del * a + *add * a;
            *(avg + j) = sum / 7;
            del++;
            add++;
        }
    }
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
    //if the data is NULL, the program will exit and print "Data is NULL!"
    if (data == NULL) {
        fprintf(stderr, "Data is NULL!\n");
        exit(EXIT_FAILURE);
    }
    //if the cum is NULL, the program will exit and print "cum is NULL!"
    if (cum == NULL) {
        fprintf(stderr, "cum is NULL!\n");
        exit(EXIT_FAILURE);
    }
    //if the population is 0, the program will exit and print "Population should be a positive integer!"
    if (pop == 0) {
        fprintf(stderr, "Population should be a positive number!\n");
        exit(EXIT_FAILURE);
    }
    /*to store the data to double precision, we can use 'a' to convert the type unsigned and size_t
    because the program will choose high precision of the types, the data will be stored in double */
    //get the sum and calculate cumulative cases, then put it in cum in order
    double a = 1;
    double population = pop * a;
    double sum = 0;
    double people = 100000;
    for (size_t k = 0; k < n_days; k++) {
        sum = sum + *(data + k) * a;
        *(cum + k) =  people * sum / population;
    }
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
    //if the countries array is NULL, the program will exit and print "Countries is NULL!"
    if (countries == NULL) {
        fprintf(stderr, "Countries is NULL!\n");
        exit(EXIT_FAILURE);
    }
    //if the data array is NULL, the program will exit and print "Data is NULL!"
    if (data == NULL) {
        fprintf(stderr, "Data is NULL!\n");
        exit(EXIT_FAILURE);
    }
    //compare specific number cases in the data array through countries and days and find the largest daily case among all countries
    char * country_name = NULL;
    unsigned number_cases = 0;
    for (size_t i = 0; i < n_days; i++) {
        for (size_t j = 0; j < n_countries; j++) {
            if (data[j][i] >= number_cases) {
                country_name = countries[j].name;
                number_cases = data[j][i];
            }
        }
    }
    printf("%s has the most daily cases with %u\n", country_name, number_cases);
}
