#include <stdlib.h>
#include <stdint.h>

static uint64_t seed;

void srand(unsigned s)
{
	printf("%s called\n", __func__);
	seed = s-1;
}

/* return 0 on success */
static inline int IntelRDrand64(uint64_t *rnd)
{
    unsigned char ok;

    __asm__ volatile("rdrand %0; setc %1":"=r"(*rnd), "=qm"(ok));

    return (ok) ? 0 : -1;
}

int rand(void)
{
  uint64_t r;
  if (IntelRDrand64(&r)) {
    printf("%s, RDRAND failed\n", __func__);
  }
  return r;
}
