#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

int n;	/* n items */
int d;	/* d: left rotation operations */

int *queue;	/* array */

int main() {
	int i;
	int exchange;
	int j;
	int half;
	int ops;

	scanf("%d %d", &n, &d);
	assert(n >= d);
	queue = malloc(sizeof(int) * n);
	assert(queue);

	for (i = 0; i < n; i++) {
		scanf("%d", &queue[i]);
	}

	half = n >> 1;
	/* 0 ~ n-1 */
	if (d <= half) {
		ops = d;
		for (i = 0; i < ops; i++) {
			exchange = queue[0];
			/* bubble up 1 by 1 */
			for (j = 0; j < n - 1; j++) {
				queue[j] = queue[j + 1];
			}
			/* assign exchange to the last one */
			queue[n - 1] = exchange;
#if 0
			for (j = 0; j < n; j++)
				printf("%d ", queue[j]);
			printf("\n");
#endif
		}
	} else {	/* d >= half */
		/* bubble reversely, adjust ops count accordingly */
		ops = n - d ;
		for (i = 0; i < ops; i++) {
			exchange = queue[n - 1];
			/* bubble reversely 1 by 1 */
			for (j = n - 1; j > 0; j--) {
				queue[j] = queue[j - 1];
			}
			/* assign exchange to the first one */
			queue[0] = exchange;
		}
#if 0
		for (j = 0; j < n; j++)
			printf("%d ", queue[j]);
		printf("\n");
#endif
	}

	for (i = 0; i < n; i++) {
		printf("%d ", queue[i]);
	}
	printf("\n");
	/* Enter your code here. Read input from STDIN. Print output to STDOUT */    
	return 0;
}
