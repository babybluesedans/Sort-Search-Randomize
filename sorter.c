#include "algos.h"

#undef getrusage

//TODOS
//implement binary search
//make more sorting functions!

//--------------------------------------------------------------------------------------------------------------------
//This program takes a path to a file of a list of numbers as an arguement, and gives the user options to sort the
//numbers or search for numbers within the file.The user may also randomize the list.The sorted list will be printed
//to an output file. Program will remain open until the user decides to exit.
//--------------------------------------------------------------------------------------------------------------------

int main(int argc, char* argv[])
{
    //initialize variables 
    int menuChoice = 0;
    int listSize = 0;
    int inputListSize = 0;
    int sortChoice = 0;
    int searchChoice = 0;
    int randomizerChoice = 0;
    int nameChoice = 0;
    int sizeChoice = 0;
    int* sortedArray = NULL;
    int* listAsArray = NULL;
    int* randomizedArray = NULL;
    int targetForSearch = INT_MAX;
    char* outputName = malloc(sizeof(char) * 26);
    FILE* INPUT = NULL;
    FILE* OUTPUT = NULL;

    //initialize flags
    int exitProgramFlag = 0;    
    int inputFileNeededFlag = 0;
    int inputOpenedFlag = 0;
    int outputFileNeededFlag = 0;
    int outputOpenedFlag = 0;
    int listSizedFlag = 0;
    int listToBeSizedFlag = 0;
    int arrayToBeCreatedFlag = 0;
    int listSortedFlag = 0;
    int arrayCreatedFlag = 0;
    int searchSuccessfulFlag = 0;
    int listSearchedFlag = 0;
    int sortSelectedFlag = 0;
    int searchSelectedFlag = 0;
    int selectionFlag = 0;
    int bubbleFlag = 0;
    int mergeFlag = 0;
    int linearFlag = 0;
    int binaryFlag = 0;
    int randomizeSelectedFlag = 0;
    int overwriteInputFlag = 0;
    int listRandomizedFlag = 0;
    int outputNamedFlag = 0;
    int newSizeFlag = 0;
    
    //argv[1] will be a file containing numbers seperated by blank characters
    if (argc != 2)
    {
        printf("Usage ./sorter [image path]\n");
        return 1;
    }

    INPUT = fopen(argv[1], "r");

    if (INPUT == NULL)
    {
        printf("Could not load input file.\n");
        return 1;
    }

    //define before and after times
    //define time variables
    struct rusage before, after;
    double listSizingTime = 0.0;
    double arrayCreationTime = 0.0;
    double arraySortingTime = 0.0;
    double searchTime = 0.0;
    double randomizeTime = 0.0;
    double totalTime = 0.0;
    
    while(!exitProgramFlag)//actual program
    {
        //prompt user if they would like to search or sort a list of numbers, or exit
        printf("\nPlease select an option below:\n1) Sort a list\n");
        printf("2) Search for a number in a list\n3) Randomize a list\n");
        printf("4) Exit\n\nChoice: ");

        while(menuChoice < 1 || menuChoice > 4)
        {
            getInteger(&menuChoice);
        }
        if (menuChoice == 1)//user selected Sort
        {
            sortSelectedFlag = 1;
        }
        else if (menuChoice == 2)//user selected Search
        {
            searchSelectedFlag = 1;
        }
        else if (menuChoice == 3)
        {
            randomizeSelectedFlag = 1;
        }
        else if (menuChoice == 4)//user selected Exit
        {
            exitProgramFlag = 1;
            break;
        }

        if (sortSelectedFlag)
        {
            outputFileNeededFlag = 1;

            //user is prompted by a menu with sort options
            printf("\nSelect one of the sorting options\n1) Selection sort\n");
            printf("2) Bubble sort\n3) Merge sort\n\nChoice: ");
            while (sortChoice < 1 || sortChoice > 3)
            {
                getInteger(&sortChoice);
            }

            if (sortChoice == 1)
            {
                selectionFlag = 1;
                listToBeSizedFlag = 1;
                arrayToBeCreatedFlag = 1;
            }
            else if(sortChoice == 2)
            {
                bubbleFlag = 1;
                listToBeSizedFlag = 1;
                arrayToBeCreatedFlag = 1;
            }
            else if (sortChoice == 3)
            {
                mergeFlag = 1;
                listToBeSizedFlag = 1;
                arrayToBeCreatedFlag = 1;
            }

        }
        else if (searchSelectedFlag)
        {
            printf("\nWhat number would you like to search for?\n\nNumber: ");
            while(targetForSearch == INT_MAX)
            {
                getInteger(&targetForSearch);
            }

            printf("How would you like to search?\n");
            printf("\n1) Linear search\n2) Binary Search\n\n");
            printf("Choice: ");
            while (searchChoice < 1 || searchChoice > 2)
            {
                getInteger(&searchChoice);
            }

            if (searchChoice == 1)
            {
                linearFlag = 1;
                arrayToBeCreatedFlag = 1;
                listToBeSizedFlag = 1;
            }
            else if (searchChoice == 2)
            {
                binaryFlag = 1;
            }
        }
        else if (randomizeSelectedFlag)
        {
            printf("Would you like to:\n1) Randomize input file\n");
            printf("2) Randomize output file\n");
            while(randomizerChoice < 1 || randomizerChoice > 2)
            {
                getInteger(&randomizerChoice);
            }

            if (randomizerChoice == 1)
            {
                overwriteInputFlag = 1;
                printf("Would you like to use the same size?");
                printf("\n1) Yes\n2) No\n\nChoice: ");
                while (sizeChoice < 1 || sizeChoice > 2)
                {
                    getInteger(&sizeChoice);
                }

                if (sizeChoice == 1)
                {
                    listToBeSizedFlag = 1;
                }
                else
                {
                    printf("How many numbers would you like in your new list?\n");
                    printf("Size: ");
                    while (inputListSize == 0)
                    {
                        getInteger(&inputListSize);
                    }
                    listSize = inputListSize;
                    listSizedFlag = 1;

                }

            }
            else if(randomizerChoice == 2)
            {
                if (!outputOpenedFlag)
                {
                    outputFileNeededFlag = 1;
                }
                arrayToBeCreatedFlag = 1;
                listToBeSizedFlag = 1;
            }
        }

        if (outputFileNeededFlag)
        {
            char* bufferStr = malloc(sizeof(char) * 26);
            printf("Would you like to name your output file?\n");
            printf("1) Yes\n2) no\n\nChoice: ");
            while (nameChoice < 1 || nameChoice > 2)
            {
                getInteger(&nameChoice);
            }

            if (nameChoice == 1)
            {
                printf("Name: ");
                getString(&outputName);
            }
            else
            {
                outputName = "output";
            }
            sprintf(bufferStr, "output/%s.txt", outputName);
            outputName = bufferStr;
        }

        if(overwriteInputFlag)
        {
            if (outputOpenedFlag)
            {
                fclose(OUTPUT);
            }
            OUTPUT = fopen(argv[1], "w");
            if (OUTPUT == NULL)
            {
                printf("Could not create output file.\n");
                return 1;
            }
        }

        //use flags as instructions for execution
        if (listSizedFlag)
        {
            listToBeSizedFlag = 0;
        }
        if (arrayCreatedFlag)
        {
            arrayToBeCreatedFlag = 0;
        }
        if (listToBeSizedFlag)
        {
            getrusage(RUSAGE_SELF, &before);//starting time
            listSize = findListSize(INPUT);
            getrusage(RUSAGE_SELF, &after);//ending time
            listSizingTime = calculate(&before, &after);//subtract difference
            listSizedFlag = 1;
            listToBeSizedFlag = 0;
            printf("SIZING TIME: %.4f\n", listSizingTime);
            if(overwriteInputFlag)
            {
                inputListSize = listSize;
            }
        }
        if (arrayToBeCreatedFlag)
        {
            getrusage(RUSAGE_SELF, &before);
            listAsArray = createArray(INPUT, listSize);
            getrusage(RUSAGE_SELF, &after);
            arrayCreationTime = calculate(&before, &after);
            arrayToBeCreatedFlag = 0;
            arrayCreatedFlag = 1;
            printf("CREATION TIME: %.4f\n", arrayCreationTime);
        }
        if (selectionFlag)
        {
            getrusage(RUSAGE_SELF, &before);
            sortedArray = selectionSort(listAsArray, listSize);
            getrusage(RUSAGE_SELF, &after);
            arraySortingTime = calculate(&before, &after);
            listSortedFlag = 1;
        }
        if (bubbleFlag)
        {
            getrusage(RUSAGE_SELF, &before);
            sortedArray = bubbleSort(listAsArray, listSize);
            getrusage(RUSAGE_SELF, &after);
            arraySortingTime = calculate(&before, &after);
            listSortedFlag = 1;
        }
        if (mergeFlag)
        {
            getrusage(RUSAGE_SELF, &before);
            sortedArray = mergeSort(listAsArray, listSize);
            getrusage(RUSAGE_SELF, &after);
            arraySortingTime = calculate(&before, &after);
            listSortedFlag = 1;
        }
        if (listSortedFlag)
        {
            printf("SORT TIME: %.4f\n", arraySortingTime);
        }
        if (linearFlag)
        {
            getrusage(RUSAGE_SELF, &before);
            searchSuccessfulFlag = linearSearch(targetForSearch, listAsArray, listSize);
            getrusage(RUSAGE_SELF, &after);
            searchTime = calculate(&before, &after);
            listSearchedFlag = 1;
        }
        if (listSearchedFlag)
        {
            printf("SEARCH TIME: %.4F\n", searchTime);
        }
        if (randomizerChoice == 1)
        {
            getrusage(RUSAGE_SELF, &before);
            randomizeFile(OUTPUT, inputListSize);
            getrusage(RUSAGE_SELF, &after);
            randomizeTime = calculate(&before, &after);
            listRandomizedFlag = 1;
        }
        if (randomizerChoice == 2)
        {
            getrusage(RUSAGE_SELF, &before);
            randomizedArray = randomize(listAsArray, listSize);
            getrusage (RUSAGE_SELF, &after);
            randomizeTime = calculate(&before, &after);
            listRandomizedFlag = 1;
        }
        if (listRandomizedFlag)
        {
            printf("RANDOMIZE TIME: %.4f\n", randomizeTime);
        }
        if (outputFileNeededFlag)
        {
            //sorted list is printed to a files
            if (!overwriteInputFlag)
            {
                OUTPUT = fopen(outputName, "w");
                if (OUTPUT == NULL)
                {
                    printf("Could not create output file.\n");
                    return 1;
                }
            }

            for (int index = 0; index < listSize; index++)
            {
                fprintf(OUTPUT, "%i\n", listAsArray[index]);
            }
            outputOpenedFlag = 1;
            outputFileNeededFlag = 0;
        }

        //find total time
        totalTime += listSizingTime;
        totalTime += arrayCreationTime;
        totalTime += arraySortingTime;
        totalTime += searchTime;
        totalTime += randomizeTime;
        printf("TOTAL TIME: %.4f\n", totalTime);

        if (listSearchedFlag)
        {
            if (searchSuccessfulFlag)
            {
                printf("%i was found in the list!\n", targetForSearch);
            }
            else if (!searchSuccessfulFlag)
            {
                printf("%i was NOT found in the list.\n", targetForSearch);
            }
        }

        //reset times
        arraySortingTime = 0.0;
        arrayCreationTime = 0.0;
        searchTime = 0.0;
        randomizeTime = 0.0;
        totalTime = 0.0;

        //reset choice options
        menuChoice = 0;
        sortChoice = 0;
        searchChoice = 0;
        randomizerChoice = 0;
        
        //reset misc options
        listSearchedFlag = 0;
        linearFlag = 0;
        sortSelectedFlag = 0;
        searchSelectedFlag = 0;
        targetForSearch = INT_MAX;
        sizeChoice = 0;
        selectionFlag = 0;
        bubbleFlag = 0;
        mergeFlag = 0;
        listRandomizedFlag = 0;

        if(overwriteInputFlag)
        {
            fclose(OUTPUT);
            outputOpenedFlag = 0;
            inputListSize = 0;
            overwriteInputFlag = 0;
        }
    }

    printf("\nSee you next time!!\n");

    //cant have a memory leak!
    if(arrayCreatedFlag)
    {
        free(listAsArray);
    }

    if (outputOpenedFlag)
    {
        fclose(OUTPUT);
    }
    fclose(INPUT);
    free(outputName);
    return 0;
}



