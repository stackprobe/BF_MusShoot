#define MAPDATA_DEFAULT "*"

char *PL_ReadLine(autoList<char *> *lines, int index, char *defaultValue);
int PL_ReadInt(autoList<char *> * lines, int index, int defaultValue);
double PL_ReadDouble(autoList<char *> *lines, int index, double defaultValue);

typedef struct MapCellData_st
{
	char *TopLine;
	autoList<char *> *CommonParamLines;
	autoList<char *> *ParamLines;
}
MapCellData_t;

MapCellData_t *CreateMapCellData();
void ReleaseMapCellData(MapCellData_t *i);

void LoadMapData(autoList<MapCellData_t *> *outList, textImageReader *reader);
