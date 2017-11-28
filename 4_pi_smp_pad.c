#include <stdio.h>
#include <omp.h>

#define NUM_THREADS 2
#define PAD 8 //depend on L1 cache line size
static long num_steps = 100000;
double step;

int main()
{
	int i, nthreads;
	double pi,sum[NUM_THREADS][PAD],t1,t2;
	step = 1.0/(double) num_steps;	
	
	t1 = omp_get_wtime();
	omp_set_num_threads(NUM_THREADS);
	#pragma omp parallel
	{
		int i,id, nthrds;
		double x;
		id = omp_get_thread_num();
		nthrds = omp_get_num_threads();
		if (id==0) nthreads = nthrds;
		for (i=id;i<num_steps;i=i+nthrds) {
			x = (i+0.5)*step;
			sum[id][0] = sum[id][0] + 4.0/(1.0+x*x);
		}
	}
	for (i=0,pi=0;i<nthreads;i++) pi += sum[i][0] * step;
	t2 = omp_get_wtime();
	printf("pi: %f \n", pi);
	printf("finished in %f milisecond\n", (t2-t1)*1000);
}
