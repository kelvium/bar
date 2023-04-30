#pragma once

#include <stddef.h>
#include <stdint.h>

void meminfoUpdate(void);
uint64_t meminfoTotal(void);
uint64_t meminfoFree(void);
uint64_t meminfoAvailable(void);
uint64_t meminfoUsed(void);

uint64_t diskUsed(const char* path);
uint64_t diskFree(const char* path);

void dateGet(char* buffer, size_t bufferSize);
