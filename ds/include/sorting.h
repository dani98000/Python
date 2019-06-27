/************************
Sorting algorithms iterative implementation
*************************/
#ifndef SORTS_H
#define SORTS_H

#include <stdlib.h> /* size_t */

/*
Compare  < 0 *data1 goes before *data2
Compare == 0 *data1 is equivalent to *data2
Compare  > 0 *data1 goes after *data2
*/
typedef int (*cmp_f)(const void *data1, const void *data2);

void InsertionSort(void *base, size_t n_elements, size_t element_size, cmp_f Compare);
void BubbleSort(void *base, size_t n_elements, size_t element_size, cmp_f Compare);
void SelectionSort(void *base, size_t n_elements, size_t element_size, cmp_f Compare);



#endif
