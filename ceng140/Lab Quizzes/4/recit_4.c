#include <stdio.h>
#include "recit_4.h"


int combinations(int n, int k){
  printf("(%d %d)\n",n,k);
  if (k == 0)
    return 1;
  
  else
    return (n/k) * combinations(n-1, k-1);
    
  
}

double sine(double x, int iter){

}