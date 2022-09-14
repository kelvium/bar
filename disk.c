#include "disk.h"

#include <sys/statvfs.h>

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
