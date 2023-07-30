#include "basic.h"

#include <assert.h>
#include <btrfs/ioctl.h>
#include <fcntl.h>
#include <linux/magic.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/statfs.h>
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
	int error = 0;

	struct statfs pathStat = { 0 };
	error = statfs(path, &pathStat);
	assert(error != -1);

	if (pathStat.f_type == BTRFS_SUPER_MAGIC) {
		int fd = open(path, O_RDONLY);
		assert(fd != -1);

		struct btrfs_ioctl_space_args args = { 0 };
		error = ioctl(fd, BTRFS_IOC_SPACE_INFO, &args);
		assert(error != -1);

		args.space_slots = args.total_spaces;
		error = ioctl(fd, BTRFS_IOC_SPACE_INFO, &args);
		assert(error != -1);

		close(fd);

		struct btrfs_ioctl_space_info* dataInfo = args.spaces + 0;
		self->total = dataInfo->total_bytes;
		self->free  = dataInfo->total_bytes - dataInfo->used_bytes;
		self->used  = dataInfo->used_bytes;
	} else {
		self->total = pathStat.f_bsize * pathStat.f_blocks;
		self->free  = pathStat.f_bsize * pathStat.f_bfree;
		self->used  = self->total - self->free;
	}
}

void dateGet(char* buffer, size_t bufferSize)
{
	time_t rawTime;
	struct tm* timeInfo;
	time(&rawTime);
	timeInfo = localtime(&rawTime);
	snprintf(buffer, bufferSize, "%s", asctime(timeInfo)); /* FIXME: asctime is deprecated! */
}
