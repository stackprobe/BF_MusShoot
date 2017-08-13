typedef struct Sd_st
{
	int FullScreenMode;
	double ScreenZoom; // 0.1 - 10.0

	struct
	{
		int Dir2;
		int Dir4;
		int Dir6;
		int Dir8;
		int A;
		int B;
		int C;
		int D;
		int E;
		int F;
		int L;
		int R;
		int Pause;
	}
	PadBtn;

	/*
		実際の音量は (固有の音量[0.0-2.0, def:0.5] * マスター音量[0.0-2.0, def:1.0]) を 0.0-1.0 に矯正した値 * 255 + 0.5 を四捨五入
		SetVolume() で m_d2i してる。
	*/
	double MusicMasterVolume; // 0.0 - 2.0 == 無音 - (最大 * 2)
	double SEMasterVolume;    // 0.0 - 2.0 == 無音 - (最大 * 2)

	double PlayerMouseMoveRate; // (-100.0) - 100.0
	int WeaponRotMax; // 1 - 100
}
Sd_t;

extern Sd_t Sd;

void ImportSaveData(void);
void ExportSaveData(void);
