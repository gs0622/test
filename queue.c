/* queue example */
#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;
	struct node *next;
};

static void push_back(struct node **ref, int data)
{
	struct node dummy, *cur = &dummy;
	struct node *tmp = malloc(sizeof(struct node));
	dummy.next = *ref;
	tmp->data = data, tmp->next = NULL;
	while (cur->next) cur = cur->next;
	cur->next = tmp;
	*ref = (dummy.next);
}

static int pop_front(struct node **ref)
{
	int data;
	struct node *top = *ref;
	data = top->data;
	*ref = top->next;
	free(top);
	return data;
}

int main(int argc, char **argv)
{
	int i;
	struct node *q = NULL;
	for (i=1; i<10; i++) {
		push_back(&q, i);
	}
	for (i=1; i<10; i++) {
		printf("%d\n", pop_front(&q));
	}
    return 0;
}
