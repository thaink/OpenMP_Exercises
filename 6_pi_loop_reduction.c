#include <stdio.h>
#include <omp.h>

#define NUM_THREADS 2
static long num_steps = 100000;
double step;

int main()
{
	int i;
	double pi,sum = 0.0,t1,t2;
	step = 1.0/(double) num_steps;	
	
	t1 = omp_get_wtime();
	omp_set_num_threads(NUM_THREADS);
	#pragma omp parallel
	{
		double x;
		#pragma omp for reduction(+:sum)
		for (i=0;i<num_steps;i++) {
			x = (i+0.5)*step;
			sum += 4.0/(1.0+x*x);
		}
	}
	pi = step * sum;
	t2 = omp_get_wtime();
	printf("pi: %f \n", pi);
	printf("finished in %f milisecond\n", (t2-t1)*1000);
}
