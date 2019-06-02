/*******************************************************************************
* Programmer: Eldad
* dvec
* File: dvec code
* Date: 30-05-2019 18:08:19
*******************************************************************************/

#include <assert.h>         /* assert */
#include <stdio.h> 	        /* printf */
#include <stdlib.h>         /* EXIT_SUCCESS EXIT_FAILURE malloc realloc */
#include <string.h>         /* strcat, strlen, strcpy */

#include "../../include/DVEC/dvec.h"

#define GROW (2)            /* dvec growth factor */

struct Dvec
{
    void *data;
    size_t size_of_element;
    size_t num_elements;
    size_t capacity;    
}; 

dvec_t *DVECCreate(size_t size_of_element, size_t num_elements)
{
    dvec_t *dvec = NULL;
    
    assert ((0 < size_of_element) && (0 < num_elements));
    
    dvec = (dvec_t *)malloc(sizeof(dvec_t));
    if (NULL == dvec)
    {
        return (NULL);
    }     
    
    dvec->size_of_element = size_of_element;
    dvec->num_elements    = 0;
    dvec->capacity        = num_elements;
    
    dvec->data = (void *)malloc(num_elements * size_of_element);
    if (NULL == dvec->data)
    {
        free(dvec);
        return (NULL);       
    }
    
    return (dvec);
}

void DVECDestroy(dvec_t *dvec)
{
    assert(NULL != dvec);
    
    free(dvec->data);
    dvec->data = NULL;
    free(dvec);
}

int DVECPushBack(dvec_t *dvec, const void *element)
{
    void *data_tmp = NULL;
    
    assert(NULL != dvec);
    assert(NULL != element);    
    
    data_tmp = dvec->data;
    
    memcpy(((char *)data_tmp + (dvec->num_elements * dvec->size_of_element)), 
                                                element, dvec->size_of_element);
    ++dvec->num_elements;
    
    if (dvec->num_elements == dvec->capacity)
    {             
        data_tmp = (char *)realloc(data_tmp, 
                                 dvec->capacity * dvec->size_of_element * GROW);
        if (NULL == data_tmp)
        {
            return (1);
        }
        
        dvec->capacity *= GROW;
        dvec->data = data_tmp;                                                                                 
    }
   
    return (0);
}

void DVECPopBack(dvec_t *dvec)
{
    void *data_tmp = NULL;
    
    assert(NULL != dvec);
    
    data_tmp = dvec->data;
    
    --dvec->num_elements;        
    
    if ((dvec->capacity >> GROW) >= dvec->num_elements)
    {
        data_tmp = (void *)realloc(data_tmp, (dvec->capacity / GROW) 
                                                       * dvec->size_of_element);
        if (NULL == data_tmp)
        {
            return;
        } 
        
        dvec->capacity /= GROW;
        dvec->data = data_tmp;                                                      
    }
}

void *DVECGetItemAddress(dvec_t *dvec, size_t index)
{
    assert(NULL != dvec);
        
    return ((char *)dvec->data + dvec->size_of_element * index);
}

size_t DVECSize(const dvec_t *dvec)
{
    assert(NULL != dvec);
    
    return (dvec->num_elements);
}

size_t DVECCapacity(const dvec_t *dvec)
{
    assert(NULL != dvec);
    
    return (dvec->capacity);
}

int DVECReserve(dvec_t *dvec, size_t new_capacity)
{
    void *data_tmp = NULL;
    
    assert(NULL != dvec);
    
    data_tmp = dvec->data;
    
    if (dvec->num_elements >= new_capacity)
    {
        data_tmp = (void *)realloc(data_tmp, 
                              dvec->size_of_element * (dvec->num_elements + 1));
        if (NULL == data_tmp)
        {
            return (1);
        }
        
        dvec->capacity = dvec->num_elements + 1;
        dvec->data = data_tmp;
        
        return (0);
    }
    else
    {
        data_tmp = (void *)realloc(data_tmp, dvec->size_of_element 
                                                                * new_capacity);
        if (NULL == data_tmp)
        {
            return (1);
        }
        
        dvec->capacity = new_capacity;
        dvec->data = data_tmp;
        
        return (0);
    }
        
        dvec->capacity = dvec->num_elements + 1;            
}

