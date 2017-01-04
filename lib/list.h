#include <assert.h>

struct list {
	struct list *prev;
	struct list *next;
	int v;
};

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

