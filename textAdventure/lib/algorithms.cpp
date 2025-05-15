//Program Written By: Jourdan Rampoldi//
//File: algorithms.cpp                //
////////////////////////////////////////
#include <algorithms.h>

void Algorithms::quickSort(Item* list[], int length)
{
    recQuickSort(list, 0, length - 1);
}

int Algorithms::partition(Item* list[], int first, int last)
{
    std::string pivot;
    int smallIndex;

    swap(list, first, (first + last) / 2);

    pivot = list[first]->getName();;
    smallIndex = first;
    
    for (int index = first + 1; index <= last; index++)
        if (list[index]->getName() < pivot)
        {
            smallIndex++;
            swap(list, smallIndex, index);
        }
    swap(list, first, smallIndex);

    return smallIndex;
}

void Algorithms::swap(Item* list[], int a, int b)
{
    Item* temp = list[a];
    list[b] = list[a];
    list[a] = temp;
}

void Algorithms::recQuickSort(Item* list[], int first, int last)
{
    int pivot;
    if (first < last)
    {
        pivot = partition(list, first, last);
        recQuickSort(list, first, pivot - 1);
        recQuickSort(list, pivot + 1, last);
    }
}

int Algorithms::binarySearch(Item* list[], int length, std::string item)
{
    int first = 0;
    int last = length - 1;
    int mid;

    bool found = false;


    while (first <= last && !found)
    {
        mid = (first + last) / 2;

        if (list[mid]->getName() == item)
            found = true;
        else if (list[mid]->getName() > item)
            last = mid - 1;
        else
            first = mid + 1;
    }
    if (found)
        return list[mid]->getMatchKey();
    else
        return -1;
}