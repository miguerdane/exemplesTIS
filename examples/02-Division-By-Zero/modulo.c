/* This function seems correct at the first sight, but a undefined behavior
   occurs if the caller set the value of the parameter 'b' to 0.

   According to the rule 6.5.5p5 of the C11 Standard, this is undefined behavior
   to do a division/modulo operator if the value of the second operand is 0. */
int modulo(int a, int b)
{
  return a % b;
}


/*@ ensures /result < 500; */
int main(void)
{
  int array[5] = {tis_interval(0,100), 7, 42, 10, 1};
  int i;
  int n = 0;

  for (i = 0; i < 5; i++) {
    /* The analyzer will iterate on the elements of the array, until
       reaching the value 0.

       Calling the function 'modulo' by setting the parameter 'b' to 0
       will raise an alarm. */
    n += modulo(100,array[i]);
  }

  return n;
}
