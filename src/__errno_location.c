#include <errno.h>
#include <stdio.h>

int *__errno_location(void)
{
	printf("%s, reached dummy stub\n", __func__);
	return &errno;
}
