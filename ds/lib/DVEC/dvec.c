/********************************
* 	 Author  : Daniel Maizel	*
*	 Date    : 27/05/2019		*
*	 Reviewer:     	*
*								*
*********************************/

#include <string.h> /* memcpy */
#include <stdlib.h> /* malloc */
#include <stdio.h>  /* size_t */
#include <assert.h> /* assert */

#include "../../include/DVEC/dvec.h"

int DVECSizeUp(dvec_t *dvec);
int DVECSizeDown(dvec_t *dvec);

struct Dvec
{
	void *arr;
	size_t size_of_element;
	size_t num_elements;
	size_t capacity;
};

dvec_t *DVECCreate(size_t size_of_element,size_t num_elements) 
{
	dvec_t *dvec = NULL;
	assert(num_elements > 0);
	
	dvec = (dvec_t *)malloc(sizeof(dvec_t));

	if (NULL == dvec)
	{
		return NULL;
	}
	
	dvec->arr = (void *)malloc(dvec->size_of_element * dvec->num_elements);
	if (NULL == dvec->arr)
	{
		return NULL;
	}
	
	dvec->size_of_element = size_of_element;
	dvec->num_elements = 0;

	dvec->capacity = num_elements;
	
	
	return (dvec);
}

void DVECDestroy(dvec_t *dvec)
{
	free(dvec->arr);
	free(dvec);
}

void *DVECGetItemAddress(dvec_t *dvec, size_t index)
{
	if(index > dvec->capacity)
	{
		return NULL;
	}
	
	return((void *)((size_t)dvec->arr + index * dvec->size_of_element));		
}

int DVECPushBack(dvec_t *dvec, const void *element)
{
	size_t dest = 0;
	assert(NULL != dvec);
	
	if(dvec->capacity <= dvec->num_elements) 
	{
		DVECSizeUp(dvec);
	}
	
	dest = (size_t)dvec->arr + dvec->num_elements * dvec->size_of_element;
	memcpy((void*)dest, element, dvec->size_of_element);

	++(dvec->num_elements);
	
	return 0;
}
 
void DVECPopBack(dvec_t *dvec)
{
	assert(NULL != dvec);
	if(dvec->capacity * 0.25 >= dvec->num_elements)
	{
		DVECSizeDown(dvec);
	} 
	
	if(dvec->num_elements > 0)
	{
		--(dvec->num_elements);
	}
}

size_t DVECSize(const dvec_t *dvec)
{
	return(dvec->num_elements);
}

size_t DVECCapacity(const dvec_t *dvec)
{
	return(dvec->capacity);
}

int DVECSizeUp(dvec_t *dvec)
{
		void *temp = NULL;
		size_t new_size = dvec->capacity * 2;
		temp = realloc(dvec->arr, new_size * dvec->size_of_element);
        if(NULL == temp)
        {
            return 1;
        }

        dvec->capacity = new_size;
        dvec->arr = temp;
        return 0;

}
int DVECSizeDown(dvec_t *dvec)
{
		void *temp = NULL;
		size_t new_size = dvec->capacity * 0.5;
		temp = realloc(dvec->arr, new_size * dvec->size_of_element);
        if(NULL == temp)
        {
            return 1;
        }

        dvec->capacity = new_size;
        dvec->arr = temp;
        return 0;
}
/* int DVECReserve(dvec_t *dvec, size_t new_capacity);*/
