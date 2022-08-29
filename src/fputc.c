#include <stdio.h>

int fputc(int c, FILE *f)
{
	printf("%s, reached dummy stub\n", __func__);
	return 0;
}
