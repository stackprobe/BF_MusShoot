#include "Stdinc.h"

int FrameCount; // 405日くらいでカンスト
int LFrmCnt; // ローカルカウンタ、シーン毎に初期化する。

int WindowIsActive;

int Hz;
int VSyncFlag; // ? グラボで同期する。
int SyncFrameBeforeSwapFlag;
int SyncWaitMillis; // 0でもCPU使用率が天井に張り付くことはないみたい。
int SyncNextTimeMillis;
int FRDLevel;

void SetVSyncFlag(int flag)
{
	SetDrawScreen(DX_SCREEN_BACK);
	SetWaitVSyncFlag(flag ? true : false);

	VSyncFlag = flag;
}
static void SyncFrame(void)
{
	int timems = GetNowCount();

	if(SyncNextTimeMillis < timems)
	{
		SyncNextTimeMillis = timems;
	}
	else
	{
		do
		{
			Sleep(SyncWaitMillis);
		}
		while(GetNowCount() < SyncNextTimeMillis);
	}
	SyncNextTimeMillis += FrameCount % 3 == 0 ? 17 : 16;
}

static void CheckHz(void)
{
	static int lasttimems;
	int timems = GetNowCount();
	int diffms = timems - lasttimems;

	if(diffms < 15 || 18 < diffms) FRDLevel++;
	if(diffms == 16 || diffms == 17) m_countDown(FRDLevel);

	lasttimems = timems;
}

void EndFrame(void)
{
	if(!SEFrame())
	{
		MusicFrame();
	}

	// Core >

	if(VSyncFlag)
	{
		ScreenFlip();
	}
	else
	{
		if(SyncFrameBeforeSwapFlag)
			SyncFrame();

		ScreenFlip();

		if(!SyncFrameBeforeSwapFlag)
			SyncFrame();
	}
	CheckHz(); // not core

	if(CheckHitKey(KEY_INPUT_ESCAPE) == 1 || ProcessMessage() == -1)
	{
		EndProc();
	}

	// < Core

	FrameCount++;
	errorCase(IMAX < FrameCount); // まさかのカンスト
	LFrmCnt++;

	WindowIsActive = IsWindowActive();

	PadFrame();
	KeyFrame();

	InputMouseEachFrame();
}
