#include "algos.h"

#undef getrusage

//TODOS
//fix scanf nonnumeric char infinite loop bug
//implement linear and binary search
//make program continue until exited
//implement randomize list function
//make more sorting functions!

//--------------------------------------------------------------------------------------------------------------------
//This program takes a path to a file of a list of numbers as an arguement, and gives the user options to sort the
//numbers or search for numbers within the file.The user may also randomize the list.The sorted list will be printed
//to an output file. Program will remain open until the user decides to exit.
//--------------------------------------------------------------------------------------------------------------------


int main(int argc, char* argv[])
{
    int listChoice = 0;
    int* sortedArray = NULL;
    int listSize = 0;
    int sortChoice = 0;
    FILE* INPUT = NULL;
    FILE* OUTPUT = NULL;

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


    //prompt user if they would like to search or sort a list of numbers, or exit
    printf("\nPlease select an option below:\n1) Sort a list\n");
    printf("2) Search for a number in a list\n3) Exit\n\nSelection: ");

    while(listChoice < 1 || listChoice > 3)
    {
        getInput(&listChoice);
    }

    if (listChoice == 1)//user selected Sort
    {
        //user is prompted by a menu with sort options
        printf("\nSelect one of the sorting options\n1) Selection sort\n");
        printf("2) Bubble sort\n3) Merge sort\n\nChoice: ");
        while (sortChoice < 1 || sortChoice > 3)
        {
            getInput(&sortChoice);
        }


        //list is sorted, some type of data structure is created
        if (sortChoice == 1)//selection sort!
        {
            getrusage(RUSAGE_SELF, &before);//time before
            listSize = findListSize(INPUT);
            getrusage(RUSAGE_SELF, &after);//time after
            listSizingTime = calculate(&before, &after);

            getrusage(RUSAGE_SELF, &before);
            int* listAsArray = createArray(INPUT, listSize);
            getrusage(RUSAGE_SELF, &after);
            arrayCreationTime = calculate(&before, &after);

            getrusage(RUSAGE_SELF, &before);
            sortedArray = selectionSort(listAsArray, listSize);
            getrusage(RUSAGE_SELF, &after);
            arraySortingTime = calculate(&before, &after);
        }
        else if (sortChoice == 2)//bubble sort!
        {
            getrusage(RUSAGE_SELF, &before);
            listSize = findListSize(INPUT);
            getrusage(RUSAGE_SELF, &after);
            listSizingTime = calculate(&before, &after);

            getrusage(RUSAGE_SELF, &before);
            int* listAsArray = createArray(INPUT, listSize);
            getrusage(RUSAGE_SELF, &after);
            arrayCreationTime = calculate(&before, &after);

            getrusage(RUSAGE_SELF, &before);
            sortedArray = bubbleSort(listAsArray, listSize);
            getrusage(RUSAGE_SELF, &after);
            arraySortingTime = calculate(&before, &after);
        }
        else if (sortChoice == 3)//merge sort!
        {
            getrusage(RUSAGE_SELF, &before);
            listSize = findListSize(INPUT);
            getrusage(RUSAGE_SELF, &after);
            listSizingTime = calculate(&before, &after);

            getrusage(RUSAGE_SELF, &before);
            int* listAsArray = createArray(INPUT, listSize);
            getrusage(RUSAGE_SELF, &after);
            arrayCreationTime = calculate(&before, &after);

            getrusage(RUSAGE_SELF, &before);
            sortedArray = mergeSort(listAsArray, listSize);
            getrusage(RUSAGE_SELF, &after);
            arraySortingTime = calculate(&before, &after);
        }

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

        //time of sort printed back to user to show success
        char* time = "Time to";
        listSizingTime != 0.0 ? printf("%s size array:    %.4f seconds\n", time, listSizingTime): printf("");
        arrayCreationTime != 0.0 ? printf("%s create array: %.4f seconds\n", time, arrayCreationTime): printf("");
        arraySortingTime != 0.0 ? printf("%s sort array:    %.4f seconds\n", time, arraySortingTime): printf("");
        double totalTime = (listSizingTime + arrayCreationTime + arraySortingTime);
        printf("Total Time: %.4f seconds\n", totalTime);

        //user is prompted if they would like to search for a number from sorted list

    }



    //if user selects search
        //use linear search to find item, and print time back to user

    //if user selects exit, exit.
    if (listChoice == 3)
    {
        printf("\nSee you next time!!\n");
        return 1;
    }

    //cant have a memory leak!
    free(sortedArray);
    fclose(OUTPUT);
    fclose(INPUT);
}



