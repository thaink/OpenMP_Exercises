#include <stdio.h>
#include <omp.h>

#define NUM_THREADS 1
static long num_steps = 100000;
double step;

int main()
{
	double pi,sum=0.0,t1,t2;
	step = 1.0/(double) num_steps;	
	
	t1 = omp_get_wtime();
	omp_set_num_threads(NUM_THREADS);
	#pragma omp parallel
	{
		int i,id, nthrds; double x, s = 0.0;
		id = omp_get_thread_num();
		nthrds = omp_get_num_threads();
		for (i=id;i<num_steps;i=i+nthrds) {
			x = (i+0.5)*step;
			s = s + 4.0/(1.0+x*x);
		}
	#pragma omp critical
		sum += s;
	}
	pi = sum * step;
	t2 = omp_get_wtime();
	printf("pi: %f \n", pi);
	printf("finished in %f milisecond\n", (t2-t1)*1000);
}
