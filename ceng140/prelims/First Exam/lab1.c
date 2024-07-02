#include <stdio.h>
#include "lab1.h"

void hello_ceng140(int course_count, float cgpa, char letter_grade){
  printf("I'm taking %d courses this semester. I would like to get an %c from Ceng140 and have a %.2f CGPA in total.", course_count, letter_grade, cgpa);
}

void grade_effect_calculator(){
  float weight;
  char letter_grade; int course_credit;
  
  scanf("%c %d", &letter_grade, &course_credit);

  switch (letter_grade){
    case 'A':
      weight = 4.0; break;
    case 'B':
      weight = 3.5; break;
    case 'C':
      weight = 2.0; break;
    case 'D':
      weight = 1.5; break;
    case 'F':
      weight = 0.5; break;
  }

  printf("%.2f", weight * course_credit);

}

void sum_of_digits(){
  int sum = 0, i = 10;
  int input_int;
  
  scanf("%d", &input_int);

  while (input_int > 0){
    sum += input_int % i;
    input_int /= 10;
  }

  printf("%d", sum);

}