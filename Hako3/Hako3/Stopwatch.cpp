#include "Stdinc.h"

#define TIMETABLE_MAX 10

static int TimeTable[TIMETABLE_MAX];
static int TimeIndex = -1;

void SW_Start2(void)
{
	errorCase(TIMETABLE_MAX - 1 <= TimeIndex);

	TimeIndex++;
	TimeTable[TimeIndex] = GetNowCount();
}
void SW_Lap2(char *source, int lineno, char *function)
{
	errorCase(TimeIndex < 0);

	int lapTime = GetNowCount() - TimeTable[TimeIndex];

	if(2 <= lapTime)
	{
		fprintf(GetLogFp(),
			"[LAP] %08d (%08d) %s %d %s: %d\n"
			,FrameCount
			,LFrmCnt
			,source
			,lineno
			,function
			,lapTime
			);
	}
	TimeTable[TimeIndex] = GetNowCount();
}
void SW_End2(char *source, int lineno, char *function)
{
	SW_Lap2(source, lineno, function);
	TimeIndex--;
}
