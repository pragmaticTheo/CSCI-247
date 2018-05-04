/*
	CSCI 247 - Spring 2018
	By Brandon Chavez (W#01204919), albeit with a *LOT* of modified code
	and guidelines taken from Professor Gopalan's helpful Canvas e-mails.
	And untold amounts of help from my two best friends: Google and Stack Overflow.

	Filename: Assignment 1.c
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
	int threadCount;
	pthread_t threadId;
	int threadPolicy;
	int threadPri;
	//Space for 1 initial time stamp, and additional stamps taken at the termination of each instance of perfectlyGenericProcess.
	int64_t timeStamp[MAX_TASK_COUNT+1];
	time_t startTime;
	time_t endTime;
} ThreadArgs;

//Try to change this to use a single condition variable
pthread_mutex_t g_ThreadMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t g_conditionVar = PTHREAD_COND_INITIALIZER;
ThreadArgs g_ThreadArgs[MAX_THREAD_COUNT];
int childrenReady = 0;

void perfectlyGenericProcess(void);
void* threadFunction(void*);
void InitGlobals(void);
void DisplayThreadSchdAttributes(ThreadArgs* myThreadArg);
void DisplayThreadStats(ThreadArgs* myThreadArg);
void* retrieveTime(ThreadArgs* arg, int timeStampIndex, struct timespec timeRecord);
void initializeArgs(int policy, int priority, int startingIndex);

/*
1.	Call InitGlobals
2.	Create a number of threads (start with 1 and increase to 9) using “pthread_Create”
3.	Assign 3 threads to SCHED_OTHER, another 3 to SCHED_FIFO and another 3 to SCHED_RR
4.	Signal the condition variable
5.	Call “pthread_join” to wait on the thread
6.	Display the stats on the threads
*/

// Note that this will NOT work properly if the program is not being executed as superuser,
// due to insufficient privileges to alter scheduling policies of threads.
int main(int argc, char* argv[])
{
	InitGlobals();
	//Create the appropriate amount of threads for our purposes. Pass in a ThreadArgs structure
	//unique to each thread that serves as both an instruction booklet (for telling the thread
	//its identity, as well as what kind of scheduling policy and priority it should have)
	//and a "journal" of sorts for logging statistics we would like to display/study later.
	for(int i = 0; i < MAX_THREAD_COUNT; i++)
	{
		if(pthread_create((&(g_ThreadArgs[i].threadId)), NULL, threadFunction, (void*) &g_ThreadArgs[i]))
		{
			fprintf(stderr, "Whoa there! Looks like the thread wasn't created properly.\n");
			exit(EXIT_FAILURE);
		}else
		{
			printf("testThread[%d] was created successfully.\n", i);
		}
	}
	//Signal if all of the main thread's "children" threads are waiting for the signal.
	//Do nothing in the meantime.
	while(!(childrenReady == MAX_THREAD_COUNT))
	{
	}
	pthread_cond_broadcast(&g_conditionVar);
	//Now wait for all of the threads to finish doing their thing.
	for(int i = 0; i < MAX_THREAD_COUNT; i++)
	{
		pthread_join(g_ThreadArgs[i].threadId, NULL);
	}
	return 0;
}
// A simple test function we can pass to our threads.
void perfectlyGenericProcess(void)
{
	unsigned int numbuh = 0;
	while(numbuh < 0xffffffff)
	{
		numbuh++;
	}
}
//Uses intializeArgs to properly intialize our array of threadArgs.
//Note that as it exists now, this can only be done in multiples of three without
//changing the code herein and elsewhere in the program.
//Note to SELF: Find a way to make thread creation more flexible.
void InitGlobals(void)
{
	initializeArgs(SCHED_FIFO, 10, 0);
	initializeArgs(SCHED_RR, 10, MAX_THREAD_COUNT/3);
	initializeArgs(SCHED_OTHER, 0, MAX_THREAD_COUNT/3 + MAX_THREAD_COUNT/3);
}

//Helper function for initializing threadArgs of multiple threads with different policies.
void initializeArgs(int policy, int priority, int startingIndex)
{
	for(int i = 0; i < (MAX_THREAD_COUNT/3); i++, startingIndex++)
	{
		g_ThreadArgs[startingIndex].threadCount = startingIndex;
		pthread_t testThread;
		g_ThreadArgs[startingIndex].threadId = testThread;
		g_ThreadArgs[startingIndex].threadPolicy = policy;
		g_ThreadArgs[startingIndex].threadPri = priority;
		for(int j = 0; j < MAX_TASK_COUNT; j++)
		{
					g_ThreadArgs[startingIndex].timeStamp[MAX_TASK_COUNT + 1] = 0;
		}
		g_ThreadArgs[startingIndex].startTime = 0;
		g_ThreadArgs[startingIndex].endTime = 0;
	}
}

