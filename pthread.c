/*gcc pthread.c -lpthread*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct thread_info {
	pthread_t tid;
	void *arg;
};

static void thread(void *arg)
{
	struct thread_info *ti = (struct thread_info *)arg;
	if (ti) printf("hello from tid=%u arg=%p\n", (unsigned int)ti->tid, ti->arg);
}

int main(void)
{
	int i;
	struct thread_info *ti = (struct thread_info *)malloc(sizeof(struct thread_info)*5);
	for (i=0,ti;i<5;i++) {
		//ti[i].arg=(void *)i;/*test-only*/
		pthread_create(&ti[i].tid, 0, (void *)thread, (void *)&ti[i]);
	}
        sleep(1);
	return 0;
}

