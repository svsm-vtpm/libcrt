#include <stdio.h>

long ftell(FILE *f)
{
	printf("%s, reached dummy stub\n", __func__);
	return 0;
}
