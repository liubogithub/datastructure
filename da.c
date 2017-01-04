#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

char *seq_arr;  /* Sequences */
char *q_arr;    /* Queries */
int seq_n;  /* Sequence number */
int q;  /* Query number */
int lastans = 0;

struct list {
    struct list *prev;
    struct list *next;
    int v;
};

void list_add_tail(struct list *h, struct list *new)
{
    struct list *last = h->prev;
    last->next = new;
    new->prev = last;
    new->next = h;
    h->prev = new;
}

void run_query(int i)
{
    int type;
    int q_index;
    int x, y;
    
    /* q_arr[i][0] */
    type = *((int *)q_arr + i * 3);
    
    /* q_arr[i][1] */
    x = *((int *)q_arr + i * 3 + 1);
    
    /* q_arr[i][2] */
    y = *((int *)q_arr + i * 3 + 2);

    q_index = (x ^ lastans) % seq_n;
    if (type == 1) {
        /* append y to the selected seq */
        struct list *head = (struct list *)seq_arr + q_index;
        struct list *insert;
        insert = malloc(sizeof(struct list));
        insert->v = y;
        list_add_tail(head, insert);
    } else if (type == 2) {
        /* assign the found value to lastans */
        struct list *head = (struct list *)seq_arr + q_index;
	struct list *l = head->next;
        int j;
        
        for (j = 0; j < y; j++) {
            l = l->next;
        }
        lastans = l->v;
        printf("%d\n", lastans);
    }
}

int main() {
    int i;
    
    scanf("%d %d", &seq_n, &q);
    /* each query consists of 3 items. */
    q_arr = malloc(3 * sizeof(int) * q);
    seq_arr = malloc(sizeof(struct list) * seq_n);

    for (i = 0; i < seq_n; i++) {
        struct list *head;
        head = (struct list *)seq_arr + i;
        head->next = head;
        head->prev = head;
    }

    /* input for each query */
    for (i = 0; i < q; i++) {
        scanf("%d %d %d", (int *)q_arr + (i * 3), (int *)q_arr + (i * 3) + 1, (int *)q_arr + (i * 3) + 2);
    }

    /* execute each query */
    for (i = 0; i < q; i++) {
        run_query(i);
    }
    
    free(seq_arr);
    free(q_arr);
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */    
    return 0;
}

