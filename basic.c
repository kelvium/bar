#include "basic.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/statvfs.h>
#include <time.h>
#include <unistd.h>

static uint64_t sMeminfoTotal     = 0;
static uint64_t sMeminfoFree      = 0;
static uint64_t sMeminfoAvailable = 0;

uint64_t meminfoTotal(void) { return sMeminfoTotal; }
uint64_t meminfoFree(void) { return sMeminfoFree; }
uint64_t meminfoAvailable(void) { return sMeminfoAvailable; }
uint64_t meminfoUsed(void) { return sMeminfoTotal - sMeminfoAvailable; }

static uint64_t sGetField(const char* buffer, const char* field)
{
	char* position = strstr(buffer, field);
	if (!position) return 0;

	uint64_t value = strtoll(position + strlen(field), NULL, 10);
	return value;
}

void meminfoUpdate(void)
{
	char buffer[2048] = { 0 };
	FILE* fd;

	fd = fopen("/proc/meminfo", "r");
	rewind(fd);
	fread(buffer, sizeof(buffer), 1, fd);

	sMeminfoTotal     = sGetField(buffer, "MemTotal:");
	sMeminfoFree      = sGetField(buffer, "MemFree:");
	sMeminfoAvailable = sGetField(buffer, "MemAvailable:");

	fclose(fd);
}

uint64_t diskUsed(const char* path)
{
	struct statvfs diskStat;
	statvfs(path, &diskStat);
	return (diskStat.f_bsize * diskStat.f_blocks) - (diskStat.f_bsize * diskStat.f_bfree);
}

uint64_t diskFree(const char* path)
{
	struct statvfs diskStat;
	statvfs(path, &diskStat);
	return diskStat.f_bsize * diskStat.f_bfree;
}

void dateGet(char* buffer, size_t bufferSize)
{
	time_t rawTime;
	struct tm* timeInfo;
	time(&rawTime);
	timeInfo = localtime(&rawTime);
	snprintf(buffer, bufferSize, "%s", asctime(timeInfo)); /* FIXME: asctime is deprecated! */
}
