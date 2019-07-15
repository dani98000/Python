#include <stdio.h>


#ifndef MERGE_H
#define MERGE_H

/*
Compare < 0 *data1 goes before *data2
Compare == 0 *data1 is equivalent to *data2
Compare > 0 *data1 goes after *data2
*/
typedef int (*cmp_f)(const void *data1, const void *data2);

void MergeSort(int arr[], int left, int right);

#endif
