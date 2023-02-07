/** @file
  Root include file of C runtime library to support building the third-party
  cryptographic library.

Copyright (c) 2010 - 2022, Intel Corporation. All rights reserved.<BR>
Copyright (c) 2020, Hewlett Packard Enterprise Development LP. All rights reserved.<BR>
SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#ifndef __CRT_LIB_SUPPORT_H__
#define __CRT_LIB_SUPPORT_H__

//#include <Library/BaseLib.h>
//#include <Library/BaseMemoryLib.h>
//#include <Library/DebugLib.h>
//#include <Library/PrintLib.h>

//#include "BaseTypes.h"
#include "ProcessorBind.h"

#define __BYTE_ORDER 1234
#define __LITTLE_ENDIAN 1234
#define __BIG_ENDIAN 4321

#define UCHAR_MAX 255

#define CONST     const
#define STATIC    static
#define VOID      void

#ifndef TRUE
//
// BugBug: UEFI specification claims 1 and 0. We are concerned about the
//  compiler portability so we did it this way.
//
#define TRUE  ((BOOLEAN)(1==1))
#endif

#ifndef FALSE
#define FALSE ((BOOLEAN)(0==1))
#endif

#define true 1
#define false 0
#define bool _Bool


#ifndef NULL
#define NULL  ((VOID *) 0)
#endif

#define MAX_STRING_SIZE  0x1000

//
// We already have "no-ui" in out Configure invocation.
// but the code still fails to compile.
// Ref:  https://github.com/openssl/openssl/issues/8904
//
// This is defined in CRT library(stdio.h).
//
#ifndef BUFSIZ
#define BUFSIZ  8192
#endif

//
// OpenSSL relies on explicit configuration for word size in crypto/bn,
// but we want it to be automatically inferred from the target. So we
// bypass what's in <openssl/opensslconf.h> for OPENSSL_SYS_UEFI, and
// define our own here.
//
#ifdef CONFIG_HEADER_BN_H
  #error CONFIG_HEADER_BN_H already defined
#endif

#define CONFIG_HEADER_BN_H

//#define SIXTY_FOUR_BIT
//#define SIXTY_FOUR_BIT_LONG

#if !defined (SIXTY_FOUR_BIT) && !defined (THIRTY_TWO_BIT)
  #if defined (MDE_CPU_X64) || defined (MDE_CPU_AARCH64) || defined (MDE_CPU_IA64) || defined (MDE_CPU_RISCV64)
//
// With GCC we would normally use SIXTY_FOUR_BIT_LONG, but MSVC needs
// SIXTY_FOUR_BIT, because 'long' is 32-bit and only 'long long' is
// 64-bit. Since using 'long long' works fine on GCC too, just do that.
//
#define SIXTY_FOUR_BIT_LONG
  #elif defined (MDE_CPU_IA32) || defined (MDE_CPU_ARM) || defined (MDE_CPU_EBC)
#define THIRTY_TWO_BIT
  #else
    #error Unknown target architecture
  #endif
#endif

///
/// Variable used to traverse the list of arguments. This type can vary by
/// implementation and could be an array or structure.
///
typedef __builtin_va_list VA_LIST;

#define VA_START(Marker, Parameter)  __builtin_va_start (Marker, Parameter)

#define VA_ARG(Marker, TYPE)  ((sizeof (TYPE) < sizeof (UINTN)) ? (TYPE)(__builtin_va_arg (Marker, UINTN)) : (TYPE)(__builtin_va_arg (Marker, TYPE)))

#define VA_END(Marker)  __builtin_va_end (Marker)

#define VA_COPY(Dest, Start)  __builtin_va_copy (Dest, Start)


//
// Map all va_xxxx elements to VA_xxx defined in MdePkg/Include/Base.h
//
#if !defined (__CC_ARM) // if va_list is not already defined
#define va_list   VA_LIST
#define va_arg    VA_ARG
#define va_start  VA_START
#define va_end    VA_END
#define va_copy   VA_COPY
#else // __CC_ARM
#define va_start(Marker, Parameter)  __va_start(Marker, Parameter)
#define va_arg(Marker, TYPE)         __va_arg(Marker, TYPE)
#define va_end(Marker)               ((void)0)
#endif

//
// Definitions for global constants used by CRT library routines
//
#define ENOENT           2
#define EINVAL        22              /* Invalid argument */
#define EAFNOSUPPORT  47              /* Address family not supported by protocol family */
#define EOVERFLOW       75

