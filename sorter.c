#include "algos.h"

#undef getrusage

//TODOS
//binary search
//make program continue until exited
//implement randomize list function
//make more sorting functions!
//clean this place up, its ugly around here

//--------------------------------------------------------------------------------------------------------------------
//This program takes a path to a file of a list of numbers as an arguement, and gives the user options to sort the
//numbers or search for numbers within the file.The user may also randomize the list.The sorted list will be printed
//to an output file. Program will remain open until the user decides to exit.
//--------------------------------------------------------------------------------------------------------------------


int main(int argc, char* argv[])
{
    //initialize variables 
    int listChoice = 0;
    int listSize = 0;
    int sortChoice = 0;
    int searchChoice = 0;
    int* sortedArray = NULL;
    int* listAsArray = NULL;
    int targetForSearch = INT_MAX;
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
    double totalTime = 0.0;

    while(!exitProgramFlag)//actual program
    {
        //prompt user if they would like to search or sort a list of numbers, or exit
        printf("\nPlease select an option below:\n1) Sort a list\n");
        printf("2) Search for a number in a list\n3) Exit\n\nChoice: ");

        while(listChoice < 1 || listChoice > 3)
        {
            getInput(&listChoice);
        }
        if (listChoice == 1)//user selected Sort
        {
            sortSelectedFlag = 1;
        }
        else if (listChoice == 2)//user selected Search
        {
            searchSelectedFlag = 1;
        }
        else if (listChoice == 3)//user selected Exit
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
                getInput(&sortChoice);
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
                getInput(&targetForSearch);
            }

            printf("How would you like to search?\n");
            printf("\n1) Linear search\n2) Binary Search\n\n");
            printf("Choice: ");
            while (searchChoice < 1 || searchChoice > 2)
            {
                getInput(&searchChoice);
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

        //use flags as instructions for execution
        // if (inputFileNeededFlag)//new file being action'd #TODO
        // {

        // }
        
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
            getrusage(RUSAGE_SELF, &before);
            listSize = findListSize(INPUT);
            getrusage(RUSAGE_SELF, &after);
            listSizingTime = calculate(&before, &after);
            listSizedFlag = 1;
            listToBeSizedFlag = 0;
            printf("SIZING TIME: %.4f\n", listSizingTime);
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
        

        if (outputFileNeededFlag)
        {
            //sorted list is printed to a files
            OUTPUT = fopen("output/sorted.txt", "w");
            if (OUTPUT == NULL)
            {
                printf("Could not create output file.\n");
                return 1;
            }

            for (int index = 0; index < listSize; index++)
            {
                fprintf(OUTPUT, "%i\n", sortedArray[index]);
            }
            outputOpenedFlag = 1;
            outputFileNeededFlag = 0;
        }
        //find total time
        totalTime += listSizingTime;
        totalTime += arrayCreationTime;
        totalTime += arraySortingTime;
        totalTime += searchTime;
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
        searchTime = 0.0;
        totalTime = 0.0;

        //reset choice options
        listChoice = 0;
        sortChoice = 0;
        searchChoice = 0;
        
        //reset misc options
        listSearchedFlag = 0;
        linearFlag = 0;
        sortSelectedFlag = 0;
        searchSelectedFlag = 0;

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
    return 0;
}



