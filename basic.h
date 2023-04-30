#pragma once

#include <stddef.h>
#include <stdint.h>
#include <sys/statvfs.h>

typedef struct {
	uint64_t total;
	uint64_t free;
	uint64_t available;
} Meminfo;

void meminfoFill(Meminfo* self);

typedef struct {
	struct statvfs _stat;

	uint64_t total;
	uint64_t free;
	uint64_t used;
} Diskinfo;

void diskinfoFill(Diskinfo* self, const char* path);

void dateGet(char* buffer, size_t bufferSize);
