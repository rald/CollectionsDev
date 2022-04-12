#ifndef ARRAY_H
#define ARRAY_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct Array Array;

typedef void Array_DataDestroyCallback(void **data);
typedef void Array_DataPrintCallback(void *data);

struct Array {
  void **data;
  size_t capacity;
  size_t length;
  Array_DataDestroyCallback *destroy; 
  Array_DataPrintCallback *print; 
}; 

Array *Array_Create(size_t capacity,Array_DataDestroyCallback destroy,Array_DataPrintCallback print);
void Array_Destroy(Array **array);
void Array_Set(Array **array,size_t index,void *value);
void *Array_Get(Array *array,size_t index);
void Array_Append(Array **array,void *value);
void Array_Prepend(Array **array,void *value);
void Array_Insert(Array **array,size_t index,void *value);
void Array_Remove(Array **array,size_t index);
void Array_Print(Array *array);
void ArrayDataDestroy(void **array);
void ArrayDataPrint(void *array);

#ifdef ARRAY_IMPLEMENTATION

Array *Array_Create(size_t capacity,Array_DataDestroyCallback destroy,Array_DataPrintCallback print) {
  Array *array=malloc(sizeof(*array));
  if(array!=NULL) {
    array->data=malloc(sizeof(*(array->data))*capacity);
    array->capacity=capacity;
    array->length=0;
    array->destroy=destroy;
    array->print=print;
  }
  return array;
}

void Array_Destroy(Array **array) {
  for(size_t i=0;i<(*array)->length;i++) {
    (*array)->destroy(&((*array)->data[i]));
  }
  free(*array);
  (*array)=NULL;
}

void Array_Set(Array **array,size_t index,void *value) {
  assert(index < (*array)->length);
  (*array)->destroy(&((*array)->data[index]));
  (*array)->data[index]=value;
}

void *Array_Get(Array *array,size_t index) {
  assert(index < array->length);
  return array->data[index];
}

void Array_Append(Array **array,void *value) {
  if((*array)->capacity==(*array)->length) {
    (*array)->capacity++;;
    (*array)->data=realloc((*array)->data,sizeof(*((*array)->data))*((*array)->capacity));
  }
  (*array)->data[(*array)->length++]=value;
}

void Array_Prepend(Array **array,void *value) {
  if((*array)->capacity==(*array)->length) {
    (*array)->capacity++;
    (*array)->data=realloc((*array)->data,sizeof(*((*array)->data))*((*array)->capacity));
  }
  for(size_t i=(*array)->length;i>0;i--) {
    (*array)->data[i]=(*array)->data[i-1];
  }
  (*array)->data[0]=value;
  (*array)->length++;
}

void Array_Insert(Array **array,size_t index,void *value) {
  if((*array)->capacity==(*array)->length) {
    (*array)->capacity++;
    (*array)->data=realloc((*array)->data,sizeof(*((*array)->data))*(*array)->capacity);
  }
  (*array)->length++;
  for(size_t i=(*array)->length-1;i>index;i--) {
    (*array)->data[i]=(*array)->data[i-1];
  }
  (*array)->data[index]=value;
}

void Array_Remove(Array **array,size_t index) {
  assert(index < (*array)->length);
  (*array)->destroy((*array)->data[index]);
  for(size_t i=index;i<(*array)->length-1;i++) {
    (*array)->data[i]=(*array)->data[i+1];
  }
  (*array)->length--;  
}

void Array_Print(Array *array) {
  for(size_t i=0;i<array->length;i++) {
    array->print(array->data[i]);
  }
  printf("\n");
}

void ArrayDataDestroy(void **array) {
  for(size_t i=0;i<((Array*)(*array))->length;i++) {
    Array_Destroy(((Array*)(*array))->data[i]);
  }
}

void ArrayDataPrint(void *array) {
  for(size_t i=0;i<((Array*)array)->length;i++) {
    Array_Print(((Array*)array)->data[i]);
  }
}

#endif /* ARRAY_IMPLEMENTATION  */

#endif /* ARRAY_H  */
