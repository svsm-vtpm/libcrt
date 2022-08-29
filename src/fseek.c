#include <stdio.h>

int fseek(FILE *f, long off, int whence)
{
	printf("%s, reached dummy stub\n", __func__);
	return 0;
}
