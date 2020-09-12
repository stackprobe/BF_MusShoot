#include "Stdinc.h"

char *PL_ReadLine(autoList<char *> *lines, int index, char *defaultValue)
{
	errorCase(index < 0);

	if(lines->GetCount() <= index)
		return defaultValue;

	char *line = lines->GetElement(index);

	if(line[0] == MAPDATA_DEFAULT[0])
		return defaultValue;

	return line;
}
int PL_ReadInt(autoList<char *> * lines, int index, int defaultValue)
{
	char *line = PL_ReadLine(lines, index, MAPDATA_DEFAULT);

	if(line[0] == MAPDATA_DEFAULT[0])
		return defaultValue;

	return atoi(line);
}
double PL_ReadDouble(autoList<char *> *lines, int index, double defaultValue)
{
	char *line = PL_ReadLine(lines, index, MAPDATA_DEFAULT);

	if(line[0] == MAPDATA_DEFAULT[0])
		return defaultValue;

	return toDouble(line);
}

// <== PL_Read_

MapCellData_t *CreateMapCellData(char *bind_line, autoList<char *> *bind_cpl, autoList<char *> *bind_pl)
{
	MapCellData_t *i = nb_(MapCellData_t);

	i->TopLine = bind_line;
	i->CommonParamLines = bind_cpl;
	i->ParamLines = bind_pl;

	return i;
}
void ReleaseMapCellData(MapCellData_t *i)
{
	if(!i)
		return;

	memFree(i->TopLine);

	i->CommonParamLines->CallAllElement((void (*)(char *))memFree);
	i->ParamLines->CallAllElement((void (*)(char *))memFree);

	delete i->CommonParamLines;
	delete i->ParamLines;

	memFree(i);
}

void LoadMapData(autoList<MapCellData_t *> *outList, textImageReader *reader)
{
	for(; ; )
	{
		char *line = reader->ReadLine();

		if(!line)
			break;

		if(line[0])
		{
			autoList<char *> *pl_a = reader->ReadLineListBlock();
			autoList<char *> *pl_b = reader->ReadLineListBlock();

			outList->AddElement(CreateMapCellData(line, pl_a, pl_b));
		}
		else
		{
			memFree(line);
			outList->AddElement(NULL);
		}
	}
}
