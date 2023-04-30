#include "basic.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

static uint64_t sGetField(const char* buffer, const char* field)
{
	char* position = strstr(buffer, field);
	if (!position) return 0;

	uint64_t value = strtoll(position + strlen(field), NULL, 10);
	return value;
}

void meminfoFill(Meminfo* self)
{
	char buffer[2048] = { 0 };
	FILE* fd;

	fd = fopen("/proc/meminfo", "r");
	rewind(fd);
	fread(buffer, sizeof(buffer), 1, fd);

	self->total     = sGetField(buffer, "MemTotal:");
	self->free      = sGetField(buffer, "MemFree:");
	self->available = sGetField(buffer, "MemAvailable:");

	fclose(fd);
}

void diskinfoFill(Diskinfo* self, const char* path)
{
	statvfs(path, &self->_stat);
	self->total = self->_stat.f_bsize * self->_stat.f_blocks;
	self->free  = self->_stat.f_bsize * self->_stat.f_bfree;
	self->used  = self->total - self->free;
}

void dateGet(char* buffer, size_t bufferSize)
{
	time_t rawTime;
	struct tm* timeInfo;
	time(&rawTime);
	timeInfo = localtime(&rawTime);
	snprintf(buffer, bufferSize, "%s", asctime(timeInfo)); /* FIXME: asctime is deprecated! */
}
