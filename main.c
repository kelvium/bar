#include "basic.h"
#include "alsa.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>

static Meminfo  sMeminfo;
static Diskinfo sDiskinfo;

enum {
	OPTION_ONCE,
	OPTION_LOOP,
};

static void printInfo(void)
{
	char date[64] = { 0 };

	meminfoFill(&sMeminfo);
	diskinfoFill(&sDiskinfo, "/");
	dateGet(date, sizeof(date));

	printf("󰋋 %u%%  %zu MiB 󰋊 %zu MiB  %s",
		alsaVolume(),
		(sMeminfo.total - sMeminfo.available) / 1024,
		sDiskinfo.used / 1024 / 1024,
		date);
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
