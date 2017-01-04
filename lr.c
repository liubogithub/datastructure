#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

int n;	/* n items */
int d;	/* d: left rotation operations */

struct list {
	struct list *prev;
	struct list *next;
	int v;
};

struct list *queue_head;	/* array head */

void list_add_tail(struct list *new, struct list *h, struct list *prev)
{
	assert(prev);
	prev->next = new;
	h->prev = new;
	new->prev = prev;
	new->next = h;
}

void list_del_init(struct list *l)
{
	struct list *prev = l->prev;
	struct list *next = l->next;

	assert(prev);
	assert(next);
	prev->next = next;
	next->prev = prev;
	l->next = l->prev = NULL;
}

int main() {
	int i;
	struct list *l;

	scanf("%d %d", &n, &d);
	assert(n >= d);
	queue_head = malloc(sizeof(struct list));
	assert(queue_head);
	queue_head->prev = queue_head->next = queue_head;

	for (i = 0; i < n; i++) {
		struct list *new = malloc(sizeof(struct list));
		assert(new);
		scanf("%d", &new->v);
		list_add_tail(new, queue_head, queue_head->prev);
	}

	l = queue_head->next;
	for (i = 0; i < d; i++, l = queue_head->next) {
		list_del_init(l);
		list_add_tail(l, queue_head, queue_head->prev);
	}

	l = queue_head->next;
	for (i = 0; i < n; i++, l = l->next) {
		assert(l);
		printf("%d ", l->v);
	}
	printf("\n");
	/* Enter your code here. Read input from STDIN. Print output to STDOUT */    
	return 0;
}
