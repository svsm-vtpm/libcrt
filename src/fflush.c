#include <stdio.h>

int fflush(FILE *f)
{
	printf("%s, reached dummy stub\n", __func__);
	return 0;
}
