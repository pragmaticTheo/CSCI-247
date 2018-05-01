/*
	CSCI 247 - Spring 2018
	Filename: Assignment 1
	A Study of Thread Management and Scheduling Policies
	Rated 'G' for "Goddamn, Son."
	
*/

#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <inttypes.h>

#define MAX_THREAD_COUNT 9
#define MAX_TASK_COUNT 3

//Typedefs
typedef struct{
	//Presumably corresponds to the sequence in which threads in this process are created (0th, 1st, 2nd, etc.).
	int threadCount;
	// Interesting that the identifier for a threadId appears to have it's own type.
	pthread_t threadId;
	int threadPolicy;
	// The thread's absolute priority.
	int threadPri;
	long processTime;
	int64_t timeStamp[MAX_TASK_COUNT+1];
	time_t startTime;
	time_t endTime;
} ThreadArgs;

//Try to change this to use a single condition variable
pthread_mutex_t g_ThreadMutex [MAX_THREAD_COUNT];
pthread_cond_t g_conditionVar [MAX_THREAD_COUNT];
ThreadArgs g_ThreadArgs[MAX_THREAD_COUNT];

// A test function we can pass to the thread we are about to create.
void* perfectlyGenericFunction(void*);
void InitGlobals(void);
void DisplayThreadSchdAttributes(void);
void DisplayThreadStats(ThreadArgs* myThreadArg);

int main(int argc, char* argv[])
{
	pthread_t testThread1;
	void* voidPointer;
	int returnValue;
	
	//Create our test thread.
	
	returnValue = pthread_create(&testThread1, NULL, perfectlyGenericFunction, voidPointer);
	if(returnValue)
	{
		//Here we need to specify that we're outputting to the stderr stream instead of stdout (just to be safe).
		fprintf(stderr, "Whoa there! Looks like the thread wasn't created properly. Return code: %d\n", returnValue);
		exit(EXIT_FAILURE);	
	}else
	{
		printf("The testThread was created successfully with return code: %d\n", returnValue);
	}
	
	pthread_join(testThread1, NULL);
	
	
	return 0;	
}

void* perfectlyGenericFunction(void* voidPointer)
{
	unsigned int Numbuh = 0;
	for(int i = 0; i < 100000; i++)
	{
		Numbuh += 5;
	}
	//printf("Looks like 6 added to your genericInteger 100 times ended up being: %d\n", *integer);
}

void InitGlobals(void)
{
	// Initialize all globals

}

void DisplayThreadSchdAttributes( void )
{
	int policy;
	struct sched_param param;

	pthread_getschedparam(pthread_self(), &policy, &param);

	printf("DisplayThreadSchdAttributes:\n threadID = 0x%lx\n policy = %s\n priority = %d\n",
	pthread_self(),
	(policy == SCHED_FIFO) ? "SCHED_FIFO" :
	(policy == SCHED_RR) ? "SCHED_RR" :
	(policy == SCHED_OTHER) ? "SCHED_OTHER" :
	"???",
	param.sched_priority);
}

void DisplayThreadStats(ThreadArgs* myThreadArg)
{
	if( myThreadArg )
	{
		//printf("DisplayThreadArgs: Thread Id [%lx] Pri [%d] ProcTime [%ld]\n",
		// myThreadArg->threadId, myThreadArg->threadPri, myThreadArg->processTime);

		DisplayThreadSchdAttributes();
		printf(" startTime = %s\n endTime = %s\n", ctime(&myThreadArg->startTime), ctime(&myThreadArg->endTime));
		printf(" TimeStamp [%"PRId64"]\n", myThreadArg->timeStamp[0] );
		
		//Prints out timestamps (in microseconds) for each additional time the thread completes a task.
		for(int y=1; y<MAX_TASK_COUNT+1; y++)
		{
			printf(" TimeStamp [%"PRId64"] Delta [%"PRId64"]us\n", myThreadArg->timeStamp[y],
			(myThreadArg->timeStamp[y]-myThreadArg->timeStamp[y-1]));
		}
	}
	else
	{
		for(int i=0;i<MAX_THREAD_COUNT;i++)
		{
			//printf("DisplayThreadArgs: Thread Id [%lx] Pri [%d] ProcTime [%ld]\n",
			// g_ThreadArgs[i].threadId, g_ThreadArgs[i].threadPri, g_ThreadArgs[i].processTime);

			DisplayThreadSchdAttributes();
			printf(" TimeStamp (task starting) [%ld]\n", g_ThreadArgs[i].timeStamp[0] );
			for(int y=1; y<MAX_TASK_COUNT+1; y++)
			{
				printf(" TimeStamp (task completed) [%ld] Delta [%ld]\n", g_ThreadArgs[i].timeStamp[y],
				(g_ThreadArgs[i].timeStamp[y]-g_ThreadArgs[i].timeStamp[y-1]));
			}
		}
	}
}





















