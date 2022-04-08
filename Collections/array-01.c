#define ARRAY_IMPLEMENTATION
#include "array.h"

void IntDataDestroy(void *data);
void IntDataPrint(void *data);
int *WrapInt(int x);
int UnwrapInt(void *x);

void IntDataDestroy(void *data) {
  free(data);
  data=NULL;
}

void IntDataPrint(void *data) {
  printf("%d ",*(int*)data);
}

int *IntWrap(int x) {
  int *y=malloc(sizeof(*y));
  *y=x;
  return y;
}

int IntUnwrap(void *x) {
  return *(int*)x;
}

int main() {

//*

  Array *a=Array_Create(5,IntDataDestroy,IntDataPrint);

  for(int i=0;i<10;i++) {
    Array_Append(a,IntWrap(i));
    Array_Print(a);
  }
  printf("\n");

  for(int i=0;i<10;i++) {
    Array_Remove(a,0);
    Array_Print(a);
  }  
  printf("\n");

  for(int i=0;i<10;i++) {
    Array_Prepend(a,IntWrap(i));
    Array_Print(a);
  }  
  printf("\n");
  
  for(int i=0;i<10;i++) {
    Array_Set(a,i,IntWrap(i));
    Array_Print(a);
  }  
  printf("\n");

  for(int i=0;i<10;i++) {
    printf("%d ",IntUnwrap(Array_Get(a,i)));
  }  
  printf("\n");

  Array_Destroy(a);

//*/

  int n=3;

  a=Array_Create(n,ArrayDataDestroy,ArrayDataPrint);
  for(int k=0;k<n;k++) {
    Array_Append(a,Array_Create(n,ArrayDataDestroy,ArrayDataPrint));
    for(int j=0;j<n;j++) {
      Array_Append(Array_Get(a,k),Array_Create(n,IntDataDestroy,IntDataPrint));    
      for(int i=0;i<n;i++) {
        Array_Append(Array_Get(Array_Get(a,k),j),IntWrap(i+j*n+k*n*n));    
      }         
    }    
  }

  Array_Print(a);

  Array_Destroy(a);
    
  return 0;

}
