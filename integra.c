#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mpi.h"

float x0[10];


double function(float x[], int size);
double randn(double mu,double sigma);

int main(int argc, char *argv[]){
  
  double min=0.0;
  double max=1.0;
  double mu=0.0;
  double sigma=1.0;
  int N=atoi(argv[1]);
  double h=max/(double)N;
  double integral=0.0;
  
  int i;
  for (i=0;i<10;i++){
    x0[i]=(double) rand()/ (double) RAND_MAX;
  }
  int j;
  for (i=0;i<10;i++){
    for(j=0;j<N;j++){
      double rand_c=(double) rand()/ (double) RAND_MAX;
      x0[i]=rand_c;
      integral=h*(integral+function(x0,10));
    }
  }
  printf("%lf\n",integral);
  return 0;
}

double function(float *x, int size)
{
  float x_s;
  int i;
  for (i=0; i<size;i++)
  {
    x_s+=x[i];
  }
  return pow(x_s,2.0);
}

double randn (double mu, double sigma)
{
  double U1, U2, W, mult;
  static double X1, X2;
  static int call = 0;
 
  if (call == 1)
    {
      call = !call;
      return (mu + sigma * (double) X2);
    }
 
  do
    {
      U1 = -1 + ((double) rand() / RAND_MAX) * 2;
      U2 = -1 + ((double) rand() / RAND_MAX) * 2;
      W = pow(U1, 2) + pow(U2, 2);
    }
  while (W >= 1 || W == 0);
 
  mult = sqrt((-2 * log(W)) / W);
  X1 = U1 * mult;
  X2 = U2 * mult;
 
  call = !call;
 
  return (mu + sigma * (double) X1);
}
