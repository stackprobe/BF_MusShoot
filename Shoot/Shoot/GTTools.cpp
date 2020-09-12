#include "Stdinc.h"

void GTWaitFadeout(int resno_wallpic, double whiteLevel, int frmcnt)
{
	GTSetCurtain(whiteLevel, frmcnt);

	while(GTActWhiteLevel != whiteLevel)
	{
		SimpleDrawPic(0, 0, Pic(resno_wallpic));
		GTEndFrame();
	}
}

void GTDrawBox(int x, int y, int w, int h, int color)
{
	I2RGB(color);

	SetAlpha(Color_A / 255.0);
	SetBright(
		Color_R / 255.0,
		Color_G / 255.0,
		Color_B / 255.0
		);

	DrawPicRect(x, y, w, h, Pic(P_WHITEBOX));

	ResetBlend();
	ResetBright();
}
void GTDrawCircle(double x, double y, double r, int color)
{
	I2RGB(color);

	SetAlpha(Color_A / 255.0);
	SetBright(
		Color_R / 255.0,
		Color_G / 255.0,
		Color_B / 255.0
		);

	DrawBegin(x, y, Pic(P_WHITECIRCLE));
	DrawZoom(r / 50.0); // P_WHITECIRCLE の幅と高さは 100 
	DrawEnd();

	ResetBlend();
	ResetBright();
}

void GTSetFullScreenMode(int mode)
{
	if(Sd.FullScreenMode ? mode : !mode) // ? 変更ナシ
		return;

	NEL_forscene(60)
	{
		if(WindowIsActive == 0) // ? アクティブじゃなくなったら即行キャンセル
			return;

		SetBright(0, 0, 0);
		DrawPicRect(0, 0, SCREEN_W, SCREEN_H, Pic(P_WHITEBOX));
		ResetBright();

		GTEndFrame();
	}
	Sd.FullScreenMode = mode ? 1 : 0;
	ApplyScreenMode();

	NEL_forscene(60)
	{
		SetBright(0, 0, 0);
		DrawPicRect(0, 0, SCREEN_W, SCREEN_H, Pic(P_WHITEBOX));
		ResetBright();

		GTEndFrame();
	}
}

DPOE_t *CreateDPOE(void)
{
	DPOE_t *i = nb_(DPOE_t);

	i->PicResno = P_DUMMY; // 2bs
	i->A = 1.0;
	i->Type = DPOE_MAX; // 2bs
	i->u.Center.Z = 1.0;

	return i;
}
void AddDPOE(taskGroup_t *el, DPOE_t *i)
{
	AddTask(el, DrawPicOnEffect, i, (void (*)(DPOE_t *))memFree);
}
int DrawPicOnEffect(DPOE_t *i)
{
	errorCase(i == NULL);

	if(i->BlendAddMode)
		SetBlendAdd(i->A);
	else
		SetAlpha(i->A);
	
	switch(i->Type)
	{
	case DPOE_FREE:
		{
			DrawPicFree(
				i->u.Free.LTX, i->u.Free.LTY,
				i->u.Free.RTX, i->u.Free.RTY,
				i->u.Free.RBX, i->u.Free.RBY,
				i->u.Free.LBX, i->u.Free.LBY,
				Pic(i->PicResno)
				);
		}
		break;

	case DPOE_CENTER:
		{
			DrawBegin(i->u.Center.X, i->u.Center.Y, Pic(i->PicResno));
			DrawRotate(i->u.Center.R);
			DrawZoom(i->u.Center.Z);
			DrawEnd();
		}
		break;

	default:
		error();
	}
	ResetBlend();

	if(i->FadeOutMode)
	{
		i->A -= i->FadeOut_A;
		return 0.0 < i->A;
	}
	return 0;
}

// Print ...

/*
	MINI:
		$ (0x24) = 残機
*/
static const int CharIdxTable[0x80] =
{
	63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, // 0x00 - 0x0f
	63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, // 0x10 - 0x1f
	62, 62, 62, 62, 57, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, // 0x20 - 0x2f
	 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 61, 61, 61, 61, 61, 61, // 0x30 - 0x3f
	61, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, // 0x40 - 0x4f
	25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 60, 60, 60, 60, 60, // 0x50 - 0x5f
	60, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, // 0x60 - 0x6f
	25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 55, 55, 55, 55, 55, // 0x70 - 0x7f
};

static int P_X;
static int P_Y;
static int P_CurrX;
static int P_CurrY;
static int P_XStep;
static int P_YStep;
static int P_MiniFlag;

void GTPrintSet(int x, int y, int miniFlag, int xStep, int yStep)
{
	P_X = x;
	P_Y = y;
	P_CurrX = x;
	P_CurrY = y;
	P_XStep = xStep;
	P_YStep = yStep;
	P_MiniFlag = miniFlag;
}
void GTPrintSet(int x, int y, int miniFlag)
{
	GTPrintSet(x, y, miniFlag,
		miniFlag ? 8 : 16,
		miniFlag ? 8 : 16
		);
}
void GTPrint(char *line)
{
	for(char *p = line; *p; p++)
	{
		if(*p == '\n')
		{
			P_CurrX = P_X;
			P_CurrY += P_YStep;
		}
		else
		{
			if(*p != ' ')
			{
				SimpleDrawPic(P_CurrX, P_CurrY, Der(
					(P_MiniFlag ?
						D_ASCII_MINI_00 :
						D_ASCII_00
						) + CharIdxTable[*p & 0x7f]
					));
			}
			P_CurrX += P_XStep;
		}
	}
}
void GTPrint_x(char *line)
{
	GTPrint(line);
	memFree(line);
}
