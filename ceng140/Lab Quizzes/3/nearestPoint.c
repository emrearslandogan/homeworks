#include <stdio.h>
#include <math.h>
/* you can add math library */

int main()
{
    int i;
    int xcoors[10];
    int ycoors[10];
    /* declare your variables */
    int x_point, y_point;
    float min_dist, distance;
    int min_index = 0;

    for (i=0; i<10; i++){
        scanf("%d ", &xcoors[i]);
    }
    
    for (i=0; i<10; i++){
        scanf("%d ", &ycoors[i]);
    }
    
    scanf("%d\n%d", &x_point, &y_point);

    min_dist = sqrt(pow(xcoors[0] - x_point, 2) + pow(ycoors[0] - y_point, 2)); 

    /* implement your loop then */
    for (i = 0; i < 10; i++)
      if (distance = sqrt(pow(xcoors[i] - x_point, 2) + pow(ycoors[0] - y_point, 2)), distance < min_dist){
        min_dist = distance;
        min_index = i;
      }  
  
    printf("P = (%d,%d), nearest point index = %d, distance = %f",x_point, y_point, min_index, min_dist);


    /* print the result */

    return 0;
}