#define INT_MAX       0x7FFFFFFF      /* Maximum (signed) int value */
#define INT_MIN       (-INT_MAX-1)    /* Minimum (signed) int value */
#define LONG_MAX      0X7FFFFFFFL     /* max value for a long */
#define LONG_MIN      (-LONG_MAX-1)   /* min value for a long */
#define UINT_MAX      0xFFFFFFFF      /* Maximum unsigned int value */
#define ULONG_MAX     0xFFFFFFFF      /* Maximum unsigned long value */
#define CHAR_BIT      8               /* Number of bits in a char */


//
// Address families.
//
#define AF_INET   2     /* internetwork: UDP, TCP, etc. */
#define AF_INET6  24    /* IP version 6 */

//
// Define constants based on RFC0883, RFC1034, RFC 1035
//
#define NS_INT16SZ    2   /*%< #/bytes of data in a u_int16_t */
#define NS_INADDRSZ   4   /*%< IPv4 T_A */
#define NS_IN6ADDRSZ  16  /*%< IPv6 T_AAAA */

//
// Basic types mapping
//
typedef UINTN   size_t;
typedef UINTN   u_int;
typedef INTN    ptrdiff_t;
typedef INTN    ssize_t;
typedef INT64   time_t;
typedef UINT8   __uint8_t;
typedef UINT8   sa_family_t;
typedef UINT8   u_char;
typedef UINT32  uid_t;
typedef UINT32  gid_t;
typedef CHAR16  wchar_t;


//
// File operations are not required for EFI building,
// so FILE is mapped to VOID * to pass build
//
typedef VOID *FILE;

//
// Structures Definitions
//
struct tm {
  int     tm_sec;    /* seconds after the minute [0-60] */
  int     tm_min;    /* minutes after the hour [0-59] */
  int     tm_hour;   /* hours since midnight [0-23] */
  int     tm_mday;   /* day of the month [1-31] */
  int     tm_mon;    /* months since January [0-11] */
  int     tm_year;   /* years since 1900 */
  int     tm_wday;   /* days since Sunday [0-6] */
  int     tm_yday;   /* days since January 1 [0-365] */
  int     tm_isdst;  /* Daylight Savings Time flag */
  long    tm_gmtoff; /* offset from CUT in seconds */
  char    *tm_zone;  /* timezone abbreviation */
};

struct timeval {
  long    tv_sec;   /* time value, in seconds */
  long    tv_usec;  /* time value, in microseconds */
};

struct sockaddr {
  __uint8_t      sa_len;      /* total length */
  sa_family_t    sa_family;   /* address family */
  char           sa_data[14]; /* actually longer; address value */
};

// stdint.h

#define __NEED_int8_t
#define __NEED_int16_t
#define __NEED_int32_t
#define __NEED_int64_t

#define __NEED_uint8_t
#define __NEED_uint16_t
#define __NEED_uint32_t
#define __NEED_uint64_t

#define __NEED_intptr_t
#define __NEED_uintptr_t

#define __NEED_intmax_t
#define __NEED_uintmax_t

#define __NEED_time_t
#define __NEED_clock_t
#define __NEED_clockid_t
#define __NEED_struct_timespec

#define __NEED_pid_t

#define __NEED_dev_t
#define __NEED_ino_t
#define __NEED_mode_t
#define __NEED_nlink_t
#define __NEED_uid_t
#define __NEED_gid_t
#define __NEED_off_t
#define __NEED_blksize_t
#define __NEED_blkcnt_t

