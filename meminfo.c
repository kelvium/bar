#include "meminfo.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

static uint64_t sTotal     = 0;
static uint64_t sFree      = 0;
static uint64_t sAvailable = 0;

uint64_t meminfoTotal() { return sTotal; }

uint64_t meminfoFree() { return sFree; }

uint64_t meminfoAvailable() { return sAvailable; }

static uint64_t sGetField(const char* buffer, const char* field)
{
	char* position = strstr(buffer, field);
	if (!position) return 0;

	uint64_t value = strtoll(position + strlen(field), NULL, 10);
	return value;
}

void meminfoUpdate()
{
	char buffer[4096] = { 0 };
	FILE* fd;

	fd = fopen("/proc/meminfo", "r");
	rewind(fd);
	fread(buffer, sizeof(buffer), 1, fd);

	sTotal     = sGetField(buffer, "MemTotal:");
	sFree      = sGetField(buffer, "MemFree:");
	sAvailable = sGetField(buffer, "MemAvailable:");

	fclose(fd);
}
