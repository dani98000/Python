#include <stdio.h>
#include <unistd.h> /* ssize_t */
#include <stdlib.h>
#include <time.h> /* time */
#include <assert.h>

#include "sort.h"

int IsNum2Bigger(int num1, int num2)
{
    return num2 > num1;
}

int IsNum2Smaller(int num1, int num2)
{
    return num2 < num1;
}

void Swap(int *num1, int *num2)
{
    int temp = *num1;

    *num1 = *num2;
    *num2 = temp;
}

size_t Partition(int arr[], size_t n, enum direction direction)
{
    size_t pivot_index = n-1;
    int pivot = arr[pivot_index];
    size_t i = 0;
    size_t edge = 0;

    for(i = 0; i <= pivot_index; ++i)
    {
        if (arr[i] <= pivot) /* pushes all smaller to the left */
        {
            Swap(arr + i, arr + edge);
            ++edge;
        }
    }

    return --edge;
}

void QuickSort(int arr[], size_t n, enum direction direction)
{
    size_t pivot_index;

    assert(NULL != arr);

    if (2 > n)
    {
        return;
    }

    /* srand(clock()); */

    pivot_index = rand() % n;

    Swap(arr + pivot_index, arr + n - 1);

    /* pivot_index = n - 1;*/

    pivot_index = Partition(arr, n, direction);
    QuickSort(arr, pivot_index, direction); /* pivot - index = new size; */
    QuickSort(arr + pivot_index + 1, n - pivot_index - 1, direction);
}