#include <bits/alltypes.h>

#define STDERR_FILENO 2

#define FILENAME_MAX 4096

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

#define F_GETFL  3
#define F_SETFL  4

#define DECLARE_ARGS(val, low, high)	unsigned long low, high
#define EAX_EDX_VAL(val, low, high)	((low) | (high) << 32)
#define EAX_EDX_RET(val, low, high)	"=a" (low), "=d" (high)

static inline unsigned long long rdtsc(void)
{
	DECLARE_ARGS(val, low, high);

	asm volatile("rdtsc" : EAX_EDX_RET(val, low, high));

	return EAX_EDX_VAL(val, low, high);
}

#define CLOCK_REALTIME           0
#define CLOCK_MONOTONIC          1
#define CLOCK_PROCESS_CPUTIME_ID 2
#define CLOCK_THREAD_CPUTIME_ID  3
#define CLOCK_MONOTONIC_RAW      4

#define INTPTR_MIN      INT64_MIN
#define INTPTR_MAX      INT64_MAX
#define UINTPTR_MAX     UINT64_MAX
#define PTRDIFF_MIN     INT64_MIN
#define PTRDIFF_MAX     INT64_MAX

#define INT8_MIN   (-1-0x7f)
#define INT16_MIN  (-1-0x7fff)
#define INT32_MIN  (-1-0x7fffffff)
#define INT64_MIN  (-1-0x7fffffffffffffff)

#define INT8_MAX   (0x7f)
#define INT16_MAX  (0x7fff)
#define INT32_MAX  (0x7fffffff)
#define INT64_MAX  (0x7fffffffffffffff)

#define UINT8_MAX  (0xff)
#define UINT16_MAX (0xffff)
#define UINT32_MAX (0xffffffffu)
#define UINT64_MAX (0xffffffffffffffffu)

#if UINTPTR_MAX == UINT64_MAX
#define __PRI64  "l"
#define __PRIPTR "l"
#else
#define __PRI64  "ll"
#define __PRIPTR ""
#endif


#define PRIu8  "u"
#define PRIu16 "u"
#define PRIu32 "u"
#define PRIu64 __PRI64 "u"


typedef unsigned long __jmp_buf[8];

typedef struct __jmp_buf_tag {
	__jmp_buf __jb;
	unsigned long __fl;
	unsigned long __ss[128/sizeof(long)];
} jmp_buf[1];

#if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 1)
#define __setjmp_attr __attribute__((__returns_twice__))
#else
#define __setjmp_attr
#endif

//
// Global variables
//
extern int   errno;
extern FILE  *stderr;

//
// Function prototypes of CRT Library routines
//
void           *
malloc     (
  size_t
  );

void           *
realloc    (
  void *,
  size_t
  );

void
free        (
  void *
  );

void           *
memset     (
  void *,
  int,
  size_t
  );

int
memcmp      (
  const void *,
  const void *,
  size_t
  );

int
isdigit     (
  int
  );

int
isspace     (
  int
  );

int
isxdigit    (
  int
  );

int
isalnum     (
  int
  );

int
isupper     (
  int
  );

int
tolower     (
  int
  );

int
strcmp      (
  const char *,
  const char *
  );

int
strncasecmp (
  const char *,
  const char *,
  size_t
  );

char           *
strchr     (
  const char *,
  int
  );

char           *
strrchr    (
  const char *,
  int
  );

unsigned long
strtoul     (
  const char *,
  char **,
  int
  );

long
strtol      (
  const char *,
  char **,
  int
  );

char           *
strerror   (
  int
  );

size_t
strspn      (
  const char *,
  const char *
  );

size_t
strcspn     (
  const char *,
  const char *
  );

int
printf      (
  const char *,
  ...
  );

int
sscanf      (
  const char *,
  const char *,
  ...
  );

