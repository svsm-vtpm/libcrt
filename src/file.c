#include <unistd.h>
#include <stdio.h>

int close(int fd)
{
	(void)fd;
	printf("%s, reached dummy stub\n", __func__);
	return 0;
}

int fcntl(int fd, int cmd, ...)
{
	(void)fd;
	(void)cmd;
	printf("%s, reached dummy stub\n", __func__);
	return 0;
}

ssize_t read(int fd, void *buf, size_t count)
{
	printf("%s, reached dummy stub\n", __func__);
	return 0;
}

ssize_t write(int fd, const void *buf, size_t count)
{
	printf("%s, reached dummy stub\n", __func__);
	return 0;
}
