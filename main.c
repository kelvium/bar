#include "meminfo.h"

#include <stdio.h>

int main(void)
{
	meminfoUpdate();
	printf("Total: %zu MiB\n", meminfoTotal() / 1024);
	printf("Free: %zu MiB\n", meminfoFree() / 1024);
	printf("Available: %zu MiB\n", meminfoAvailable() / 1024);
	printf("Used: %zu MiB\n", (meminfoTotal() - meminfoAvailable()) / 1024);
	return 0;
}
