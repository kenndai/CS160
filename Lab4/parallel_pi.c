//parallel construct pi calculation
//need to distribute work between threads, should they just write in random order or partitioned?

#include <omp.h>
#include <stdio.h>

static long num_steps = 100000;
double step;
void main() {
	/* shared variables */
	int i; 
	double x, pi, sum, start, end;
	double psums[64] = {0};

	start = omp_get_wtime(); //start timer

	step = 1.0 / (double)num_steps; 

	#pragma omp parallel firstprivate(i, x, sum, num_steps)
	{
		/* private variables */
		int num_threads = omp_get_num_threads(); //number of threads 
		int ID = omp_get_thread_num(); //thread id, starts at 0

		num_steps = num_steps / num_threads;

		for (i = ID * num_steps; i < (ID + 1) * num_steps; ++i) {
			x = (i + 0.5) * step;
			sum = sum + 4.0 / (1.0 + x * x); //going to get num_threads amount of sums, need to sum
		}

		#pragma omp critical
			psums[ID] = sum;
	}

	for (i = 0; i < 64; ++i)
		pi += step * psums[i];

	end = omp_get_wtime(); //stop timer

	printf("elpased time: %f\n", end - start);
	printf("calculation of pi: %f\n", pi);
}
