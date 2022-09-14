#include "date.h"

#include <time.h>
#include <stdio.h>

void dateGet(char* buffer, size_t bufferSize)
{
	time_t rawTime;
	struct tm* timeInfo;
	time(&rawTime);
	timeInfo = localtime(&rawTime);

	snprintf(buffer, bufferSize, "%s", asctime(timeInfo));
}
