//loop construct pi calculation

#include <omp.h>
#include <stdio.h>

static long num_steps = 100000;
double step;
void main() {

	int i;
	double x, pi, sum, start, end;

	start = omp_get_wtime(); //start timer

	step = 1.0 / (double)num_steps;

	#pragma omp parallel firstprivate(i, x, num_steps)
	{
		#pragma omp for reduction (+:sum)
			for (i = 0; i < num_steps; ++i) {
				x = (i + 0.5) * step;
				sum = sum + 4.0 / (1.0 + x * x);
			}
	}
	pi = step * sum;

	end = omp_get_wtime();

	printf("elapsed time: %f\n", end - start);
	printf("calculation of pi: %f\n", pi);
}
