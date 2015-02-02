#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

const int NUMBER_OF_TERMS_PER_THREAD = 40000;

const int NUMBER_OF_THREADS = 4;

double * TERMS;

double nilakantha(double k)
{
	double result = 4/(k*(k+1)*(k+2));
	return result;
}

void * calculatePiDigitThreaded(void *threadID) 
{
	int threadIDtemp = (int) threadID;
	double startTerm = 2 + (NUMBER_OF_TERMS_PER_THREAD * threadIDtemp);
	double endTerm = startTerm + 2*NUMBER_OF_TERMS_PER_THREAD;
	double result = 0;
	double sign = 1;
	int i;
	for(i = startTerm; i < endTerm; i+= 2)
	{
		double currentTerm = nilakantha((double)i);
		currentTerm *= sign;
		sign = (sign > 0)? 1 : -1;
		result += currentTerm;
	}
	TERMS[threadIDtemp] = result;
	pthread_exit(NULL);
}

int main (int argc, const char * argv[]) 
{

	TERMS = malloc(sizeof(double) * NUMBER_OF_THREADS);
	pthread_t threads[NUMBER_OF_THREADS];
	int threadFailure,threadID;
	for (threadID=0;threadID<NUMBER_OF_THREADS;threadID++) 
	{
		printf("Creating thread %d\n",threadID);
		threadFailure = pthread_create(&threads[threadID],NULL,  calculatePiDigitThreaded,(void *)threadID);
		if (threadFailure) 
		{
			printf("ERROR return code from pthread_create(): %d\n",threadFailure);
			exit(-1);
		}
	}

	for(threadID=0;threadID<NUMBER_OF_THREADS;threadID++) 
	{
		 pthread_join( threads[threadID], NULL);
	}

	double result = 3;
	int i;
	for(i = 0; i < NUMBER_OF_THREADS; i++)
	{
		result+=TERMS[i];
	}
	printf("%lf\n",result);
}
