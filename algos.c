#include "algos.h"

//allocates an array of <size> and reads input file. 
//reads one character at a time, creates full integer when 
//blank space or a comma is read and inserts into array
//returns pointer to created array
int* createArray(FILE* file, int size)
{
    rewind(file);
    int* copiedList = malloc(sizeof(int) * size);
    char tmpInt; //char to get one number at a time
    int tmpInt2 = 0;
    int i = 0;
    while(fread(&tmpInt, sizeof(char), 1, file))
    {
        if (!isspace(tmpInt) || tmpInt == ',')
        {
            tmpInt2 = (tmpInt2 * 10) + (tmpInt - '0');
        }
        else
        {
            copiedList[i] = tmpInt2;
            tmpInt2 = 0;
            i++;
        }
        
    }
    return copiedList;
}

//reads file and counts commas or blank space
//returns count of seperate numbers in file
int findListSize(FILE* file)
{
    int count = 0;
    char c;
    while (fread(&c, sizeof(char), 1, file))
    {
        if (isspace(c) || c == ',')
        {
            count++;
        }
    }
    return count;
}

//a nested for loop that iterates through an array to find the lowest number
//swaps lowest number found by inner for loop with iterator value from outer for loop
//returns pointer to the now sorted input array
int* selectionSort(int* array, int arrSize)
{
    int tmpIndex;
    for(int arrIndex = 0; arrIndex < arrSize; arrIndex++)
    {
        int lowestNum = INT_MAX;
        for (int updatedIndex = arrIndex; updatedIndex < arrSize; updatedIndex++)
        {
            if (array[updatedIndex] <= lowestNum)
            {
                lowestNum = array[updatedIndex];
                tmpIndex = updatedIndex;
            }
        }
        array[tmpIndex] = array[arrIndex];
        array[arrIndex] = lowestNum;
    }
    return array;
}

//iterates through array making a 'swap' every time the current iteration
//is larger than the current iteration + 1
//returns pointer to the now sorted input array
int* bubbleSort(int* array, int arrSize)
{
    int swaps = 1;
    int tmpIndex;
    int tmpValue;
    while (swaps != 0)
    {
        swaps = 0;
        for (int arrIndex = 0; arrIndex < arrSize - 1; arrIndex++)
        {
            if (array[arrIndex] > array[arrIndex + 1])
            {
                tmpValue = array[arrIndex + 1];
                array[arrIndex + 1] = array[arrIndex];
                array[arrIndex] = tmpValue;
                swaps++;
            }
        }
    }
    return array;
}

//recursively calls itself to cut itself into two arrays, left and right
//stops when each half only holds 1 number
//if array is odd (not divisible by two), the extra is always added to left half.
//sorts each iteration of recursion, starting small and working back to the two halves 
//of the original array.
//frees its malloc'd arrays after inserting sorted numbers. 
//there is a likely less complicated way to do this with one auxillary array but
//real talk this was just easier to visualize
int* mergeSort(int* array, int arrSize)
{
    int leftHalfSize = arrSize / 2;
    int rightHalfSize = arrSize / 2;
    if (arrSize % 2 != 0)
    {
        leftHalfSize++;
    }

    int* leftHalf = malloc(sizeof(int) * leftHalfSize);
    int* rightHalf = malloc(sizeof(int) * rightHalfSize);
    int leftIndex = 0;
    int rightIndex = 0;

    if (arrSize > 1)
    {
        for (int index = 0; index < leftHalfSize; index++)
        {
            leftHalf[index] = array[index];
        }

        for (int index = 0; index < rightHalfSize; index++)
        {
            rightHalf[index] = array[index + leftHalfSize];
        }

        leftHalf = mergeSort(leftHalf, leftHalfSize);
        rightHalf = mergeSort(rightHalf, rightHalfSize);

        for (int index = 0; index < arrSize; index++)
        {
            if (rightIndex > rightHalfSize - 1)
            {
                while (index < arrSize)
                {
                    array[index] = leftHalf[leftIndex];
                    leftIndex++;
                    index++;
                }
                break;
            }
            else if (leftIndex > leftHalfSize - 1)
            {
                while (index < arrSize)
                {
                    array[index] = rightHalf[rightIndex];
                    rightIndex++;
                    index++;
                }
                break;
            }

            if (leftHalf[leftIndex] <= rightHalf[rightIndex])
            {
                array[index] = leftHalf[leftIndex];
                leftIndex++;
            }
            else
            {
                array[index] = rightHalf[rightIndex];
                rightIndex++;
            }
        }
    }

    free(leftHalf);
    free(rightHalf);

    return array;
}

//takes arguements of program time before and after a process
//multiplies the (post-process) user time in seconds by a million, adds the milliseconds
//subtracts this total from seconds/milliseconds of pre-process user time, then does the
//same thing with system time, divides by a million, and returns seconds in a sec.millisec format
double calculate(const struct rusage *b, const struct rusage *a)
{
    if (a == NULL || b == NULL)
    {
        return 0.0;
    }
    else
    {
        return ((((a->ru_utime.tv_sec * 1000000 + a->ru_utime.tv_usec) -
                  (b->ru_utime.tv_sec * 1000000 + b->ru_utime.tv_usec)) +
                 ((a->ru_stime.tv_sec * 1000000 + a->ru_stime.tv_usec) -
                  (b->ru_stime.tv_sec * 1000000 + b->ru_stime.tv_usec)))
                / 1000000.0);
    }
}

//fixes a bug where scanf can 'brick' itself
//if characters consumed by scanf is 0, assume something went wrong
//consume the rest of the scanf input with getchar until it hits the '\n'
//pushes current char back to keyboard input with ungetc
void getInteger(int *buffer)
{
    char c;
    if (scanf("%i", buffer) == 0)
    {
       c = getchar();
       while (c != '\n')
       {
        c = getchar();
       }
       ungetc(c, stdin);
    }
}

//iterates through array until current iteration matches the targer
//returns 0 or 1, boolean.
int linearSearch(int targetForSearch, int* array, int arrSize)
{
    for (int i = 0; i < arrSize; i++)
    {
        if(targetForSearch == array[i])
        {
            return 1;
        }
    }
    return 0;
}

int* randomize(int* array, int arrSize)
{
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    srand(current_time.tv_usec);
    for (int i = 0; i < arrSize; i++)
    {
        unsigned int g = rand();
        array[i] = (g % 100000);
    }
    return array;
}

void getString(char** buffer)
{ 
    char c;
    if (scanf(" %[^\n]%*c", *buffer) == 0)
    {
       c = getchar();
       while (c != '\n')
       {
        c = getchar();
       }
       ungetc(c, stdin);
    }
}

void randomizeFile(FILE* file, int size)
{
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    srand(current_time.tv_usec);
    int randNum;
    for (int i = 0; i < size; i++)
    {
        randNum = rand() % 100000;
        fprintf(file, "%i\n", randNum);
    }
}

int binarySearch(int target, int* array, int arrSize)
{
    int updatedSize = arrSize / 2;
    int i = updatedSize - 1;

    while (updatedSize != 0)
    {
        if (array[i] == target)
        {
            return 1;
        }

        if (array[i] > target)
        {
            i -= (updatedSize / 2);
        }
        else if (array[i] < target)
        {
            i += (updatedSize / 2);
        }
        updatedSize /= 2;
    }
    return 0;
}