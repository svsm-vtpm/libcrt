#include <stdio.h>
#include <stdarg.h>

extern int vprints(const char *format, va_list ap);

int fprintf(FILE *restrict f, const char *restrict fmt, ...)
{
	int ret;
	va_list ap;
	va_start(ap, fmt);
	ret = vprints(fmt, ap);
	va_end(ap);
	return ret;

	//printf("%s, reached dummy stub\n", __func__);
	//return 0;
}
