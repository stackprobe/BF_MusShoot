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
//	remove(LOG_DIR "\\Log.txt"); // 3.08c からOK
	SetApplicationLogSaveDirectory(LOG_DIR);
#endif
	SetOutApplicationLogValidFlag(APPLOG_ENABLED); 
	SetAlwaysRunFlag(true); // フォーカス外したら、true: 動く, false: 止まる。

	/*
		fixme:
		このソースをコンパイルしないと日付が変わらない。
		リリース前は必ずリビルドしてね!!
	*/
	SetMainWindowText(
#if \
	APPLOG_ENABLED || \
	LOG_ENABLED || \
	SW_ENABLED
		"(DEBUG) "
#endif
		"BF_MusShoot - blt: " __DATE__ " " __TIME__
		);

	SetGraphMode(SCREEN_W, SCREEN_H, 32);
	ChangeWindowMode(Sd.FullScreenMode ? 0 : 1); // 0: 全画面, 1: 窓

	if(DxLib_Init())
	{
		return 1;
	}
	DxLibInited = 1;

	SetMouseDispFlag(1); // 0: マウス消し, 1: マウス表示
	SetVSyncFlag(1);

	/*
		ウィンドウの右下をドラッグで、ウィンドウ伸縮 true: 可, false: 不可
		可にすると SetWindowSizeExtendRate() の最大サイズに影響する。
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
		ウィンドウが非アクティブな時にスクリーンモードを変更するとフリーズする。
		これを呼び出す前に IsWindowActive() でアクティブであることを確認してね。
		とりあえず IsWindowActive() == 0 の時はキー・パッド入力を抑止して、
		非アクティブ時にこれを呼び出す状況を作らないようにする。
		シビアなタイミングでアクティブ状態が変化したら駄目だろうけど、そこまで考えなくていいや...。
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
