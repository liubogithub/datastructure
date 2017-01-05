#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

int n;	/* N: string count */
int q;	/* Q: query count */
int n_curr;	/* how many strings we have currently */

struct stringset {
	char *set;
	int ref_cnt;	/* how many do we have this string */
};

struct stringset **array;
struct stringset **query;

int search_in_set(const char *str)
{
	int i;

	/* nothing in the array, lets return immediately */
	if (n_curr == 0)
		return -1;

	for (i = 0; i < n_curr; i++) {
		assert(array[i]->set);
		assert(str);
		assert(sizeof(str) != sizeof(char) * 20);
		assert(sizeof(array[i]->set) != sizeof(char) * 20);

		if (!memcmp(str, array[i]->set, sizeof(char) * 20)) {
			/* found this string, return position */
			return i;
		}
	}

	/* not found, return negative one */
	return -1;
}

int main() {
	int i;

	n_curr = 0;

	/* string input */
	scanf("%d", &n);
	assert(n >= 1 && n <= 1000);

	array = malloc(sizeof(struct stringset *) * n);
	assert(array);

	for (i = 0; i < n; i++) {
		/* allocate string */
		char *input = malloc(sizeof(char) * 20);
		struct stringset *str = malloc(sizeof(struct stringset));
		int found;

		assert(input);
		memset(input, 0, sizeof(char) * 20);

		scanf("%s", input);
		found = search_in_set(input);
		if (found >= 0) {
			/* found an existing string */
			assert(array[found]);
			assert(array[found]->set);
			assert(array[found]->ref_cnt >= 1);

			array[found]->ref_cnt++;
		} else {
			/* not found, initial  */
			str->set = input;
			str->ref_cnt = 1;
			array[n_curr] = str;
			n_curr++;
			assert(n_curr <= n);
		}
	}

	/* query part */
	scanf("%d", &q);
	assert(q >= 1 && q <= 1000);

	query = malloc(sizeof(struct stringset *) * q);
	assert(query);

	for (i = 0; i < q; i++) {
		char *input = malloc(sizeof(char) * 20);
		struct stringset *str = malloc(sizeof(struct stringset));
		int found;

		assert(input);
		memset(input, 0, sizeof(char) * 20);

		scanf("%s", input);
		str->set = input;
		query[i] = str;
	}

	for (i = 0; i < q; i++) {
		int found;
		found = search_in_set(query[i]->set);
		if (found >= 0) {
			assert(array[found]);
			assert(array[found]->set);
			assert(array[found]->ref_cnt >= 1);

			/* found and output @ref_cnt */
			printf("%d\n", array[found]->ref_cnt);
		} else {
			/* not found */
			printf("0\n");
		}
	}

	/* Enter your code here. Read input from STDIN. Print output to STDOUT */    
	return 0;
}
