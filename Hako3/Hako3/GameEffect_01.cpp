#include "Stdinc.h"

void DrawSlowBarrier(PShot_t *ps, int ba_mode, double a)
{
	if(!ba_mode)
	{
		SetPictureGroup(S_HSTEffectPicGrp());
		SetAlpha(a);
	}
	else
		SetBlendAdd(a);

	DrawBegin(ps->X, ps->Y, Pic(P_SLOW_BARRIER));
	DrawMove(-5.0, 0.0);
	DrawZoom(ps->u.Slow.R / 100.0); // ’¼Œa 207, 208 ‚­‚ç‚¢
	DrawRotate(ps->u.Slow.Rot);
	DrawEnd();

	if(!ba_mode)
		SetPictureGroup(NULL);

	ResetBlend();
}
void DrawSlowBarrier_Main(PShot_t *ps)
{
	DrawSlowBarrier(ps, 0, 0.5);
}
int DrawSlowBarrier_Cover(PShot_t *ps)
{
	DrawSlowBarrier(ps, 1, 0.2);
	return 0;
}
