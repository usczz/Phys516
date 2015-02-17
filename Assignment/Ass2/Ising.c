#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main(int argc, char *argv[])
{
if (argc < 4)
{
printf("Not enough parameters,using #(L) #(H) #(Step)\n ");
exit(-1);
}
double JdivT, HdivT;
double runM, sumM, sumM2;
int L = atoi(argv[1]);
HdivT = atof(argv[2]);
int Sta_step = atoi(argv[3]);
double avgM, sigM;
int step;
FILE *avg, *sig, *Jd, *run;
avg = fopen("avgMVal", "w");
sig = fopen("sigMVal", "w");
Jd = fopen("JVal", "w");
run = fopen("HistogramV","w");
//allocate memory for 2D ising model
int **s = (int **)malloc(L * sizeof(*s));
for (int i = 0; i < L; i++)
s[i] = (int *)malloc(L * sizeof(*(s[i])));
//outer loop
for (JdivT = 0.2; (0.9 - JdivT) > 1e-5; JdivT += 0.1)
{
for (int i = 0; i < L; i++)
for (int j = 0; j < L; j++)
s[i][j] = 1;
runM = 1.0 * L * L;
sumM = 0.0;
sumM2 = 0.0;
srand((unsigned)time((long *)0));
//inner loop
for (step = 0; step < Sta_step; step++)
{

int i = rand()%L;
int j = rand()%L;
//printf("i %d, j %d\n",i,j);
int im = (i + L - 1) % L;
int ip = (i + 1) % L;
int jm = (j + L - 1) % L;
int jp = (j + 1) % L;
double dVdivT = 2 * s[i][j] * (JdivT * (s[im][j] + s[ip][j] + s[i][jm] + s[i][jp]) + HdivT);
//printf("%e\n",dVdivT);
if (dVdivT <= 0)
{
s[i][j] = -s[i][j];
runM += 2 * s[i][j];
}
else
{
double randnum =  rand() / (double)RAND_MAX;
double exp_dv = exp(-dVdivT);
if (randnum <= exp_dv)
{
s[i][j] = - s[i][j];
runM += 2 * s[i][j];
}
}
//printf("Run M %e,i %d, j %d\n",runM,i,j);
sumM += runM;
sumM2 += runM * runM;
	if((0.2-JdivT)<1e-5 && (JdivT-0.2)<1e-5)
	{
		fprintf(run,"%d",(int)runM);
		if(step != (Sta_step-1))
			fprintf(run,",");
	}
}
avgM = fabs(sumM / Sta_step);
sigM = sqrt(sumM2 / Sta_step - avgM * avgM);
//printf("J %e, avgM %e, sigM %e\n",JdivT,avgM,sigM);
fprintf(Jd, "%e", JdivT);
fprintf(sig, "%e", sigM);
fprintf(avg, "%e", avgM);
if ((0.8 - JdivT) > 1e-5)
{
fprintf(Jd, ",");
fprintf(avg, ",");
fprintf(sig, ",");
}
}
//close file handler
fclose(Jd);
fclose(avg);
fclose(sig);
fclose(run);
//free space of ising model
for (int i = 0; i < L; i++)
free(s[i]);
free(s);
return 0;
}
