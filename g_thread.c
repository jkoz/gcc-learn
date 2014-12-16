#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define CHILD_NUM 10

// gcc g_thread.c -lpthread

typedef struct shared_t {
	int counter;
	int end;
	int *array;
	sem_t *mutex; // muttex added
} shared_t;

static void *check_malloc(int size);
static pthread_t make_thread(void *(*entry)(void*), shared_t *);
static void join_thread(pthread_t);
void *run_entry(void *arg);
static sem_t *make_semaphore(int n);
static shared_t *make_shared(int);
static void check_array(shared_t *);

int main() {
	int i;
	pthread_t childs[CHILD_NUM];
	shared_t *shared = make_shared(1000000);

	// run threads
	for (i = 0; i < CHILD_NUM; i++) {
		childs[i] = make_thread(run_entry, shared);
	}

	// wait for threads before terminating
	for (i = 0; i< CHILD_NUM; i++) {
		join_thread(childs[i]);
	}

	// check results
	check_array(shared);
	return 0;
}

static void join_thread(pthread_t thread) {
	int ret = pthread_join(thread, NULL);
	if (ret == -1) {
		perror("pthread_join failed");
		exit(-1);
	}
}

static void *check_malloc(int size) {
	void *p = malloc(size);
	if (!p) {
		perror("malloc failed");
		exit(-1);
	}
	return p;
}

static pthread_t make_thread(void *(*entry)(void*), shared_t *shared) {
	pthread_t thread;
	int ret = pthread_create(&thread, NULL, entry, (void*)shared);
	if (ret != 0) {
		perror("pthread_create failed");
		exit(-1);
	}
	return thread;
}

// multiple threads go here and increase value of arrays to 1
void *run_entry(void *arg) {
	printf("run_entry()\n");
	shared_t *shared = (shared_t*) arg;

	sem_wait(shared->mutex); // mutext added, wait
	while (1) {

		if (shared->counter >= shared->end) {
			sem_post(shared->mutex); // mutext added, signal
			break;
		}
		shared->array[shared->counter]++;
		shared->counter++;

	}
	sem_post(shared->mutex); // mutext added, signal

	pthread_exit(NULL);
}

static void check_array(shared_t *shared) {
	int i, errors = 0;
	for (i = 0; i < shared->end; i++) {
		printf("%d, ", shared->array[i]);
		if (shared->array[i] != 1) errors++;
	}
	printf("\n%d errors.\n", errors);
}

static sem_t *make_semaphore(int n) {
	sem_t *sem = check_malloc(sizeof(sem_t*));
	int ret = sem_init(sem, 0, n);
	if (ret == -1) {
		perror("sem_init failed");
		exit(-1);
	}
	return sem;
}

static shared_t *make_shared(int end) {
	int i;
	shared_t *shared = check_malloc(sizeof(shared_t*));

	shared->counter = 0;
	shared->end = end;
	shared->array = check_malloc(shared->end * sizeof(int));
	for (i = 0; i < shared->end; i++) {
		shared->array[i] = 0;
	}

	// mutext added
	shared->mutex = make_semaphore(1);

	return shared;
}
