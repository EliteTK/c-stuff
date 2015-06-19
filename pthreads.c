#define _GNU_SOURCE
#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define NUM_THREADS 100

typedef void *(* thread_func)(void *);

void *somefunction(int *arg)
{
	int loops = rand();

	for (int i = 0; i < loops; i++) {
		pthread_yield();
		for (;i < loops; i++);
	}

	printf("%d:\t%d\n", *arg, loops);

	return NULL;
}

int main(void)
{
	srand(time(NULL));

	pthread_t threads[NUM_THREADS];
	int args[NUM_THREADS];

	for (int i = 0; i < NUM_THREADS; i++) {
		args[i] = i;
		if (pthread_create(&threads[i], NULL, (thread_func)somefunction, args + i))
			return EXIT_FAILURE;
	}

	for (int i = 0; i < NUM_THREADS; i++)
		if (pthread_join(threads[i], NULL))
			return EXIT_FAILURE;

	return EXIT_SUCCESS;
}
