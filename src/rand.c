#include <stdlib.h>
#include <stdint.h>

static uint64_t seed;

void srand(unsigned s)
{
	printf("%s called\n", __func__);
	seed = s-1;
}

int rand(void)
{
	printf("%s called\n", __func__);
	seed = 6364136223846793005ULL*seed + 1;
	return seed>>33;
}
