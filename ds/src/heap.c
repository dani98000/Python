
#include <stdlib.h>
#include <assert.h>

#include "heap.h" /* My header file */
#include "dvec.h" /* My header file */


#define SIZE 4
#define PARENT(i) (i - 1)/2 
#define LEFT(i) 2*i+1
#define RIGHT(i) 2*i+2

enum side{LEFT, RIGHT};

struct heap
{
	dvec_t *vector;
	int (*Compare)(const void *data1, const void *data2);
};

/* Compare function returns positive, 0, or negative
   integer, if data1 > data2, data1 = data2 or
   data1 < data2, respectively. Compare must not be NULL.
   Create returns an initialized heap on success
   and NULL on failure */

static void DownwordHeapify(heap_t *heap, int index);
static void UpwordHeapify(heap_t *heap);
static void Swap(void **x, void **y);

heap_t *HeapCreate(int (*Compare)(const void *data1, const void *data2))
{
   heap_t *arr = NULL;

   assert(Compare);

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

   arr->Compare = Compare;

   return arr;
}

void HeapDestroy(heap_t *heap)
{
   assert(heap);

   DVECDestroy(heap->vector);
   free(heap);
}

/* heap must not be null.r eturns 0
   on success, 1 on failure */
int HeapPush(heap_t *heap, void *data)
{
   int status = 0;

   assert(heap);

   status = DVECPushBack(heap->vector, &data);
   if(HeapSize(heap) > 0)
   UpwordHeapify(heap);

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

/* heap must not be NULL. Compare function returns
   1 if data needs to be removed, Otherwise returns
   0. Compare must not be NULL. */

void Remove(heap_t *heap, 
            int (*Compare)(const void *data, const void *args),
            void *args)
{
   void *left_child = NULL;
   void *right_child = NULL;
   void *current = NULL;
   int res = 0;

   assert(heap);
   assert(Compare);

   while(flag == 0)
   {

      res = Compare(*(void **)left_child, *(void **)current);

   }
}
            
/* heap must not be NULL */
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
   int l = 0;
   int r = 0;
   int largest = 0;
   int res= 0;
   void *left_child = NULL;
   void *right_child = NULL;
   void *current = NULL;
   int i = index;

   assert(heap);
   
   while (i < HeapSize(heap))
   {
      left_child = DVECGetItemAddress(heap->vector, LEFT(i));
      right_child = DVECGetItemAddress(heap->vector, RIGHT(i));
      current = DVECGetItemAddress(heap->vector, i);
      l = LEFT(i);
      r = RIGHT(i);

      res = heap->Compare(*(void **)left_child, *(void **)current);

      if(l < HeapSize(heap) && res > 0)
      {
         largest = l;
      }
      else
      {
         largest = i;
      }

      current = DVECGetItemAddress(heap->vector, largest);
      res = heap->Compare(*(void **)right_child, *(void **)current);

      if(r < HeapSize(heap) && res > 0)
      {
         largest = r;
      }
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

static void UpwordHeapify(heap_t *heap)
{
   int last = HeapSize(heap) - 1;
   int side = 0;
   int res = 0;
   void *child = NULL;
   void *parent = NULL;
   int i = last;
   int flag = 0;

   while(i > 0 && flag == 0)
   {
      child = DVECGetItemAddress(heap->vector, i);
      parent = DVECGetItemAddress(heap->vector, PARENT(i));

      res = (heap->Compare(*(void **)child, *(void **)parent));
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