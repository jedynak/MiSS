#include <stdio.h>


int main(int argc, char *argv[])
{
  long unsigned int a, c, m;
  long unsigned int lcg;
  long unsigned int l_n=atoi(argv[1]);
  long unsigned int l_m=atoi(argv[2]);
  long unsigned int i;
  //scanf("%lu", &lcg);
  scanf("%lu %lu %lu %lu", &lcg, &a, &c, &m);
  
  for (i=1; i<=l_m; i++)
  {
    //printf("i = %lu m = %lu n=%lu  ", i, m, n);
    lcg = (a*lcg+c)%m;
    if ( i >= l_n )
        printf("%lu/%lu ", lcg, m);
  }
  
  return 0;
  
}
