#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

const int NUMBER_OF_PI_DIGITS = 4;

int exponent(int base, int exponent)
{
	int result = 1;
	int i;
	for(i = 0; i < exponent; i++)
	{
		result *= base;
	}
	return result;
}

double BBP(int k)
{
	int i;
	double result = 0;
	for(i = 0; i < k; i++)
	{	
		double currentTerm = 1;

		currentTerm /= exponent(16, i);

		currentTerm *= 4*(8*i + 1) -2*(8*i + 4) -1*(8*i + 5) -1*(8*i + 6);

		result += currentTerm;
	}
	return result;
}

void * calculatePiDigit(void *threadid) 
{
	int temp = (int)threadid + 1;
	int i;
	int digit = 0;
	for(i = 0; i < temp; i++)
	{
		int quotient = exponent(16, i);

	}
	pthread_exit(NULL);
}

int main (int argc, const char * argv[]) 
{
	double test = BBP(1);
	printf("%lf\n",test);
	/*
	pthread_t threads[NUMBER_OF_PI_DIGITS];
	int rc,t;
	for (t=0;t<NUMBER_OF_PI_DIGITS;t++) 
	{
		printf("Creating thread %d\n",t);
		rc = pthread_create(&threads[t],NULL,  calculatePiDigit,(void *)t);
		if (rc) 
		{
			printf("ERROR return code from pthread_create(): %d\n",rc);
			exit(-1);
		}
	}

	for(t=0;t<NUMBER_OF_PI_DIGITS;t++) 
	{
		 pthread_join( threads[t], NULL);
	}
	*/
}
