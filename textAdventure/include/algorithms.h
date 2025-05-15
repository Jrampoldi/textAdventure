//Program Written By: Jourdan Rampoldi//
//File: algorithms.h                  //
////////////////////////////////////////
#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <item.h>

class Algorithms
{
    public:
        static void quickSort(Item* list[], int length);
        //function will call determine first index and last index
        //from provided length of provided list. Will then 
        //call recQuickSort.

        static void recQuickSort(Item* list[], int first, int last);
        //Function will use recursion to sort list also calling 
        //upon partition to find pivot index.

        static int partition(Item* list[], int first, int last);
        //function will partition list elements based on name value
        //and return index of element in correct position.

        static void swap(Item* list[], int a, int b);
        //swap takes in two indecies, along with the array
        //and will swap the two elements using the provided
        //index.

        static int binarySearch(Item* list[], int length, std::string item);
        //function uses the binary search method to search for given item name
        //in the provided list of items.
};

#endif