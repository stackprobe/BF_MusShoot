#include "C:\Factory\Common\all.h"
#include "C:\Factory\SubTools\libs\bmp.h"

static void Hanten(char *file)
{
	autoList_t *table = readBMPFile(file);
	autoList_t *row;
	uint rowidx;
	uint cell;
	uint colidx;

	foreach(table, row, rowidx)
	foreach(row, cell, colidx)
	{
		setElement(row, colidx, cell ^ 0xffffff);
	}
	writeBMPFile_cx(file, table);
}
int main(int argc, char **argv)
{
	errorCase(!argIs("/OverWrite"));

	if(argIs("/D"))
	{
		autoList_t *files = lssFiles(nextArg());
		char *file;
		uint index;

		foreach(files, file, index)
		{
			if(!_stricmp("bmp", getExt(file)))
			{
				Hanten(file);
			}
		}
		releaseDim(files, 1);
		return;
	}
	Hanten(nextArg());
}
