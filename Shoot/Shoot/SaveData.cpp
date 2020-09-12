#include "Stdinc.h"

#define SAVEDATAFILE "SaveData.dat"
#define CHECKDIGIT 39713971

Sd_t Sd;

static autoQueue<uchar> *FileImage;

static char *ReadLine(void)
{
	return q_readLine(FileImage);
}
static char *c_ReadLine(void)
{
	static char *stock;
	memFree(stock);
	return stock = ReadLine();
}
static void WriteLine(char *line)
{
	q_writeLine(FileImage->GetList(), line);
}
static void WriteLine_x(char *line)
{
	q_writeLine_x(FileImage->GetList(), line);
}
static int ReadInt(int minval, int maxval)
{
	int value = atoi_x(ReadLine());

	m_range(value, minval, maxval);
	return value;
}
static void WriteInt(int value)
{
	WriteLine_x(xcout("%d", value));
}
static double ReadDouble(double minval, double maxval, int scale)
{
	double value = (double)atoi_x(ReadLine()) / scale;

	m_range(value, minval, maxval);
	return value;
}
static void WriteDouble(double value, int scale)
{
	WriteInt(m_d2i(value * scale));
}

static void LoadDefaultSaveData(void)
{
	Sd.ScreenZoom = 1.0;

	Sd.PadBtn.Dir2 = SWPB_DIR_2;
	Sd.PadBtn.Dir4 = SWPB_DIR_4;
	Sd.PadBtn.Dir6 = SWPB_DIR_6;
	Sd.PadBtn.Dir8 = SWPB_DIR_8;
	Sd.PadBtn.A = SWPB_A1;
	Sd.PadBtn.B = SWPB_B1;
	Sd.PadBtn.C = SWPB_A2;
	Sd.PadBtn.D = SWPB_B2;
	Sd.PadBtn.E = SWPB_A3;
	Sd.PadBtn.F = SWPB_B3;
	Sd.PadBtn.L = SWPB_L;
	Sd.PadBtn.R = SWPB_R;
	Sd.PadBtn.Pause = SWPB_DSTART;

	Sd.MusicMasterVolume = 1.0; // 0.0 - 2.0
	Sd.SEMasterVolume    = 1.0; // 0.0 - 2.0

	Sd.PlayerMouseMoveRate = 1.0;
	Sd.WeaponRotMax = 3;
}
void ImportSaveData(void)
{
	memset(&Sd, 0x00, sizeof(Sd_t));

	if(!accessible(SAVEDATAFILE))
	{
		LoadDefaultSaveData();
		return;
	}
LOGPOS();
	FileImage = new autoQueue<uchar>(readBinary(SAVEDATAFILE), IMAX);
LOGPOS();

	if(
		Jammer(FileImage->GetList(), 0) == 0 ||
//		strcmp(__DATE__, c_ReadLine()) != 0 ||
//		strcmp(__TIME__, c_ReadLine()) != 0 ||
		ReadInt(CHECKDIGIT - 1, CHECKDIGIT + 1) != CHECKDIGIT
		)
	{
LOGPOS();
		delete FileImage;
		LoadDefaultSaveData();
		return;
	}
LOGPOS();
	Sd.FullScreenMode = ReadInt(-1, 1);
	Sd.ScreenZoom = ReadDouble(0.1, 10.0, 100);

	Sd.PadBtn.Dir2 = ReadInt(0, 31);
	Sd.PadBtn.Dir4 = ReadInt(0, 31);
	Sd.PadBtn.Dir6 = ReadInt(0, 31);
	Sd.PadBtn.Dir8 = ReadInt(0, 31);
	Sd.PadBtn.A = ReadInt(0, 31);
	Sd.PadBtn.B = ReadInt(0, 31);
	Sd.PadBtn.C = ReadInt(0, 31);
	Sd.PadBtn.D = ReadInt(0, 31);
	Sd.PadBtn.E = ReadInt(0, 31);
	Sd.PadBtn.F = ReadInt(0, 31);
	Sd.PadBtn.L = ReadInt(0, 31);
	Sd.PadBtn.R = ReadInt(0, 31);
	Sd.PadBtn.Pause = ReadInt(0, 31);

	Sd.MusicMasterVolume = ReadDouble(0.0, 2.0, IMAX / 2);
	Sd.SEMasterVolume    = ReadDouble(0.0, 2.0, IMAX / 2);

	Sd.PlayerMouseMoveRate = ReadDouble(-100.0, 100.0, IMAX / 100);
	Sd.WeaponRotMax = ReadInt(1, 100);

LOGPOS();
	delete FileImage;
}
void ExportSaveData(void)
{
	//Sd.ScreenZoom = GetWindowSizeExtendRate();

	FileImage = new autoQueue<uchar>(IMAX);

//	WriteLine(__DATE__);
//	WriteLine(__TIME__);
	WriteInt(CHECKDIGIT);
	WriteInt(Sd.FullScreenMode);
	WriteDouble(Sd.ScreenZoom, 100);

	WriteInt(Sd.PadBtn.Dir2);
	WriteInt(Sd.PadBtn.Dir4);
	WriteInt(Sd.PadBtn.Dir6);
	WriteInt(Sd.PadBtn.Dir8);
	WriteInt(Sd.PadBtn.A);
	WriteInt(Sd.PadBtn.B);
	WriteInt(Sd.PadBtn.C);
	WriteInt(Sd.PadBtn.D);
	WriteInt(Sd.PadBtn.E);
	WriteInt(Sd.PadBtn.F);
	WriteInt(Sd.PadBtn.L);
	WriteInt(Sd.PadBtn.R);
	WriteInt(Sd.PadBtn.Pause);

	WriteDouble(Sd.MusicMasterVolume, IMAX / 2);
	WriteDouble(Sd.SEMasterVolume,    IMAX / 2);

	WriteDouble(Sd.PlayerMouseMoveRate, IMAX / 100);
	WriteInt(Sd.WeaponRotMax);

	Jammer(FileImage->GetList(), 1);
	writeBinary(SAVEDATAFILE, FileImage->GetList());

	delete FileImage;
}
