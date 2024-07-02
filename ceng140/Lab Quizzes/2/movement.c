#include <stdio.h>

int main(void){
  char direction; int x_coord, y_coord, grid_size;

  scanf("%c %d %d %d", &direction, &x_coord, &y_coord, &grid_size);

  if (direction == 'E'){
    if (x_coord+1 < grid_size)
      printf("%d %d\n", ++x_coord, y_coord);
    else
      printf("%d %d\n", x_coord, y_coord);
  }
  else if (direction == 'W'){
    if (x_coord-1 >= 0)
      printf("%d %d\n", --x_coord, y_coord);
    else
      printf("%d %d\n", x_coord, y_coord);
  }
  else if (direction == 'S'){
    if (y_coord+1 < grid_size)
      printf("%d %d\n", x_coord, ++y_coord);
    else
      printf("%d %d\n", x_coord, y_coord);
  }
  else if (direction == 'N'){
    if (y_coord-1 >= 0)
      printf("%d %d\n", x_coord, --y_coord);
    else
      printf("%d %d\n", x_coord, y_coord);
  }


  return 0;
}