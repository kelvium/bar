#include "basic.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>

enum {
	OPTION_ONCE,
	OPTION_LOOP,
};

static void printInfo(void)
{
	char date[64] = { 0 };

	meminfoUpdate();
	dateGet(date, sizeof(date));

	printf("\uf15b %zu MiB \uf7c9 %zu MiB \uf133 %s", meminfoUsed() / 1024, diskUsed("/") / 1024 / 1024, date);
}

static void printUsage(const char* name)
{
	printf("%s [(once|loop)]", name);
}

int main(int argc, char** argv)
{
	uint8_t option = OPTION_ONCE;
	if (argc >= 2) {
		if (!strcmp(argv[1], "once"))
			option = OPTION_ONCE;
		else if (!strcmp(argv[1], "loop"))
			option = OPTION_LOOP;
		else {
			printUsage(argv[0]);
			return 1;
		}
	}

	switch (option) {
	case OPTION_ONCE: {
		printInfo();
	} break;
	case OPTION_LOOP: {
		for (;;) {
			printInfo();
			sleep(1);
		}
	} break;
	}
	return 0;
}
