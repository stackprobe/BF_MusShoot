/*
	ToTile.exe /S
		[X-TOP] [Y-TOP]
		[TILE-X-SIZE] [TILE-Y-SIZE]
		[X-NUM] [Y-NUM]
		[X-SPAN] [Y-SPAN]
		[BMP-FILE]
		[OUT-DIR]
*/

#include "C:\Factory\Common\all.h"
#include "C:\Factory\SubTools\libs\bmp.h"

static autoList_t *GetTile(autoList_t *mainBmp, uint xTop, uint yTop, uint xSize, uint ySize)
{
	autoList_t *tileBmp = newList();
	uint x;
	uint y;

	for(y = 0; y < ySize; y++)
	{
		autoList_t *tileRow = newList();
		autoList_t *row = (autoList_t *)refElement(mainBmp, yTop + y);

		for(x = 0; x < xSize; x++)
		{
			addElement(tileRow, row ? refElement(row, xTop + x) : 0);
		}
		addElement(tileBmp, (uint)tileRow);
	}
	return tileBmp;
}
static void ToTile(char *file, char *outDir, uint tileXSize, uint tileYSize)
{
	autoList_t *mainBmp = readBMPFile(file);
	uint xSize;
	uint ySize;
	uint x;
	uint y;

	mkAddCwd(outDir);

	xSize = getCount((autoList_t *)getElement(mainBmp, 0));
	ySize = getCount(mainBmp);

	for(y = 0; y < ySize; y += tileYSize)
	{
		mkAddCwd_x(xcout("%010u", y));

		for(x = 0; x < xSize; x += tileXSize)
		{
			writeBMPFile_xx(xcout("%010u.bmp", x), GetTile(mainBmp, x, y, tileXSize, tileYSize));
		}
		unaddCwd();
	}
	unaddCwd();
}
static void ToTileEx(char *file, char *outDir, uint xTop, uint yTop, uint tileXSize, uint tileYSize, uint xNum, uint yNum, uint xStep, uint yStep)
{
	autoList_t *mainBmp = readBMPFile(file);
	uint x;
	uint y;

	mkAddCwd(outDir);

	for(y = 0; y < yNum; y++)
	{
		mkAddCwd_x(xcout("%010u", y));

		for(x = 0; x < xNum; x++)
		{
			writeBMPFile_xx(xcout("%010u.bmp", x), GetTile(
				mainBmp,
				xTop + x * xStep,
				yTop + y * yStep,
				tileXSize,
				tileYSize
				));
		}
		unaddCwd();
	}
	unaddCwd();
}
int main(int argc, char **argv)
{
	if(argIs("/S"))
	{
		uint xTop;
		uint yTop;
		uint tileXSize;
		uint tileYSize;
		uint xNum;
		uint yNum;
		uint xStep;
		uint yStep;

		xTop = toValue(nextArg());
		yTop = toValue(nextArg());
		tileXSize = toValue(nextArg());
		tileYSize = toValue(nextArg());
		xNum = toValue(nextArg());
		yNum = toValue(nextArg());
		xStep = toValue(nextArg());
		yStep = toValue(nextArg());

		errorCase(!m_isRange(xTop, 0, 0x10000));
		errorCase(!m_isRange(yTop, 0, 0x10000));
		errorCase(!m_isRange(tileXSize, 1, 0x10000));
		errorCase(!m_isRange(tileYSize, 1, 0x10000));
		errorCase(!m_isRange(xNum, 1, 0x10000));
		errorCase(!m_isRange(yNum, 1, 0x10000));
		errorCase(!m_isRange(xStep, 1, 0x10000 / xNum));
		errorCase(!m_isRange(yStep, 1, 0x10000 / yNum));

		ToTileEx(getArg(0), getArg(1), xTop, yTop, tileXSize, tileYSize, xNum, yNum, xStep, yStep);
		return;
	}
	if(argIs("/64"))
	{
		ToTile(getArg(0), getArg(1), 64, 64);
		return;
	}
	if(argIs("/48"))
	{
		ToTile(getArg(0), getArg(1), 48, 48);
		return;
	}
	if(argIs("/32"))
	{
		ToTile(getArg(0), getArg(1), 32, 32);
		return;
	}
	ToTile(getArg(0), getArg(1), 16, 16);
}
