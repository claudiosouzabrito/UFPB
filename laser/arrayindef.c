#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv)
{
  /* declare a pointer do an integer */
  int *data; 
  /* we also have to keep track of how big our array is - I use 50 as an example*/
  const int datacount = 50;
  data = malloc(sizeof(int) * datacount); /* allocate memory for 50 int's */
  if (!data) { /* If data == 0 after the call to malloc, allocation failed for some reason */
    perror("Error allocating memory");
    abort();
  }
  /* at this point, we know that data points to a valid block of memory.
     Remember, however, that this memory is not initialized in any way -- it contains garbage.
     Let's start by clearing it. */
  memset(data, 0, sizeof(int)*datacount);
  /* now our array contains all zeroes. */
  data[2] = 15;
  data[49] = 66; /* the last element in our array, since we start counting from 0 */
  /* Loop through the array, printing out the values (mostly zeroes, but even so) */
  for(int i = 0; i < 51; ++i) {
    printf("Element %d: %d\n", i, data[i]);
  }
  printf("%d\n", sizeof(data));
}