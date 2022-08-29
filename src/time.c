#include <time.h>
#include <stdio.h>
#include <sys/types.h>


clock_t clock(void) {
	//printf("%s, reached dummy stub\n", __func__);
	return __rdtsc();
}

uint64_t secs;

int clock_gettime(clockid_t clk_id, struct timespec *tp) {

	(void) clk_id;
	//(void) tp;
	if (tp) {
		tp->tv_nsec = __rdtsc();
		tp->tv_sec = secs++;
	}

	//printf("%s, sec %lu nsec %lu\n", __func__, tp->tv_sec, tp->tv_nsec);
	return 0;
}

//  time() returns the time as the number of seconds since the Epoch
time_t time(time_t *tloc) {
	(void)tloc;
	time_t t = __rdtsc();
	//printf("%s, %lu \n", __func__, t);
	return t;
}

int gettimeofday(struct timeval *restrict tv, void *restrict tz)
{
        if (!tv) return 0;
        tv->tv_sec = clock();
        tv->tv_usec = 0;
        return 0;
}
