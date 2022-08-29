#include <stddef.h>

typedef __builtin_va_list	VA_LIST;

int vsnprints(char *str, size_t size, const char *format, VA_LIST ap);
extern void serial_out(const char *s);

enum {
	LEN_MOD_INVALID		= 0,

	LEN_MOD_HALF_HALF,
	LEN_MOD_HALF,
	LEN_MOD_INT,
	LEN_MOD_LONG,
	LEN_MOD_LONG_LONG,

	LEN_MOD_MAX
};

static char *format_string(char *cur, char *end, VA_LIST ap)
{
	char *tmp = VA_ARG(ap, char *);

	while (*tmp) {
		if (cur < end)
			*cur = *tmp;

		cur++;
		tmp++;
	}

	return cur;
}

static char *format_base16(char *cur, char *end, int width, VA_LIST ap)
{
	unsigned long long num;
	char *tmp, buffer[32];
	unsigned int size;
	char *map;

	map = "0123456789abcdef";

	if (cur < end)
		*cur++ = '0';
	if (cur < end)
		*cur++ = 'x';

	if (width == LEN_MOD_HALF_HALF) {
		unsigned char n = (unsigned char) VA_ARG(ap, int);
		num = (unsigned long long)n;
		size = 1;
	} else if (width == LEN_MOD_HALF) {
		unsigned short n = (unsigned short) VA_ARG(ap, int);
		num = (unsigned long long)n;
		size = 2;
	} else if (width == LEN_MOD_INT) {
		unsigned int n = (unsigned int) VA_ARG(ap, int);
		num = (unsigned long long)n;
		size = 4;
	} else if (width == LEN_MOD_LONG) {
		unsigned long n = (unsigned long) VA_ARG(ap, long);
		num = (unsigned long long)n;
		size = 8;
	} else {
		unsigned long long n = (unsigned long long) VA_ARG(ap, long long);
		num = (unsigned long long)n;
		size = 8;
	}

	tmp = buffer + sizeof(buffer);

	tmp--;
	*tmp = '\0';
	while (size--) {
		tmp--;
		*tmp = map[num & 0xf];
		num >>= 4;

		tmp--;
		*tmp = map[num & 0xf];
		num >>= 4;
	}

	while (*tmp) {
		if (cur < end)
			*cur = *tmp;

		cur++;
		tmp++;
	}

	return cur;
}

static char *format_base10(char *cur, char *end, int width, bool signed_format, VA_LIST ap)
{
	unsigned long long num;
	char *tmp, buffer[32];

	if (width == LEN_MOD_HALF_HALF) {
		unsigned char n = (unsigned char) VA_ARG(ap, int);
		if (signed_format && (char)n < 0) {
			if (cur < end)
				*cur++ = '-';
			n = -(char)n;
		}
		num = (unsigned long long)n;
	} else if (width == LEN_MOD_HALF) {
		unsigned short n = (unsigned short) VA_ARG(ap, int);
		if (signed_format && (short)n < 0) {
			if (cur < end)
				*cur++ = '-';
			n = -(short)n;
		}
		num = (unsigned long long)n;
	} else if (width == LEN_MOD_INT) {
		unsigned int n = (unsigned int) VA_ARG(ap, int);
		if (signed_format && (int)n < 0) {
			if (cur < end)
				*cur++ = '-';
			n = -(int)n;
		}
		num = (unsigned long long)n;
	} else if (width == LEN_MOD_LONG) {
		unsigned long n = (unsigned long) VA_ARG(ap, long);
		if (signed_format && (long)n < 0) {
			if (cur < end)
				*cur++ = '-';
			n = -(long)n;
		}
		num = (unsigned long long)n;
	} else {
		unsigned long long n = (unsigned long long) VA_ARG(ap, long long);
		if (signed_format && (long long)n < 0) {
			if (cur < end)
				*cur++ = '-';
			n = -(long long)n;
		}
		num = (unsigned long long)n;
	}

	tmp = buffer + sizeof(buffer);

	tmp--;
	*tmp = '\0';
	do {
		tmp--;
		*tmp = (char)('0' + num % 10);

		num /= 10;
	} while (num);

	while (*tmp) {
		if (cur < end)
			*cur = *tmp;

		cur++;
		tmp++;
	}

	return cur;
}

int vsnprints(char *str, size_t size, const char *format, VA_LIST ap)
{
	unsigned int width;
	char *cur, *end;
	bool convert;

	cur = str;
	end = cur + size;
	if (end < cur) {
		end = (void *)-1;
		size = end - cur;
	}

	convert = false;
	while (*format) {
		if (!convert) {
			if (*format != '%') {
				if (cur < end)
					*cur = *format;

				cur++;
				format++;
				continue;
			}

			format++;
			if (*format == '%') {
				if (cur < end)
					*cur = '%';

				cur++;
				format++;
				continue;
			}

			convert = true;
			width = LEN_MOD_INT;
		} else {
			bool signed_format = false;

			switch (*format) {
			case 'h':
				width--;
				if (width == LEN_MOD_INVALID)
					convert = false;
				break;
			case 'l':
				width++;
				if (width == LEN_MOD_MAX)
					convert = false;
				break;

			case 'd':
				signed_format = true;
			case 'u':
				cur = format_base10(cur, end, width, signed_format, ap);
				convert = false;
				break;

			case 'p':
				width = LEN_MOD_LONG;
			case 'x':
				cur = format_base16(cur, end, width, ap);
				convert = false;
				break;

			case 's': {
				cur = format_string(cur, end, ap);
				convert = false;
				break;
			}

			default:
				convert = false;
			}

			format++;
		}
	}

	if (size) {
		if (cur < end)
			*cur = '\0';
		else
			*(end - 1) = '\0';
	}

	return cur - str;
}

int vprints(const char *format, VA_LIST ap)
{
	char buffer[256];
	int ret;

	ret = vsnprints(buffer, sizeof(buffer), format, ap);
	if (ret >= sizeof(buffer))
		buffer[255] = '\0';

	serial_out(buffer);

	return ret;
}
