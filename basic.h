#pragma once

#include <stddef.h>
#include <stdint.h>

typedef struct {
	uint64_t total;
	uint64_t free;
	uint64_t available;
} Meminfo;

void meminfoFill(Meminfo* self);

uint64_t diskUsed(const char* path);
uint64_t diskFree(const char* path);

void dateGet(char* buffer, size_t bufferSize);
