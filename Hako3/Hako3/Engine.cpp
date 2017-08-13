#include "Stdinc.h"

int FrameCount; // 405�����炢�ŃJ���X�g
int LFrmCnt; // ���[�J���J�E���^�A�V�[�����ɏ���������B

int WindowIsActive;

int Hz;
int VSyncFlag; // ? �O���{�œ�������B
int SyncFrameBeforeSwapFlag;
int SyncWaitMillis; // 0�ł�CPU�g�p�����V��ɒ���t�����Ƃ͂Ȃ��݂����B
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
	errorCase(IMAX < FrameCount); // �܂����̃J���X�g
	LFrmCnt++;

	WindowIsActive = IsWindowActive();

	PadFrame();
	KeyFrame();

	InputMouseEachFrame();
}
