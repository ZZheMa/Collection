#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sort.h"


int main() {
  int arr[10] = {10, 12, 1, 3, 2, 2, 55, 44, 66, 11};
  int len = sizeof(arr) / sizeof(*arr);

  printf("The original order :\n");
  PrintArray(arr, len);

  printf("The SelectionSort order :\n");
  SelectionSort(arr, len);
  PrintArray(arr, len);
  printf("\n");

  int arr1[10] = { 10, 12, 1, 3, 2, 2, 55, 44, 66, 11 };
  printf("The InsertionSort order :\n");
  InsertionSort(arr1, len);
  PrintArray(arr1, len);
  printf("\n");

  int arr2[10] = { 10, 12, 1, 3, 2, 2, 55, 44, 66, 11 };
  printf("The BubbleSort order :\n");
  BubbleSort(arr2, len);
  PrintArray(arr2, len);
  printf("\n");

  int arr3[10] = { 10, 12, 1, 3, 2, 2, 55, 44, 66, 11 };
  printf("The ShellSort order :\n");
  ShellSort(arr3, len);
  PrintArray(arr3, len);
  printf("\n");

  int arr4[10] = { 10, 12, 1, 3, 2, 2, 55, 44, 66, 11 };
  printf("The QuickSort order :\n");
  QuickSort(arr4, len);
  PrintArray(arr4, len);
  printf("\n");

  int arr5[10] = { 10, 12, 1, 3, 2, 2, 55, 44, 66, 11 };
  printf("The MergeSort order :\n");
  MergeSort(arr5, len);
  PrintArray(arr5, len);
  printf("\n");

  return 0;
}
