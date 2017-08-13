#include "C:\Factory\Common\all.h"
#include "C:\Factory\SubTools\libs\bmp.h"

static uint GetCell(autoList_t *srcBmp, uint xPos, uint yPos, uint xSize, uint ySize)
{
	uint x;
	uint y;
	uint cR = 0;
	uint cG = 0;
	uint cB = 0;
	uint cNum;

	for(x = 0; x < xSize; x++)
	for(y = 0; y < ySize; y++)
	{
		autoList_t *row = (autoList_t *)refElement(srcBmp, yPos + y);
		uint cell;

		cell = row ? refElement(row, xPos + x) : 0;

		cR += cell >> 16 & 0xff;
		cG += cell >>  8 & 0xff;
		cB += cell >>  0 & 0xff;
	}
	cNum = xSize * ySize;

	cR /= cNum;
	cG /= cNum;
	cB /= cNum;

	return cR << 16 | cG << 8 | cB;
}
static void ToSmall(char *file, char *destFile, uint src_l, uint src_t, uint dest_w, uint dest_h, uint srcRate)
{
	autoList_t *srcBmp = readBMPFile(file);
	autoList_t *destBmp = newList();
	uint x;
	uint y;

	errorCase(dest_w < 1);
	errorCase(dest_h < 1);
	errorCase(srcRate < 1);

	for(y = 0; y < dest_h; y++)
	{
		autoList_t *row = newList();

		for(x = 0; x < dest_w; x++)
		{
			addElement(row, GetCell(
				srcBmp,
				src_l + x * srcRate,
				src_t + y * srcRate,
				srcRate,
				srcRate
				));
		}
		addElement(destBmp, (uint)row);
	}
	writeBMPFile(destFile, destBmp);

	releaseDim_BR(srcBmp, 2, NULL);
	releaseDim_BR(destBmp, 2, NULL);
}
int main(int argc, char **argv)
{
	if(argIs("/RES"))
	{
		char *resFile;
		char *smallDir;
		char *sameSizeDir;
		autoList_t *resLines;
		char *resLine;
		uint index;

		resFile = nextArg();
		smallDir = nextArg();
		sameSizeDir = nextArg();
		resLines = readResourceLines(resFile);

		foreach(resLines, resLine, index)
		{
			autoList_t *resTokens = ucTokenize(resLine);
			char *srcBmpFile;
			uint src_l;
			uint src_t;
			uint src_w;
			uint src_h;
			uint srcRate;
			char *smallBmpFile;
			char *sameSizeBmpFile;

			srcBmpFile = getLine(resTokens, 0);
			src_l = toValue(getLine(resTokens, 1));
			src_t = toValue(getLine(resTokens, 2));
			src_w = toValue(getLine(resTokens, 3));
			src_h = toValue(getLine(resTokens, 4));
			srcRate = toValue(getLine(resTokens, 5));

			smallBmpFile = combine_cx(smallDir, xcout("Small_%010u.bmp", index));
			sameSizeBmpFile = combine_cx(sameSizeDir, xcout("%010u.bmp", index));

			ToSmall(
				srcBmpFile,
				smallBmpFile,
				src_l,
				src_t,
				src_w,
				src_h,
				srcRate
				);
			ToSmall(
				srcBmpFile,
				sameSizeBmpFile,
				src_l,
				src_t,
				src_w * srcRate,
				src_h * srcRate,
				1
				);

			releaseDim(resTokens, 1);
			memFree(smallBmpFile);
			memFree(sameSizeBmpFile);
		}
		releaseDim(resLines, 1);
		return;
	}

	ToSmall(
		getArg(0),
		getArg(1),
		toValue(getArg(2)),
		toValue(getArg(3)),
		toValue(getArg(4)),
		toValue(getArg(5)),
		toValue(getArg(6))
		);
}
