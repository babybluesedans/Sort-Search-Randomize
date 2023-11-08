#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <ctype.h>

int* createArray(FILE* file, int size);
int findListSize(FILE* file);
int* selectionSort(int* array, int arrSize);
int* bubbleSort(int* array, int arrSize);
int* mergeSort(int* array, int arrSize);