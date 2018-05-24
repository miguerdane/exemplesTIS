/* Includes are necessary to provide declarations, otherwise the analyzer will
   stop the analyzer and warn about undeclared functions (for malloc and
   printf) in this example. */
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
  int i;
  int *array = malloc(50 * sizeof(int));

 // if (array != NULL) {
    array[0] = 13;
    array[1] = 7;
    array[2] = 42;
    array[3] = 0;
    array[4] = 1;

    for (i = 0; i <= 5; i++) {
      /* The analyzer iterates on each element of the array, and print
         the value stored in it. Functions from the standard library,
         like 'printf' are supported by the analyzer.

         When the variable reaches the value 5, the analyzer complains
         about a memory access. We are trying here to access the cell
         5 but it is not in the range of the allocated array.

         According to the rule 6.5.6p8 of the C11 Standard, this is
         undefined behavior to access a cell that is out of bound of
         the array. */
      printf("array[%d] = %d\n", i, array[i]);
    }
  //}

  return 0;
}
