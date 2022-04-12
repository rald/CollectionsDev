#define ARRAY_IMPLEMENTATION
#include "array.h"

void IntDataDestroy(void **data);
void IntDataPrint(void *data);
int *WrapInt(int x);
int UnwrapInt(void *x);

void IntDataDestroy(void **data) {
  free(*data);
  (*data)=NULL;
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

  int n=3;
  
  Array *a=Array_Create(n,IntDataDestroy,IntDataPrint);
  for(int i=0;i<n;i++) {
    Array_Append(&a,IntWrap(i));    
  }         

  Array_Print(a);

  Array_Destroy(&a);

  assert(a == NULL);
    
  return 0;

}
