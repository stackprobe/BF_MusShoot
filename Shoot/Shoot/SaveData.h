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
		���ۂ̉��ʂ� (�ŗL�̉���[0.0-2.0, def:0.5] * �}�X�^�[����[0.0-2.0, def:1.0]) �� 0.0-1.0 �ɋ��������l * 255 + 0.5 ���l�̌ܓ�
		SetVolume() �� m_d2i ���Ă�B
	*/
	double MusicMasterVolume; // 0.0 - 2.0 == ���� - (�ő� * 2)
	double SEMasterVolume;    // 0.0 - 2.0 == ���� - (�ő� * 2)

	double PlayerMouseMoveRate; // (-100.0) - 100.0
	int WeaponRotMax; // 1 - 100
}
Sd_t;

extern Sd_t Sd;

void ImportSaveData(void);
void ExportSaveData(void);
