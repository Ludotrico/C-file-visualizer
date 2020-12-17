#include <stdio.h>

// -f option
// Number of function definitions: 4

void print_new_line();

// The first for loop signifies the number of rows
// The second for loop prints the necessary spaces
// The third for loop the stars
void print_star_triangle(int n) {
  int k = 2 * n - 2;
  printf("Star triangle with n = %d\n", n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < k; j++) {
      printf(" ");
    }

    k = k - 1;

    for (int j = 0; j <= i; j++) {
      printf("* ");
    }
    print_new_line();
  }
}

/* The first for loop signifies the number of rows
 The second for loop prints the necessary spaces
 The third for loop the stars */
void print_mario_steps(int n) {
  int k = 2 * n - 2;
  printf("Mario steps with n = %d\n", n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < k; j++) {
      printf(" ");
    }

    k = k - 2;

    for (int j = 0; j <= i; j++) {
      printf("* ");
    }
    print_new_line();
  }
}

void print_new_line() { printf("\n"); }

int main(int argc, char* argv[]) {
  print_star_triangle(10);
  print_new_line();
  print_mario_steps(5);
  return 0;
}