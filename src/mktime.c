#include <time.h>
#include <stdio.h>
#include <errno.h>

time_t mktime(struct tm *tm)
{
	(void)tm;
	printf("%s, reached dummy stub\n", __func__);
	return 0;
}
