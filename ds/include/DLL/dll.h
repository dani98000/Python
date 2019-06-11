#ifndef _DLL_H
#define _DLL_H

typedef struct DLL dll_t ; 
typedef struct DLLnode *it_t;

/*struct DLLnode               
{
	void *data;
	sturct node *next;
	sturct node *prev;
};*/

typedef int (*cmp_f)(const void *data, const void *key, const void *params); 
/* arg (pointer to an argument) is optional, could be NULL */
typedef int (*act_f)(void *data, const void *arg);  
/*0 FOR SUCCES */

dll_t *DLLCreate();
void DLLDestroy(dll_t *dll);
size_t DLLSize(const dll_t *dll);
int DLLIsEmpty(const dll_t *dll); /* 1 For Empty */
it_t DLLBegin(const dll_t *dll); 
it_t DLLEnd(const dll_t *dll);
it_t DLLNext(const it_t iter); /* do not pass DLLEnd ("end of dll") as 'iter' */
it_t DLLPrev(const it_t iter); /* do not pass DLLEnd ("end of dll") as 'iter' */
int IsSameIter(const it_t iter1,const it_t iter2);
void *DLLGetData(const it_t iter);
it_t DLLInsert(dll_t *dll, it_t iter, const void *data); 
it_t DLLErase(it_t where);  /*returns the node after the one removed*/ 
it_t DLLPushBack(dll_t *dll, const void *data);
it_t DLLPushFront(dll_t *dll, const void *data);
void DLLPopBack(dll_t *dll);
void DLLPopFront(dll_t *dll);
int DLLForEach(it_t from, it_t to, act_f action, void* params);
/* returns 0 on success */
it_t DLLFind(it_t from, it_t to, cmp_f compare, void* params, void* data);
/* returns to if not found */

void DLLSpliceBefore(it_t where, it_t from, it_t to);
/*err return val of a func which returns an iter should be the end_iter*/

#endif