//Handles the portion of statistic printing concerned with the thread's basic information.
//Based heavily on sample code provided by Professor Gopalan (though I did not use it
//until I was confident that I understood how it worked).
void DisplayThreadSchdAttributes(ThreadArgs* myThreadArg )
{
	int policy;
	struct sched_param param;

	pthread_getschedparam(myThreadArg->threadId, &policy, &param);

	printf("\ntestThread[%d] now exiting...", myThreadArg->threadCount);
	printf("Thread Statistics:\n threadID = 0x%lx\n policy = %s\n priority = %d\n",
	(long int) myThreadArg->threadId,
	(policy == SCHED_FIFO) ? "SCHED_FIFO" :
	(policy == SCHED_RR) ? "SCHED_RR" :
	(policy == SCHED_OTHER) ? "SCHED_OTHER" :
	"???",
	param.sched_priority);
}

//Handles the remainder of statistic printing for the thread calling it.
//Also a modified version of Professor Gopalan's sample code.
void DisplayThreadStats(ThreadArgs* myThreadArg)
{
	if(myThreadArg)
	{
		//printf("DisplayThreadArgs: Thread Id [%lx] Pri [%d] ProcTime [%ld]\n",
		// myThreadArg->threadId, myThreadArg->threadPri, myThreadArg->processTime);

		DisplayThreadSchdAttributes(myThreadArg);
		printf(" startTime = %s", ctime(&myThreadArg->startTime));
		printf(" endTime = %s", ctime(&myThreadArg->endTime));
		printf(" TimeStamp [%"PRId64"]\n", myThreadArg->timeStamp[0] );
		//Prints out timestamps (in microseconds) for each additional time the thread completes a task.
		for(int y=1; y<MAX_TASK_COUNT+1; y++)
		{
			printf(" TimeStamp [%"PRId64"] Delta [%"PRId64"]us\n", myThreadArg->timeStamp[y],
			(myThreadArg->timeStamp[y]-myThreadArg->timeStamp[y-1]));
		}
	}
	// If no threadArgs are present, print out the stats for all of them.
	else
	{
		for(int i=0;i<MAX_THREAD_COUNT;i++)
		{
			//printf("DisplayThreadArgs: Thread Id [%lx] Pri [%d] ProcTime [%ld]\n",
			// g_ThreadArgs[i].threadId, g_ThreadArgs[i].threadPri, g_ThreadArgs[i].processTime);

			DisplayThreadSchdAttributes(myThreadArg);
			printf(" TimeStamp (task starting) [%ld]\n", g_ThreadArgs[i].timeStamp[0] );
			for(int y=1; y<MAX_TASK_COUNT+1; y++)
			{
				printf(" TimeStamp (task completed) [%ld] Delta [%ld]\n", g_ThreadArgs[i].timeStamp[y],
				(g_ThreadArgs[i].timeStamp[y]-g_ThreadArgs[i].timeStamp[y-1]));
			}
		}
	}
}

void* threadFunction(void* arg)
{
	//Set threadPolicy and threadId in accordance with the corresponding ThreadArgs
	//structure that has been provided to this particular thread.
	ThreadArgs* myArgs = (ThreadArgs*) arg;
	struct timespec timeRecord;
	struct sched_param param;
	param.sched_priority = myArgs->threadPri;
	int result = pthread_setschedparam(myArgs->threadId, myArgs->threadPolicy, &param);
	if(result)
	{
		printf("OH MY! We couldn't change the schedule parameter for some reason. Return value was: %d\n", result);
	}

	//Wait for the signal broadcast from main that signals every thread is ready to begin
	//the perfectlyGenericProcess.
	pthread_mutex_lock(&g_ThreadMutex);
	printf("testThread[%d] is waiting on signal from main.\n", myArgs->threadCount);
	childrenReady++;
	pthread_cond_wait(&g_conditionVar, &g_ThreadMutex);
	//Free the mutex for the next thread to "awaken."
	pthread_mutex_unlock(&g_ThreadMutex);

	//Get task start timeStamp. Also record the calendar time and date in timeStart.
	time(&myArgs->startTime);
	retrieveTime(myArgs, 0, timeRecord);

	for(int i = 0; i < MAX_TASK_COUNT; i++)
	{
		perfectlyGenericProcess();
		retrieveTime(myArgs, i + 1, timeRecord);
	}
	time(&myArgs->endTime);

	//Mutex lock here is necessary to ensure that results are not printed in a potentially garbled
	//fashion since SCHED_FIFO and SCHED_RR threads seem to have a tendency to end up printing
	// Their statistics as the same time. Which is irritating, to say the least.
	pthread_mutex_lock(&g_ThreadMutex);
	DisplayThreadStats(myArgs);
	pthread_mutex_unlock(&g_ThreadMutex);
}

//Gets time and then stores it as both a calendar date and a time in microseconds within a given ThreadArgs structure.
void* retrieveTime(ThreadArgs* arg, int timeStampIndex, struct timespec timeRecord)
{
	clock_gettime(CLOCK_REALTIME, &timeRecord);
	//Convert seconds to microseconds.
	arg->timeStamp[timeStampIndex] = timeRecord.tv_sec *1000000;
	//Convert nanoseconds to microseconds and then add to the timeStamp to get an accurate time in microseconds.
	arg->timeStamp[timeStampIndex] += timeRecord.tv_nsec/1000;
	//If the remainder of this conversion is .5 microseconds or higher, the timeStamp should be incremented by 1 for best accuracy.
	if(timeRecord.tv_nsec % 1000 >= 500 ) arg->timeStamp[timeStampIndex]++;
}
