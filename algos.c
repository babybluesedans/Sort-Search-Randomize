#include "algos.h"

int* createArray(FILE* file, int size)
{
    rewind(file);
    int* copiedList = malloc(sizeof(int) * size);
    char tmpInt; //char to get one number at a time
    int tmpInt2 = 0;
    int i = 0;
    while(fread(&tmpInt, sizeof(char), 1, file))
    {
        if (!isspace(tmpInt))
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

int findListSize(FILE* file)
{
    int count = 0;
    char c;
    while (fread(&c, sizeof(char), 1, file))
    {
        if (isspace(c))
        {
            count++;
        }
    }
    return count;
}
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