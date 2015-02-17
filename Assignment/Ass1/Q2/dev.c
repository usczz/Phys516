#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define NSEED 100
int main()
{
	double sum,pi,pi2,x,dev,log_std_dev,std_dev;
	FILE *dev_arr,*log_dev_arr;
	dev_arr = fopen("std_dev","w");
	log_dev_arr = fopen("log_std_est","w");
	int ntry,try,seed;
	for(ntry = 10;ntry<=1000000;ntry*=10)
	{
		dev = -1;
		while(dev <=0)
		{
			pi = 0.0;
			pi2 = 0.0;
			srand((unsigned)time((long*)0));
			for(seed = 0;seed < NSEED ;seed++)
			{
				sum = 0.0;
				for(try = 0;try<ntry;try++)
				{
					x = rand()/(double)RAND_MAX;
					x = 4.0/(1.0+x*x);
					sum+= x;
				}
				pi += sum/ntry;
				pi2 += (sum/ntry)*(sum/ntry);
			}
			dev = pi2/100 - (pi/100)*(pi/100);
		}
		std_dev = sqrt(dev);
		log_std_dev = log10(sqrt(dev));
		fprintf(dev_arr, "%e", std_dev);
		if(ntry!=1000000)
			fprintf(dev_arr,",");
		fprintf(log_dev_arr,"%e",log_std_dev);
		if(ntry!=1000000)
			fprintf(log_dev_arr,",");
	}
	fclose(dev_arr);
	fclose(log_dev_arr);
	return 0;
}
