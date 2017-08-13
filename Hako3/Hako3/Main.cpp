#include "Stdinc.h"

int DxLibInited;

int ReqTestPlay;
int ReqTestPlayStartPos;

void termination(int errorLevel)
{
	if(DxLibInited)
	{
		DxLib_End();
	}
	exit(errorLevel);
}
void EndProc(void)
{
	// PROC_FNLZ
	{
		ExportSaveData();
		ReleaseResources();
	}
	termination(0);
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	char **args = __argv + 1;

	if(*args && !strcmp(*args, "/TSP")) // Test-play Start Pos
	{
		ReqTestPlay = 1;

		if(*++args)
			ReqTestPlayStartPos = atoi(*args++);
	}

	memAlloc_INIT();
	initRnd((int)time(NULL));
	ImportSaveData();

	// Core >

#if APPLOG_ENABLED
//	remove(LOG_DIR "\\Log.txt"); // 3.08c ����OK
	SetApplicationLogSaveDirectory(LOG_DIR);
#endif
	SetOutApplicationLogValidFlag(APPLOG_ENABLED);
	SetAlwaysRunFlag(true); // �t�H�[�J�X�O������Atrue: ����, false: �~�܂�B

	/*
		fixme:
		���̃\�[�X���R���p�C�����Ȃ��Ɠ��t���ς��Ȃ��B
		�����[�X�O�͕K�����r���h���Ă�!!
	*/
	SetMainWindowText(
#if \
	APPLOG_ENABLED || \
	LOG_ENABLED || \
	SW_ENABLED
		"(DEBUG) "
#endif
		"HakoIII - blt: " __DATE__ " " __TIME__
		);

	SetGraphMode(SCREEN_W, SCREEN_H, 32);
	ChangeWindowMode(Sd.FullScreenMode ? 0 : 1); // 0: �S���, 1: ��

	if(DxLib_Init())
	{
		return 1;
	}
	DxLibInited = 1;

	SetMouseDispFlag(1); // 0: �}�E�X����, 1: �}�E�X�\��
	SetVSyncFlag(1);

	/*
		�E�B���h�E�̉E�����h���b�O�ŁA�E�B���h�E�L�k true: ��, false: �s��
		�ɂ���� SetWindowSizeExtendRate() �̍ő�T�C�Y�ɉe������B
	*/
	SetWindowSizeChangeEnableFlag(false);

	// < Core

	LOGPOS();

	// PROC_INIT
	{
		GTACE_Reset();
		GmResetDataCenter();
		GmResetResultCenter();
	}
	LOGPOS();
	ApHome();
	LOGPOS();

	EndProc();
}

static int LastSetMouseDispMode;

void SetDispMouseCursorMode(int mouseDispMode)
{
	SetMouseDispFlag(mouseDispMode ? 1 : 0);
	LastSetMouseDispMode = mouseDispMode;
}
void ApplyWindowSize(void)
{
	SetWindowSizeExtendRate(Sd.ScreenZoom);
	SetDispMouseCursorMode(LastSetMouseDispMode);
}
void ApplyScreenMode(void)
{
	int mdm = GetMouseDispFlag();

	ReleasePictures();

	/*
		�E�B���h�E����A�N�e�B�u�Ȏ��ɃX�N���[�����[�h��ύX����ƃt���[�Y����B
		������Ăяo���O�� IsWindowActive() �ŃA�N�e�B�u�ł��邱�Ƃ��m�F���ĂˁB
		�Ƃ肠���� IsWindowActive() == 0 �̎��̓L�[�E�p�b�h���͂�}�~���āA
		��A�N�e�B�u���ɂ�����Ăяo���󋵂����Ȃ��悤�ɂ���B
		�V�r�A�ȃ^�C�~���O�ŃA�N�e�B�u��Ԃ��ω�������ʖڂ��낤���ǁA�����܂ōl���Ȃ��Ă�����...�B
	*/
	ChangeWindowMode(Sd.FullScreenMode ? 0 : 1);

	SetDispMouseCursorMode(LastSetMouseDispMode);
	SetVSyncFlag(1);
}
void ReleaseResources(void)
{
	ReleasePictures();
	ReleaseMusics();
	ReleaseSoundEffects();
	ReleasePads();
}
void TouchResources(void)
{
	for(int r = 0; r < P_MAX; r++)
	{
		Pic(r);
		/*
		SetPictureGroup(S_EnemyLv1PictureGroup());
		Pic(r);
		SetPictureGroup(S_EnemyLv2PictureGroup());
		Pic(r);
		SetPictureGroup(S_EnemyLv3PictureGroup());
		Pic(r);
		SetPictureGroup(NULL);
		*/
	}
	for(int r = 0; r < D_MAX; r++)
	{
		Der(r);
	}
	for(int r = 0; r < SE_MAX; r++)
	{
		SETouch(r);
	}
}
