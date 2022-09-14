#include "meminfo.h"
#include "date.h"
#include "disk.h"

#include <stdio.h>

int main(void)
{
	char date[64] = { 0 };

	meminfoUpdate();
	dateGet(date, sizeof(date));

	printf("\uf15b %zu MiB \uf7c9 %zu MiB \uf133 %s", meminfoUsed() / 1024, diskUsed("/") / 1024 / 1024, date);
	return 0;
}
