#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

char *seq_arr;  /* Sequences */
char *q_arr;    /* Queries */
int seq_n;  /* Sequence number */
int q;  /* Query number */
int lastans = 0;

struct array {
	int n;	/* item count of the array */
	int lastpos;	/* the last item position */
	int *item; /* array starts here */
};

void append_seq(struct array *seq, int v)
{
	seq->item[seq->lastpos] = v;
	seq->lastpos++;
	/* array actual size is now seq->lastpos */

	if (seq->lastpos == seq->n) {
		/* enlarge this array by 2 */
		char *new_item = malloc(sizeof(int) * 2 * seq->n);

		/* copy the old to the new */
		memcpy(new_item, (char *)seq->item, sizeof(int) * seq->n);
		seq->item = (int *)new_item;
		seq->n *= 2;
		if (0) {
			int i;
			for (i = 0; i < seq->lastpos; i++)
				printf("%d, ", seq->item[i]);
			printf("\n");
		}
	}
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
		struct array * seq = (struct array *)seq_arr + q_index;
//		printf("%d %d\n", seq->n, seq->lastpos);
		append_seq(seq, y);
	} else if (type == 2) {
		/* assign the found value at y % size to lastans */
		struct array * seq = (struct array *)seq_arr + q_index;
		int index = y % seq->lastpos;

		lastans = seq->item[index];
		printf("%d\n", lastans);
	}
}

int main() {
	int i;
	int init_cnt = 1;

	scanf("%d %d", &seq_n, &q);
	/* each query consists of 3 items. */
	q_arr = malloc(3 * sizeof(int) * q);
	seq_arr = malloc(sizeof(struct array) * seq_n);

	/* initial each array with 16 preallocated slots */
	for (i = 0; i < seq_n; i++) {
		struct array * seq = (struct array *)seq_arr + i;
		char *seq_pointer = malloc(sizeof(int) * init_cnt);

		seq->item = (int *)seq_pointer;
		seq->n = init_cnt;
		seq->lastpos = 0;
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

