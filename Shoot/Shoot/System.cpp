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
	printfDx("致命的なエラーが発生しました。\n");
//	printfDx("下記(及び上記)メッセージと併せてご連絡いただけると幸いです。\n");
//	printfDx("エスケープキーを押して、このアプリケーションを終了して下さい。\n");
	printfDx("----\n");
	printfDx("場所: %s (%d) %s\n", source, lineno, function);

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

int IsWindowActive(void) // ret: ? ウィンドウがアクティブ状態
{
	return GetActiveFlag() ? 1 : 0;
}
