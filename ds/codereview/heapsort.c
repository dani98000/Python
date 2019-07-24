#include <stdio.h>
#include <unistd.h> /* ssize_t */

#include "sort.h"

void Swap(int *num1, int *num2);
void HeapifyDown(int arr[], size_t n, size_t index,
                 int (*IsData2AboveData)(int data1, int data2));
size_t GetMinMaxChild(int arr[], size_t n, size_t index,
                     int (*IsData2AboveData)(int data1, int data2));

void HeapSort(int arr[], size_t n, enum direction direction)
{
    ssize_t cur_parent = n / 2 - 1; /* set as last parent */
    int (*IsAbove)(int data1, int data2);

    if (ASC == direction)
    {
        /* will build max heap */
        IsAbove = &IsNum2Bigger;
    }
    else
    {
        /* will build min heap */
        IsAbove = &IsNum2Smaller;
    }

    for (; 0 <= cur_parent; --cur_parent)
    {
        HeapifyDown(arr, n, cur_parent, IsAbove);
    }

    while (1 < n)
    {
        --n;
        Swap(arr, arr + n);
        HeapifyDown(arr, n, 0, IsAbove);
    }

}

void HeapifyDown(int arr[], size_t n, size_t index,
                 int (*IsData2AboveData)(int data1, int data2))
{
    int cmp_val = 0;
    size_t max_child = 0;

    do
    {
        max_child = GetMinMaxChild(arr, n, index, IsData2AboveData); /* 0 is invalid child*/

        if (0 < max_child)
        {
            cmp_val = IsData2AboveData(arr[index], arr[max_child]);
        }
        else
        {
            cmp_val = 0;
        }

        if (cmp_val)
        {
            Swap(arr + index, arr + max_child);
            index = max_child;
        }

    }while(cmp_val);
}

void Swap(int *num1, int *num2)
{
    int temp = *num1;

    *num1 = *num2;
    *num2 = temp;
}

size_t LeftChild(size_t index)
{
    return index * 2 + 1;
}

size_t RightChild(size_t index)
{
    return index * 2 + 2;
}


size_t GetMinMaxChild(int arr[], size_t n, size_t index,
                     int (*IsData2AboveData1)(int data1, int data2))
{
    size_t left = LeftChild(index);
    size_t right = RightChild(index);
    int left_val = 0;
    int right_val = 0;

    if (n > left)
    {
        left_val = arr[left];
        
        if (n > right)
        {
            right_val = arr[right];

            return IsData2AboveData1(left_val, right_val) ? right : left;
        }

        return left;
    }

    return 0;
}
