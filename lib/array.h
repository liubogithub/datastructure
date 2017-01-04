#include <assert.h>

struct array {
	int n;  /* item count of the array */
	int lastpos;    /* the last item position */
	int *item; /* array starts here */
};
