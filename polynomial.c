#include <stdio.h>
#include <stdlib.h>
typedef struct node {
    float coef;
    int exp;
    struct node *next;
} polynomial;
int add(float coef, int exp, struct node **headref)
{
    struct node *p, *q;
    if (!headref) return -1; /*error*/
    p = *headref;
    q = malloc(sizeof(struct node));
    if (!q) {
        perror("no memory");
        return -1; /*error*/
    }
    q->coef = coef, q->exp = exp;
    if (!p) {
        *headref = q;
        return 0;
    }
    while (p->next) p = p->next;
    p->next = q;
    return 0;
}
void freeall(struct node *head)
{
    if (head) {
        struct node *cur = head;
        while (cur) {
            struct node *tmp = cur;
            cur = cur->next;
            free(tmp);
        }
        head = NULL;
    }
}
void printall(struct node *head)
{
    if (head) {
        struct node *cur = head;
        while (cur) {
            if (cur == head)
                printf("%fx^%d", cur->coef, cur->exp);
            else 
                printf(" + %fx^%d", cur->coef, cur->exp);
            cur = cur->next;
        }
        printf("\n");
    }
}
int main(void)
{
    struct node *head = NULL;
    add(3, 2, &head);
    add(5, 1, &head);
    add(9, 0, &head);
    printall(head);
    freeall(head);
    return 0;
}
