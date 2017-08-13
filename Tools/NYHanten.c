#include "C:\Factory\Common\all.h"
#include "C:\Factory\SubTools\libs\bmp.h"

static void TwistNaname(autoList_t *table)
{
	uint rowcnt = getCount(table);
	uint colcnt = getCount(getList(table, 0));
	uint rowidx;
	uint colidx;

	for(rowidx = 0; rowidx < rowcnt; rowidx++)
	for(colidx = 0; colidx < colcnt; colidx++)
	{
		if(rowidx < colidx)
		{
			uint a = getElement(getList(table, rowidx), colidx);
			uint b = getElement(getList(table, colidx), rowidx);

			setElement(getList(table, rowidx), colidx, b);
			setElement(getList(table, colidx), rowidx, a);
		}
	}
}
static void TwistYoko(autoList_t *table)
{
	uint rowcnt = getCount(table);
	uint rowidx;

	for(rowidx = 0; rowidx < rowcnt; rowidx++)
	{
		reverseElements(getList(table, rowidx));
	}
}
static void NYHanten(char *inpFile, char *outFile, char *cmds)
{
	autoList_t *table = readBMPFile(inpFile);
	char *p;

	cout("< %s\n", inpFile);
	cout("> %s\n", outFile);

	for(p = cmds; *p; p++)
	{
		switch(*p)
		{
		case 'N':
			TwistNaname(table);
			break;

		case 'Y':
			TwistYoko(table);
			break;

		defualt:
			error();
		}
	}
	writeBMPFile_cx(outFile, table);
}
int main(int argc, char **argv)
{
	char *cmds = NULL;

	if(argIs("/T")) // 縦に
	{
		cmds = "NYN";
	}
	if(argIs("/Y")) // 横に
	{
		cmds = "Y";
	}
	if(argIs("/T90")) // 時計回り90°
	{
		cmds = "NY";
	}
	if(argIs("/T180")) // 時計回り180°
	{
		cmds = "NYNY";
	}
	if(argIs("/T270") || argIs("/HT90")) // 時計回り270°== 反時計回り90°
	{
		cmds = "YN";
//		cmds = "NYNYNY";
	}
	errorCase(!cmds);

	if(argIs("/OverWrite"))
	{
		char *path = getArg(0);

		if(existDir(path))
		{
			autoList_t *files = lssFiles(path);
			char *file;
			uint index;

			foreach(files, file, index)
			{
				NYHanten(file, file, cmds);
			}
			releaseDim(files, 1);
		}
		else
			NYHanten(path, path, cmds);

		return;
	}
	NYHanten(getArg(0), getArg(1), cmds);
}
