#include "Stdinc.h"

FILE *GetLogFp(void)
{
	static FILE *fp;

	if(!fp)
		fp = fileOpen(LOG_FILE, "wt");

	return fp;
}

void error2(char *source, int lineno, char *function)
{
	static int callcnt;

	if(callcnt)
	{
		exit(2);
	}
	callcnt++;

	if(!DxLibInited)
	{
		LOG("[ERROR] %s (%d) %s", source, lineno, function);
		exit(3);
	}
	DrawBox(0, 0, SCREEN_W, SCREEN_H, GetColor(0, 0, 64), 1);

	printfDx("----\n");
	printfDx("�v���I�ȃG���[���������܂����B\n");
//	printfDx("���L(�y�я�L)���b�Z�[�W�ƕ����Ă��A������������ƍK���ł��B\n");
//	printfDx("�G�X�P�[�v�L�[�������āA���̃A�v���P�[�V�������I�����ĉ������B\n");
	printfDx("----\n");
	printfDx("�ꏊ: %s (%d) %s\n", source, lineno, function);

	ScreenFlip();

	while(CheckHitKey(KEY_INPUT_ESCAPE) == 0 && ProcessMessage() != -1)
	{
		ScreenFlip();
	}
	termination(1);
}

int fs_count;
int fs_max;
double fs_rate;

int IsWindowActive(void) // ret: ? �E�B���h�E���A�N�e�B�u���
{
	return GetActiveFlag() ? 1 : 0;
}
