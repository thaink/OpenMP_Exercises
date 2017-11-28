#include <stdio.h>
#include <omp.h>

int main()
{
	int j,tmp = 0;
	#pragma omp parallel for private(tmp)
	for (j = 0; j < 1000; ++j)
		tmp += j;
	printf("%d\n", tmp);
}
