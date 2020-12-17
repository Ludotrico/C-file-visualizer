#include <stdio.h>

// -a option
// Number of assignments: 9

int sum_array(int* arr, int size) {
  int total = 0;
  for (int i = 0; i < size; ++i) {
    total += arr[i];
  }
  return total;
}

void double_array(int* arr, int size) {
  for (int i = 0; i < size; ++i) {
    arr[i] *= 2;
  }
}

int main() {
  int first_nums[5] = {1, 2, 3, 4, 5};
  int second_nums[3] = {3, 4, 5};

  int first_sum = sum_array(first_nums, 5);
  int second_sum = sum_array(second_nums, 3);

  printf("first sum is % d.\n", first_sum);
  printf("second sum is % d.\n", second_sum);

  if (first_sum == second_sum) {
    printf("The sums are equal.\n");
  } else {
    printf("The sums are different.\n");
  }

  double_array(first_nums, 5);
  printf("New sum of the first array = %d\n", sum_array(first_nums, 5));
  return 0;
}