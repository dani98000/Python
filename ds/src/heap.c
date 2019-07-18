/********************************
*   Author  : Daniel Maizel      *
*   Date    : 18/07/2019         *
*   Reviewer: Sasha              *
*                                *
*********************************/

#include <stdlib.h>/* malloc */
#include <assert.h>/* assert.h */

#include "heap.h" /* My header file */
#include "dvec.h" /* My header file */

#define SIZE 4
#define PARENT(i) (i - 1)/2 
#define LEFT(i) 2*i+1
#define RIGHT(i) 2*i+2

struct heap
{
	dvec_t *vector;
	int (*IsData2BeforeData1)(const void *data1, const void *data2, const void *params);
};

static void PrintHeap(heap_t *heap);
static void DownwordHeapify(heap_t *heap, int index);
static void UpwordHeapify(heap_t *heap, int index);
static void Swap(void **x, void **y);
static int Check_Largest_Child(heap_t *heap, int i);

heap_t *HeapCreate(int (*IsData2BeforeData1)(const void *data1, const void *data2, const void *params))
{
   heap_t *arr = NULL;

   assert(IsData2BeforeData1);

   arr = (heap_t *)malloc(sizeof(heap_t));
   if (NULL == arr)
   {
      return NULL;
   }

   arr->vector = DVECCreate(sizeof(void *), SIZE);
   if(NULL == arr->vector)
   {
      free(arr);

      return NULL;
   }

   arr->IsData2BeforeData1 = IsData2BeforeData1;

   return arr;
}

void HeapDestroy(heap_t *heap)
{
   assert(heap);

   PrintHeap(heap);
   printf("\n");
   DVECDestroy(heap->vector);
   free(heap);
}

int HeapPush(heap_t *heap, void *data)
{
   int status = 0;

   assert(heap);

   status = DVECPushBack(heap->vector, &data);

   if(HeapSize(heap) > 0)
   {
      UpwordHeapify(heap ,HeapSize(heap) - 1);
   }

   return status;
}

/* returns the root of the heap.
   Behavior is undefined if the heap is empty
   heap must not be null */
void *HeapPeek(const heap_t *heap)
{
   assert(heap);

   return *(void **)(DVECGetItemAddress(heap->vector, 0));
}

void HeapPop(heap_t *heap)
{
   void *root = NULL;
   void *last_element = NULL;
  
   assert(heap);

   root = DVECGetItemAddress(heap->vector, 0);
   last_element = DVECGetItemAddress(heap->vector, HeapSize(heap) - 1);
   Swap(root, last_element);
   DVECPopBack(heap->vector);
   DownwordHeapify(heap, 0);
}

/* heap must not be NULL. IsData2BeforeData1 function returns
   1 if data needs to be removed, Otherwise returns
   0. IsData2BeforeData1 must not be NULL. */

int HeapRemove(heap_t *heap, int (*ShouldRemove)(const void *data, const void *key, const void *params), const void *key)
{
   void *current = NULL;
   void *last_element = NULL;
   void *parent = NULL;
   int res = 0;
   int i = 0;
   int size = 0;
   int flag = 0;

   assert(heap);
   assert(ShouldRemove);

   size = HeapSize(heap) - 1;
   last_element = DVECGetItemAddress(heap->vector, size);

   while(flag == 0)
   {
      current = DVECGetItemAddress(heap->vector, i);
      res = ShouldRemove(key, *(void **)current, NULL);

      if (res)
      {
         Swap(current, last_element);
         DVECPopBack(heap->vector);
         parent = DVECGetItemAddress(heap->vector, PARENT(i));

         if(heap->IsData2BeforeData1(*(void **)current, *(void **)parent, NULL))
         {
            UpwordHeapify(heap, i);
         }
         else
         {
            DownwordHeapify(heap, i);
         }
         flag = 1;

         return 1;
      }
      else
      {
         ++i;
      }
   }

   return 0;
}
            
size_t HeapSize(const heap_t *heap)
{
   return DVECSize(heap->vector);
}

int HeapIsEmpty(const heap_t *heap)
{
   assert(heap);

   return (DVECSize(heap->vector) == 0);
}

static void DownwordHeapify(heap_t *heap, int index)
{
   int l_index = 0;
   int r_index = 0;
   int largest = index;
   int res= 0;
   void *left_child = NULL;
   void *right_child = NULL;
   void *current = NULL;
   size_t i = index;

   assert(heap);
   
   while (i < HeapSize(heap))
   {
      largest = Check_Largest_Child(heap, i);
      if(largest != i)
      {
         Swap(DVECGetItemAddress(heap->vector, i), DVECGetItemAddress(heap->vector, largest));
         i = largest;
      }
      else
      {
         break;
      }
   }
}

static void UpwordHeapify(heap_t *heap, int index)
{
   int side = 0;
   int res = 0;
   void *child = NULL;
   void *parent = NULL;
   int i = index;
   int flag = 0;

   while(i > 0 && flag == 0)
   {
      child = DVECGetItemAddress(heap->vector, i);
      parent = DVECGetItemAddress(heap->vector, PARENT(i));

      res = heap->IsData2BeforeData1(*(void **)child, *(void **)parent, NULL);
      if (res > 0)
      {
         Swap(child, parent);
      }
      else
      {
         flag = 1;
      }
      i = PARENT(i);
   }
}

static void Swap(void **x, void **y)
{
   void *temp = *y;
   *y = *x;
   *x = temp;
}

static void PrintHeap(heap_t *heap)
{
   void *current = NULL;
   int i = 0;
   int size = 0;

   assert(heap);

   size = HeapSize(heap) - 1;

   for(; i <= size; ++i)
   {
      current = DVECGetItemAddress(heap->vector, i);
      printf("%d->",**(int **)current);
   }
}

static int Check_Largest_Child(heap_t *heap, int i)
{
   void *current = DVECGetItemAddress(heap->vector, i);   
   void *left_child = NULL;
   void *right_child = NULL;
   int l_index = LEFT(i);
   int r_index = RIGHT(i);
   int largest = i;
   int res = 0;

   if(l_index < HeapSize(heap))
   {
      left_child = DVECGetItemAddress(heap->vector, l_index);
      res = heap->IsData2BeforeData1(*(void **)left_child, *(void **)current, NULL);
      if(res > 0 )
      {
         largest = l_index;
      }   
   }

   current = DVECGetItemAddress(heap->vector, largest);
   if(r_index < HeapSize(heap))
   {
      right_child = DVECGetItemAddress(heap->vector, r_index);
      res = heap->IsData2BeforeData1(*(void **)right_child, *(void **)current, NULL);
      if(res > 0 && heap->IsData2BeforeData1(*(void **)right_child, *(void **)left_child, NULL))
      {
         largest = r_index;
      }
   }

   return largest;
}