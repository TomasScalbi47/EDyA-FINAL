#include <stdio.h>
#include <stdlib.h>

// A recursive binary search function. It returns
// location of x in given array arr[l..r] is present,
// otherwise -1
int binarySearch(int arr[], int l, int r, int x)
{
  int mid = l + (r - l) / 2;
  printf ("mid: |%d|, l: |%d|, r: |%d|\n", mid, l, r);
    if (r >= l) {


        // If the element is present at the middle
        // itself
        if (arr[mid] == x)
            return mid;

        // If element is smaller than mid, then
        // it can only be present in left subarray
        if (arr[mid] > x)
            return binarySearch(arr, l, mid - 1, x);

        // Else the element can only be present
        // in right subarray
        return binarySearch(arr, mid + 1, r, x);
    }
    // Si r es -1, significa que x, si estuviese, estaría como primer elemento.
    // si no significa que x, si estuviese, estaría como último elemento.
    if (r == -1){
      return -1;
    }
    else
      return mid;
}

int main(void)
{
    int arr[] = { 2, 4, 6, 8, 10, 40 };
    int n = sizeof(arr) / sizeof(arr[0]);
    int x = 1;
    int result = binarySearch(arr, 0, n - 1, x);
    if (result == -1)
      printf("El elemento no esta, si estuviese estaria al comienzo\n");
    else if (result == n)
      printf ("El elemento no esta, si estuviese estaria al final\n");
    else
      printf("Element is present at index %d\n", result);
    return 0;
}
