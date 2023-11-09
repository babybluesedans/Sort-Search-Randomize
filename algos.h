#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/resource.h>
#include <sys/time.h>

int* createArray(FILE* file, int size);
int findListSize(FILE* file);
int* selectionSort(int* array, int arrSize);
int* bubbleSort(int* array, int arrSize);
int* mergeSort(int* array, int arrSize);
double calculate(const struct rusage *b, const struct rusage *a);