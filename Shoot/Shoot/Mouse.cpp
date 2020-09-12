#include "Stdinc.h"

int MouseL;
int MouseR;
int MouseMid;
int MouseWheelRot;
int MouseX;
int MouseY;
int MouseMoveUpdateLevel; // 0: �s�g�p, 1: �O�t���[���Ŏg�p����, 2: ���t���[���Ŏg�p����
int MouseMoveX;
int MouseMoveY;

static int ResumeFrame;

static int MouseScreenCenterX = SCREEN_CENTER_X;
static int MouseScreenCenterY = SCREEN_CENTER_Y;

void InputMouseEachFrame(void)
{
	int freezeNow = WindowIsActive == 0 || FrameCount < GTI_ResumeFrame;

	int status = freezeNow ? 0 : GetMouseInput(); // ? freezeNow -> ���͂𖳌��ɂ���B

	UPDATEINPUT(status & MOUSE_INPUT_LEFT, MouseL)
	UPDATEINPUT(status & MOUSE_INPUT_RIGHT, MouseR)
	UPDATEINPUT(status & MOUSE_INPUT_MIDDLE, MouseMid)

	MouseWheelRot = freezeNow ? 0 : GetMouseWheelRotVol(); // ? freezeNow -> ���͂𖳌��ɂ���B
	m_range(MouseWheelRot, -IMAX, IMAX); // 2bs

	m_countDown(MouseMoveUpdateLevel);
}
void UpdateMousePos(void)
{
	if(GetMousePoint(&MouseX, &MouseY) != 0) // ? ���s
	{
		error();
	}
}
void ApplyMousePos(void)
{
	if(SetMousePoint(MouseX, MouseY) != 0) // ? ���s
	{
		error();
	}
}
void UpdateMouseMove(void)
{
	if(MouseMoveUpdateLevel == 2) // ? ���t���[����2���
		return;

	UpdateMousePos();

	MouseMoveX = MouseX - MouseScreenCenterX;
	MouseMoveY = MouseY - MouseScreenCenterY;

	MouseX = MouseScreenCenterX;
	MouseY = MouseScreenCenterY;

	ApplyMousePos();
#if 0
	UpdateMousePos();

#if LOG_ENABLED
	if(
		MouseScreenCenterX != MouseX ||
		MouseScreenCenterY != MouseY
		)
	{
		LOG("[MUSCTR-ERR] %d %d -> %d %d\n", MouseScreenCenterX, MouseScreenCenterY, MouseX, MouseY);
	}
#endif

	MouseScreenCenterX = MouseX;
	MouseScreenCenterY = MouseY;
#endif

	if(!MouseMoveUpdateLevel)
	{
		MouseMoveX = 0;
		MouseMoveY = 0;
	}
	MouseMoveUpdateLevel = 2;

	// add =>

	if(FrameCount < ResumeFrame)
	{
		MouseMoveX = 0;
		MouseMoveY = 0;
	}
}
void FreezeMouseMove(void)
{
	ResumeFrame = FrameCount + 3;
}
