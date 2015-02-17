/* Monte Carlo integration of PI by sample mean */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
int main() {
  FILE *y,*std;
  y = fopen("pivalue","w");
  std = fopen("devvalue","w");
  double x,pi,sum,sqr;
  int try,ntry;
  for(ntry = 10;ntry<=1000000;ntry*=10)
  {
    sum =0.0;
    sqr = 0.0;
    printf("The number of MC trials: %d\n", ntry);
    srand((unsigned)time((long *)0));
    for(try = 0;try < ntry;try++)
    {
      x = rand()/(double)RAND_MAX;
      x= 4.0/ (1.0+x*x);
      sqr += x*x;
      sum+= x;
    }
    pi = sum/ntry;
    sqr = sqr/ntry;
    double std_dev = sqrt((sqr-pi*pi)/(ntry-1));
    fprintf(y, "%e", pi);
    if(ntry!=1000000)
      fprintf(y,",");
    fprintf(std,"%e",std_dev);
    if(ntry!=1000000)
      fprintf(std, ",");
  }
  fclose(y);
  fclose(std);
  return 0;
}