FILE           *
fopen      (
  const char *,
  const char *
  );

size_t
fread       (
  void *,
  size_t,
  size_t,
  FILE *
  );

size_t
fwrite      (
  const void *,
  size_t,
  size_t,
  FILE *
  );

int
fclose      (
  FILE *
  );

int
ferror      (
  FILE *
  );

int
fprintf     (
  FILE *,
  const char *,
  ...
  );

time_t
time        (
  time_t *
  );

struct tm      *
gmtime     (
  const time_t *
  );

uid_t
getuid      (
  void
  );

uid_t
geteuid     (
  void
  );

gid_t
getgid      (
  void
  );

gid_t
getegid     (
  void
  );

int
issetugid   (
  void
  );

void
qsort       (
  void *,
  size_t,
  size_t,
  int (*)(const void *, const void *)
  );

char           *
getenv     (
  const char *
  );

char           *
secure_getenv (
  const char *
  );

#if defined (__GNUC__) && (__GNUC__ >= 2)
void
abort       (
  void
  ) __attribute__ ((__noreturn__));

#else
void
abort       (
  void
  );

#endif
int
inet_pton   (
  int,
  const char *,
  void *
  );

char *
strcpy (
  char        *strDest,
  const char  *strSource
  );

size_t strlen(const char *s);

void *memcpy(void *restrict dest, const void *restrict src, size_t n);

char *__strchrnul(const char *s, int c);

char *__stpcpy(char *restrict d, const char *restrict s);

char *__stpncpy(char *restrict d, const char *restrict s, size_t n);

char *strstr(const char *h, const char *n);

void *memchr(const void *src, int c, size_t n);

int vasprintf(char **s, const char *fmt, va_list ap);

int asprintf(char **s, const char *fmt, ...);

int vsnprintf(char *restrict s, size_t n, const char *restrict fmt, va_list ap);

int snprintf(char *restrict s, size_t n, const char *restrict fmt, ...);

char *strdup(const char *s);

int dprintf(int fd, const char *__restrict fmt, ...);

int vdprintf(int fd, const char *restrict fmt, va_list ap);

int fseek(FILE *f, long off, int whence);

long ftell(FILE *f);

int remove(const char *path);

clock_t clock(void);

int clock_gettime(clockid_t clk_id, struct timespec *tp);

int gettimeofday(struct timeval *restrict tv, void *restrict tz);

int rand(void);

void srand(unsigned s);

pid_t getpid(void);

void *memmove(void *dest, const void *src, size_t n);

int setjmp (jmp_buf) __setjmp_attr;
_Noreturn void longjmp (jmp_buf, int);

#ifdef NDEBUG
#define	assert(x) (void)0
#else
#define assert(x) ((void)((x) || (__assert_fail(#x, __FILE__, __LINE__, __func__),0)))
#endif

_Noreturn void __assert_fail (const char *, const char *, int, const char *);

int fflush(FILE *f);

int atoi(const char *s);

char *strncpy(char *restrict d, const char *restrict s, size_t n);

int strncmp(const char *_l, const char *_r, size_t n);

int   toupper(int);

char *strncat (char *__restrict, const char *__restrict, size_t);

//ssize_t send (int, const void *, size_t, int);

//ssize_t recv (int, void *, size_t, int);

int close(int fd);

int strcasecmp(const char *_l, const char *_r);

int atexit(void (*func)(void));

int fcntl(int fd, int cmd, ...);

time_t mktime(struct tm *tm);

char *ctime(const time_t *t);

int isascii(int c);

#define OFFSET_OF(TYPE, Field)  ((UINTN) __builtin_offsetof(TYPE, Field))
#define offsetof(type, member)  OFFSET_OF(type,member)

#define weak __attribute__((__weak__))
#define hidden __attribute__((__visibility__("hidden")))
#define weak_alias(old, new) \
        extern __typeof(old) new __attribute__((__weak__, __alias__(#old)))

#endif
