#include "Stdinc.h"

int GTPrimaryPadno;
int GTI_ResumeFrame; // FrameCount < ResumeFrame である間、GTGetInput() == 0 になる。(マウスも)

int GTGetInput(int input, int mode)
{
	if(FrameCount < GTI_ResumeFrame)
	{
		return 0;
	}
	int (*k)(int);
	int (*p)(int, int);
	int retval;

	switch(mode)
	{
	case INP_PRESS:
		k = GetKeyPress;
		p = GetPadPress_bb;
		break;

	case INP_DOWN:
		k = GetKeyDown;
		p = GetPadDown_bb;
		break;

	case INP_PRESSCOUNT:
		k = GetKeyPressCount;
		p = GetPadPressCount;
		break;

	case INP_HIT:
		k = GetKeyHit;
		p = GetPadHit;
		break;

	default:
		error();
	}
	switch(input)
	{
		/*
			PressCount があるので || ではなく | で連結すること。
		*/

	case INP_DIR_2:
		retval = k(KEY_INPUT_DOWN) | p(GTPrimaryPadno, Sd.PadBtn.Dir2);
		break;

	case INP_DIR_4:
		retval = k(KEY_INPUT_LEFT) | p(GTPrimaryPadno, Sd.PadBtn.Dir4);
		break;

	case INP_DIR_6:
		retval = k(KEY_INPUT_RIGHT) | p(GTPrimaryPadno, Sd.PadBtn.Dir6);
		break;

	case INP_DIR_8:
		retval = k(KEY_INPUT_UP) | p(GTPrimaryPadno, Sd.PadBtn.Dir8);
		break;

	case INP_A:
		retval = k(KEY_INPUT_Z) | k(KEY_INPUT_RETURN) | p(GTPrimaryPadno, Sd.PadBtn.A); // 決定
		break;

	case INP_B:
		retval = k(KEY_INPUT_X) | k(KEY_INPUT_BACK) | p(GTPrimaryPadno, Sd.PadBtn.B); // キャンセル
		break;

	case INP_C:
		retval = k(KEY_INPUT_C) | p(GTPrimaryPadno, Sd.PadBtn.C);
		break;

	case INP_D:
		retval = k(KEY_INPUT_V) | p(GTPrimaryPadno, Sd.PadBtn.D);
		break;

	case INP_E:
		retval = k(KEY_INPUT_A) | p(GTPrimaryPadno, Sd.PadBtn.E);
		break;

	case INP_F:
		retval = k(KEY_INPUT_S) | p(GTPrimaryPadno, Sd.PadBtn.F);
		break;

	case INP_L:
		retval = k(KEY_INPUT_D) | p(GTPrimaryPadno, Sd.PadBtn.L);
		break;

	case INP_R:
		retval = k(KEY_INPUT_F) | p(GTPrimaryPadno, Sd.PadBtn.R);
		break;

	case INP_PAUSE:
		retval = k(KEY_INPUT_SPACE) | p(GTPrimaryPadno, Sd.PadBtn.Pause);
		break;

	default:
		error();
	}
	return retval;
}
void GTFreezeInput(void)
{
	GTI_ResumeFrame = FrameCount + 1;

	MouseL = 0;
	MouseR = 0;
	MouseMid = 0;
	MouseWheelRot = 0;

	FreezeMouseMove();
}
