#include "vector.h"

int *Int_Box(int x) {
  int *data=malloc(sizeof(*data));
  *data=x;
  return data;
}

int Int_Unbox(void *x) {
  return *(int*)x;
}

void Int_Print(void *data) {
  printf("%d ",Int_Unbox(data));
}

void Int_Destroy(void *data) {
  free(data);
  data=NULL;
}

int main(int argc, char **argv) {

  size_t n=3;

  Vector *a=Vector_Create(n,Int_Print,Int_Destroy);
  for(size_t i=0;i<n;i++) {
    Vector_Append(a,Int_Box(i));
  }
  Vector_Print(a);

  return 0;
}
