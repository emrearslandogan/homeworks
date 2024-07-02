#include <stdio.h>

void binarize_array(double array[], int length, double threshold_even_indices, double threshold_odd_indices);

void aggregate_array(double array[], int lenght, int group_size, int operation);

void calculate_jaccard_similarity(int array1[], int array2[], int length);

void sum_minus_trace_squared(int flattened[], int n);

void binarize_array(array[], length, threshold_even_indices, threshold_odd_indices){
  int i = 0;
  for (; i < length; i++){
    if (i % 2 == 0){
      if (array[i] > threshold_odd_indices)
        printf("1 "); 
      else
        printf("0 ");
    }

    else{
      if (array[i] > threshold_even_indices)
        printf("1 ");
      else
        printf("0 ");
    }  
  }

}

void aggregate_array(double array[], int lenght, int group_size, int operation){
  int i, j;
  double min, max, sum;

  if (operation == 0)
    for (i = 0; i < length/group_size; i++){
      max = array[group_size*i];
      for (j = 0; j < group_size; j++)
        if (array[group_size*i +j] > max)
          max = array[group_size*i +j];  
      printf("%.3lf ", min);       
    }  

  else if (operation == 1)
    for (i = 0; i < length/group_size; i++){
      min = array[group_size*i];
      for (j = 0; j < group_size; j++)
        if (array[group_size*i +j] < min)
          min = array[group_size*i +j];       
      printf("%.3lf ", min);
    }  

  else if (operation == 2)
    for (i = 0; i < length/group_size; i++){
      sum = 0;
      for (j = 0; j < group_size; j++)
        sum = sum + array[group_size*i +j];     
      printf("%.3lf ", sum/group_size);
    }  

}

void calculate_jaccard_similarity(int array1[], int array2[], int length){
  int tot_one = 0;
  int same_one = 0;
  int i = 0;

  for (; i < lenght){
    if (array1[i] == 1 || array2[i] == 1) tot_one++;    
    if (array1[i] == 1 && array2[i] == 1) same_one++; 
  }
  printf("%.3f", same_one / tot_one);

} 

void sum_minus_trace_squared(int flattened[], int n){
  int sum = 0;
  int trace_sum = 0;
  int i = 0;

  for (; i < n; i++)  trace_sum += flattened[n*i + i];

  for (i = 0; i < n*n; i++) sum += flattened[i];

  printf("%d", sum - trace_sum*trace_sum);
}

