#include "Stdinc.h"

int GTCommonEffect(GTCommonEffect_t *i)
{
	if(0 < i->FrmCnt && !--i->FrmCnt)
		return 0;

	if(
		i->PicResnoInc &&
		i->PicResno == i->PicResnoEnd
		)
		return 0;

	CheckPicSize(Pic(i->PicResno));

	double MARGIN_XY = 30.0 + (double)m_max(Pic_W, Pic_H) / 2.0;

	double x = i->X;
	double y = i->Y;

	if(x < -MARGIN_XY || (double)SCREEN_W + MARGIN_XY < x)
	{
		return 0;
	}
	if(y < -MARGIN_XY || (double)SCREEN_H + MARGIN_XY < y)
	{
		return 0;
	}
	if(i->Z <= 0.0)
	{
		return 0;
	}
	if(i->A <= 0.0)
	{
		return 0;
	}

	DrawBegin(x, y, Pic(i->PicResno));
	DrawZoom(i->Z);

	if(i->ReverseX)
		DrawXZoom(-1.0);

	if(i->ReverseY)
		DrawYZoom(-1.0);

	DrawRotate(i->R);

	if(i->BlendAddMode)
		SetBlendAdd(i->A);
	else
		SetAlpha(i->A);

	DrawEnd();
	ResetBlend();

	if(LFrmCnt % i->PicResnoIncPerFrame == 0)
		i->PicResno += i->PicResnoInc;

	if(i->Haneru && dRnd() < 0.02)
		i->YAdd = -0.5 * abs(i->YAdd);

	i->X += i->XAdd;
	i->Y += i->YAdd;
	i->Z += i->ZAdd;
	i->R += i->RAdd;
	i->A += i->AAdd;

	i->XAdd += i->XAdd2;
	i->YAdd += i->YAdd2;
	i->ZAdd += i->ZAdd2;
	i->RAdd += i->RAdd2;
	i->AAdd += i->AAdd2;

	if(0.0 < i->SpeedRate)
	{
		i->XAdd *= i->SpeedRate;
		i->YAdd *= i->SpeedRate;
	}
	if(0.0 < i->RotSpeedRate)
		i->RAdd *= i->RotSpeedRate;

	return 1;
}
int GTACE_BlendAddMode;
int GTACE_PicResnoIncDelay;
int GTACE_PicResnoEnd; // PicResno がこの値になったら(表示せず)即死
int GTACE_Haneru;
int GTACE_ReverseX;
int GTACE_ReverseY;
double GTACE_SpeedRate; // 0.0 == ignore
double GTACE_RotSpeedRate; // 0.0 == ignore

GTCommonEffect_t *GTAddCommonEffect_ZR(
	taskGroup_t *el,
	int pic_resno,
	int pic_resno_inc,
	int frmnum,
	double x, double y, double z, double r, double a,
	double x_add, double y_add, double z_add, double r_add, double a_add,
	double x_add2, double y_add2, double z_add2, double r_add2, double a_add2
	)
{
	GTCommonEffect_t *i = (GTCommonEffect_t *)memAlloc(sizeof(GTCommonEffect_t));

	i->PicResno = pic_resno;
	i->PicResnoInc = pic_resno_inc;
	i->PicResnoIncPerFrame = GTACE_PicResnoIncDelay + 1;
	i->PicResnoEnd = GTACE_PicResnoEnd;
	i->Haneru = GTACE_Haneru;
	i->ReverseX = GTACE_ReverseX;
	i->ReverseY = GTACE_ReverseY;
	i->SpeedRate = GTACE_SpeedRate;
	i->RotSpeedRate = GTACE_RotSpeedRate;
	i->FrmCnt = frmnum; // frmnum 回 GTCommonEffect() を実行する。0 == 無制限, 2 == 1回

	i->X = x;
	i->Y = y;
	i->Z = z;
	i->R = r;
	i->A = a;

	i->XAdd = x_add;
	i->YAdd = y_add;
	i->ZAdd = z_add;
	i->RAdd = r_add;
	i->AAdd = a_add;

	i->XAdd2 = x_add2;
	i->YAdd2 = y_add2;
	i->ZAdd2 = z_add2;
	i->RAdd2 = r_add2;
	i->AAdd2 = a_add2;

	i->BlendAddMode = GTACE_BlendAddMode;

	return AddTask(el, GTCommonEffect, i, (void (*)(GTCommonEffect_t *))memFree);
}
void GTACE_Reset(void) // 要ProcInit?
{
	GTACE_BlendAddMode = 0;
	GTACE_PicResnoIncDelay = 0;
	GTACE_PicResnoEnd = 0;
	GTACE_Haneru = 0;
	GTACE_ReverseX = 0;
	GTACE_ReverseY = 0;
	GTACE_SpeedRate = 0.0;
	GTACE_RotSpeedRate = 0.0;
}
