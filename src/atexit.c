#include <stdlib.h>
#include <stdio.h>

int atexit(void (*func)(void))
{
	printf("%s, reached dummy stub\n", __func__);
	return 0;
}
