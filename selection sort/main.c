#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "selection_sort.h"

#define BILLION 1000000000
#define BUFFER 100

void writeToFile(int64_t *array, int64_t len, FILE *outputFilePtr) {
    for (int i = 0; i < len; i++) {
        fprintf(outputFilePtr, "%lld\n", array[i]);
    }
}

int64_t getLen(FILE *filePtr) {
    char string[BUFFER];
    int64_t count = 0;
    while (fscanf(filePtr, "%s", string) == true) {
        count++;
    }
    rewind(filePtr);
    return count;
}

int64_t *parse(FILE *filePtr, int64_t len) {
    char string[BUFFER];
    int64_t *array;
    array = (int64_t *) malloc(len * sizeof(int64_t));
    char *endPtr;
    int i = 0;
    while (fscanf(filePtr, "%s", string) == true) {
        int64_t num = strtof(string, &endPtr);
        array[i] = num;
        i++;
    }
    return array;
}

int main(int argc, char** argv) {
    if(argc != 3){
        perror("There's not 3 arguments");
        exit(EXIT_FAILURE);
    }
    char* inputFilePath = argv[1];
    char* outputFilePath = argv[2];
    FILE *inputFilePtr,  *outputFilePtr;
    inputFilePtr = fopen(inputFilePath, "r");
    if (inputFilePtr == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    int64_t len = getLen(inputFilePtr);
    int64_t *array = parse(inputFilePtr, len);
    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);
    array = selection_sort(array, len);
    clock_gettime(CLOCK_REALTIME, &end);
    fclose(inputFilePtr);
    double timeSpent = (double) (end.tv_sec - start.tv_sec) +
                       (end.tv_nsec - start.tv_nsec) / BILLION;
    outputFilePtr = fopen(outputFilePath, "w");
    writeToFile(array, len, outputFilePtr);
    free(array);
    FILE *statisticsFilePtr;
    statisticsFilePtr = fopen("../statistics.txt", "a");
    fprintf(statisticsFilePtr, "%lld:%f\n", len, timeSpent);
    fclose(statisticsFilePtr);
    return 0;
}
