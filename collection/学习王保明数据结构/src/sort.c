#include "sort.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void PrintArray(int array[], int len) {
  for (int i = 0; i < len; i++) {
    printf("%d ", array[i]);
  }
  printf("\n");
}

void Swap(int array[], int i, int j) {
  int tem = array[i];
  array[i] = array[j];
  array[j] = tem;
}

void SelectionSort(int array[], int len) {
  for (int i = 0; i < len; i++) {
    int k = i;
    for (int j = i + 1; j < len; j++) {
      if (array[k] > array[j]) {  // 设计巧妙，不用比较一次就交换一次位置。标记最小数的位置。
        k = j;
      } 
    }
    Swap(array, i, k);
    PrintArray(array, len);
  }
}

void InsertionSort(int array[], int len) {
  for (int i = 1; i < len; i++) {
    int tem = array[i];
    int k = i;
    for (int j = i - 1; j >= 0; j--) {
      if (tem < array[j]) {
        array[j + 1] = array[j];
        k = j;  // j 位置移走后为空，则需要tem移进去。
      }
    }
    array[k] = tem;
    PrintArray(array, len);
  }
}

void BubbleSort(int array[], int len) {
  int is_exchanged = 1;  // true = 1, false = 0;
  for (int i = 0; i < len && is_exchanged == 1; i++) {
    is_exchanged = 0;
    for (int j = len - 1; j > i; j--) {
      if (array[j] < array[j - 1]) {
        is_exchanged = 1;
        Swap(array, j, j - 1);
      }
    }
    PrintArray(array, len);
  }
}

// 步长不断改变的插入排序。
void ShellSort(int array[], int len) {
  int gap = len;
  do {
    gap = gap / 3 + 1;
    for (int i = gap; i < len; i += gap) {  // InsertionSort which step is gap;
      int k = i;
      int tem = array[i];
      for (int j = i - gap; j >= 0; j -= gap) {
        if (tem < array[j]) {
          array[j + gap] = array[j];
          k = j;
        } else {
          break;
        }
      }
      array[k] = tem;
    }
    PrintArray(array, len);
  } while (gap > 1);
}

static int Partition(int array[], int low, int high) {
  int pv = array[low];
  while (low < high) {
    while (low < high && array[high] >= pv) {
      high--;
    }
    Swap(array, low, high);
    while (low < high && array[low] <= pv) {
      low++;
    }
    Swap(array, low, high);
  }
  return low;
}

static void QSort(int array[], int low, int high) {
  if (low < high) {
    int pivot = Partition(array, low, high);
    QSort(array, low, pivot - 1);
    QSort(array, pivot + 1, high);
  }
}

void QuickSort(int array[], int len) {
  QSort(array, 0, len - 1);
}

static void Merge(int src[], int dst[], int low, int mid, int high) {
  int i = low;
  int j = mid + 1;
  int k = low;

  while (j <= high && i <= mid) {
    if (src[i] < src[j]) {
      dst[k++] = src[i++];
    } else {
      dst[k++] = src[j++];
    }
  }

  while (i <= mid) {
    dst[k++] = src[i++];
  }

  while (j <= high) {
    dst[k++] = src[j++];
  }
}

static void MSort(int src[], int dst[], int low, int high, int max) {
  if (low == high) {
    dst[low] = src[low];
  } else {
    int mid = (low + high) / 2;
    int* space = (int*)malloc(sizeof(int) * max);
    if (space != NULL) {
      MSort(src, space, low, mid, max);
      MSort(src, space, mid + 1, high, max);
      Merge(space, dst, low, mid, high);
    }
    free(space);
  }
}

void MergeSort(int array[], int len) {
  MSort(array, array, 0, len - 1, len);
}
