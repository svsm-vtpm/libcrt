#include <stdio.h>
#include <unistd.h>

static pid_t monotonic_counter;

pid_t getpid(void)
{
	printf("%s, reached dummy stub\n", __func__);
	return ++monotonic_counter;
}
