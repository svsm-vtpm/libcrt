#include <stdio.h>
#include <stdarg.h>

extern int vprints(const char *format, va_list ap);

int printf(const char *restrict fmt, ...)
{
	int ret;
	va_list ap;
	va_start(ap, fmt);
	ret = vprints(fmt, ap);
	va_end(ap);
	return ret;
}

int dprintf(int fd, const char *__restrict fmt, ...) {
	int ret;
	va_list ap;
	va_start(ap, fmt);
	ret = vprints(fmt, ap);
	va_end(ap);
	return ret;
}

int vdprintf(int fd, const char *restrict fmt, va_list ap) {
  return vprints(fmt, ap);
}

int puts(const char *s)
{
        return printf("%s\n", s);
}
