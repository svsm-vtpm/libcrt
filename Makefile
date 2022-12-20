# SPDX-License-Identifier: MIT

CFLAGS = -I./include -O3 -nostdinc -nostdlib
CFLAGS		+= -m64 -march=x86-64 -mno-sse2 -fPIE
CFLAGS		+= -fno-stack-protector
CFLAGS		+= -ffreestanding
CC := gcc
PREFIX := /usr/local/

OBJS := $(addprefix src/, \
			 	crt_wrapper.o \
				strcasecmp.o \
				strncasecmp.o \
				strcat.o \
				strchrnul.o \
				strlen.o \
				strcmp.o \
				strchr.o \
				strncat.o \
				strncmp.o \
				stpncpy.o \
				stpcpy.o \
				strcpy.o \
				strncpy.o \
				strstr.o \
				memchr.o \
				memcpy.o \
				memmove.o \
				memset.o \
				memcmp.o \
				snprintf.o \
				vsnprintf.o \
				printf.o \
				strdup.o \
				fseek.o \
				ftell.o \
				time.o \
				rand.o \
				getpid.o \
				assert.o \
				fflush.o \
				setjmp.o \
				asprintf.o \
				vasprintf.o \
				atoi.o \
				gmtime_r.o \
				__secs_to_tm.o \
				fprintf.o \
				fputc.o \
				longjmp.o \
				net.o \
				file.o \
				atexit.o \
				tolower.o \
				toupper.o \
				islower.o \
				isupper.o \
				printf_wrapper.o \
				mktime.o \
				__errno_location.o \
				ctime.o \
				)

all: libcrt.a

install: all
	cp libcrt.a $(PREFIX)

libcrt.a: $(OBJS)
	ar rcs $@ $(OBJS)

%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.o : %.s
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@rm -f libcrt.a
	@rm -f src/*.o
