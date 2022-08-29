#include <sys/socket.h>
#include <stdio.h>

typedef unsigned socklen_t;

ssize_t send(int fd, const void *buf, size_t len, int flags)
{
	printf("%s, reached dummy stub\n", __func__);
	return 0;
}

ssize_t recv(int fd, void *buf, size_t len, int flags)
{
	printf("%s, reached dummy stub\n", __func__);
	return 0;
}

int connect(int fd, const struct sockaddr *addr, socklen_t len)
{
	(void)fd;
	(void)addr;
	(void)len;
	printf("%s, reached dummy stub\n", __func__);
	return 0;
}

int socket(int domain, int type, int protocol)
{
	(void)domain;
	(void)type;
	(void)protocol;
	printf("%s, reached dummy stub\n", __func__);
	return 0;
}
