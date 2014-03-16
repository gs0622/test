#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct sclist {

	int data;
	struct sclist *next;
};

typedef struct sclist sc;

sc *create_list(int n)
{
	int i;
	sc *p, *head;

	if (0==n) return NULL;
	p = head = malloc(sizeof(sc));
	srand((unsigned int)time(NULL));

	for (i=0; p && i<n; i++) {
		p->data = rand()%100;
		/*printf("%d: %d\n", i, p->data);*/
		p->next = (i<(n-1))? malloc(sizeof(sc)) : NULL;
		p = p->next;
	}
	return head;
}

void print_list(sc *head)
{
	sc *p = head;

	while (p) {
		printf("%.2d%s", p->data, (p->next)?  " ": "\n");
		p = p->next;
	}
}

sc *reverse_list(sc *head)
{
	sc *p = head, *next = NULL;

	while (p->next) {
		head = p->next;
		p->next = next;
		next = p;
		p = head;
	}
	head->next = next;
	return head;
}

int main(int argc, char **argv)
{
	sc *head;
	int n = (argc>1)? atoi(argv[1]) : 10;
	head = create_list(n);
	print_list(head);
	head = reverse_list(head);
	print_list(head);
	head = reverse_list(head);
	print_list(head);
	return 0;
}

