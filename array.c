#define ARRAY_IMPLEMENTATION
#include "array.h"

void ArrayArray_Destroy(size_t n,Array *a) {
  
  if(n>0) {
    for(size_t i=0;i<a->length;i++) { 
      ArrayArray_Destroy(n-1,Array_Get(a,i));
    }    
  }

  Array_Destroy(a);

}

int main() {

/*

  Array *a=Array_Create(5,IntDataDestroy,IntDataPrint);

  for(int i=0;i<10;i++) {
    Array_Append(a,WrapInt(i));
    Array_Print(a);
  }
  printf("\n");

  for(int i=0;i<10;i++) {
    Array_Remove(a,0);
    Array_Print(a);
  }  
  printf("\n");

  for(int i=0;i<10;i++) {
    Array_Prepend(a,WrapInt(i));
    Array_Print(a);
  }  
  printf("\n");
  
  for(int i=0;i<10;i++) {
    Array_Set(a,i,WrapInt(i));
    Array_Print(a);
  }  
  printf("\n");

  for(int i=0;i<10;i++) {
    printf("%d ",UnwrapInt(Array_Get(a,i)));
  }  
  printf("\n");

  Array_Destroy(a);

//*/

  int n=3;

  Array *a=Array_Create(n,IntDataDestroy,IntDataPrint);

  for(int k=0;k<n;k++) {
    Array_Append(a,Array_Create(n,IntDataDestroy,IntDataPrint));
    for(int j=0;j<n;j++) {
      Array_Append(Array_Get(a,k),Array_Create(n,IntDataDestroy,IntDataPrint));    
      for(int i=0;i<n;i++) {
        Array_Append(Array_Get(Array_Get(a,k),j),WrapInt(i+j*n+k*n*n));    
      }         
    }    
  }

  for(int k=0;k<n;k++) {
    for(int j=0;j<n;j++) {
      for(int i=0;i<n;i++) {
        printf("%d ",UnwrapInt(Array_Get(Array_Get(Array_Get(a,k),j),i)));    
      }
      printf("\n");         
    }    
    printf("\n");
  }
  printf("\n");

  ArrayArray_Destroy(3,a);
    
  return 0;

}
