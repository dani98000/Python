#include <stdio.h>
#include <math.h>

#include "sort.h"

static int BinarySearchDirected(const int arr[], int key, size_t n, size_t *index, 
                         int (*compare)(int num1, int num2));

static int CompareIntAscending(int num1, int num2)
{
    /* returns negative if num1 is before num2, 0 if equal, 1 otherwise */
    return num1 - num2;
}

static int CompareIntDescending(int num1, int num2)
{
    /* returns negative if num1 is before num2, 0 if equal, 1 otherwise */
    return num2 - num1;
}

static int IsAscending(const int arr[], size_t n)
{
    /* returns 1 if descending array, otherwise returns 0 */
    while (0 < n-1 && !(arr[n-1] < arr[n-2]))
    {
       if (arr[n-1] > arr[n-2])
        {
            return 1;
        }
        --n;
    }

    return 0;
}

/*** JUMP SEARCH ***/
int JumpSearch(const int arr[], int key, size_t n, size_t *index)
{
    size_t sq = sqrt(n);
    size_t i = -1;
    int cmp_val = -1;
    int (*compare)(int num1, int num2);
    int iterations = 0;

    if (IsAscending(arr, n))
    {
        compare = CompareIntAscending;
    }
    else
    {
        compare = CompareIntDescending;
    }

    for (iterations = sq; iterations && 0 > cmp_val; --iterations)
    {
        i += sq;
        cmp_val = compare(arr[i], key);
    }

    if (0 > cmp_val && 0 == iterations)
    {
        i = n - 1;
    }

    for (; 0 < sq; --sq)
    {
        if (key == arr[i])
        {
            *index = i;

            return 1;
        }
        --i;
    }

    return 0;
}

/*** binary search ***/
int BinarySearch(const int arr[], int key, size_t n, size_t *index)
{
    int (*comparefunc)(int num1, int num2) = NULL;

    if (IsAscending(arr, n))
    {
        comparefunc = CompareIntAscending;
    }
    else
    {
        comparefunc = CompareIntDescending;
    }

    return BinarySearchDirected(arr, key, n, index, comparefunc);
}

static int BinarySearchDirected(const int arr[], int key, size_t n, size_t *index, 
                         int (*compare)(int num1, int num2))
{
    size_t mid = n / 2;
    int cmp_val = 0;

    while (0 < n)
    {
        cmp_val = compare(arr[mid], key); /* compare returns negative number if arr[mid] is before key*/

        if (0 == cmp_val)
        {
            *index =  mid;
            return 1;
        }
        else if (0 < cmp_val) /* value is possibly on the left */
        {
            mid -= n / 2;
        }
        else /* value is possibly on the right */
        {
            mid += n % 2;
        }

        n /= 2;
        mid += n / 2;
    }

    return 0;
}