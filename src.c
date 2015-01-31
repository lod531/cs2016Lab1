#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

const int NUMBER_OF_TERMS_PER_THREAD = 4000;

const int NUMBER_OF_THREADS = 4;

const double * TERMS = malloc(sizeof(double) * 4);

double nilakantha(double k)
{
	double result = 4/(k*(k+1)*(k+2));
	return result;
}

void * calculatePiDigitThreaded(void *threadID) 
{
	double startTerm = 2 + NUMBER_OF_TERMS_PER_THREAD * (int)(threadID);
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
	int threadIDtemp = (int) threadID;
	TERMS[threadIDtemp] = result;
	pthread_exit(NULL);
}

double calculatePiDigitTest(void *threadID) 
{

	int startTerm = 2 + NUMBER_OF_TERMS_PER_THREAD * (int)(threadID);
	int endTerm = startTerm + 2*NUMBER_OF_TERMS_PER_THREAD;
	long double result = 0;
	int sign = 1;
	int i;
	for(i = startTerm; i < endTerm; i+= 2)
	{
		double currentTerm = nilakantha((double)i);
		currentTerm *= (double)sign;
		sign *= -1;
		result += currentTerm;
	}
	return result;
}

int main (int argc, const char * argv[]) 
{
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
}
