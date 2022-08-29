#include <string.h>
#include <stdarg.h>

extern int vsnprints(char *str, size_t size, const char *format, va_list ap);

int vsnprintf(char *restrict s, size_t n, const char *restrict fmt, va_list ap)
{
	return vsnprints(s, n, fmt, ap);
}
