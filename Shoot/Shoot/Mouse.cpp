#include "Stdinc.h"

int MouseL;
int MouseR;
int MouseMid;
int MouseWheelRot;
int MouseX;
int MouseY;
int MouseMoveUpdateLevel; // 0: 不使用, 1: 前フレームで使用した, 2: 現フレームで使用した
int MouseMoveX;
int MouseMoveY;

static int ResumeFrame;

static int MouseScreenCenterX = SCREEN_CENTER_X;
static int MouseScreenCenterY = SCREEN_CENTER_Y;

void InputMouseEachFrame(void)
{
	int freezeNow = WindowIsActive == 0 || FrameCount < GTI_ResumeFrame;

	int status = freezeNow ? 0 : GetMouseInput(); // ? freezeNow -> 入力を無効にする。

	UPDATEINPUT(status & MOUSE_INPUT_LEFT, MouseL)
	UPDATEINPUT(status & MOUSE_INPUT_RIGHT, MouseR)
	UPDATEINPUT(status & MOUSE_INPUT_MIDDLE, MouseMid)

	MouseWheelRot = freezeNow ? 0 : GetMouseWheelRotVol(); // ? freezeNow -> 入力を無効にする。
	m_range(MouseWheelRot, -IMAX, IMAX); // 2bs

	m_countDown(MouseMoveUpdateLevel);
}
void UpdateMousePos(void)
{
	if(GetMousePoint(&MouseX, &MouseY) != 0) // ? 失敗
	{
		error();
	}
}
void ApplyMousePos(void)
{
	if(SetMousePoint(MouseX, MouseY) != 0) // ? 失敗
	{
		error();
	}
}
void UpdateMouseMove(void)
{
	if(MouseMoveUpdateLevel == 2) // ? 現フレームで2回目
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
