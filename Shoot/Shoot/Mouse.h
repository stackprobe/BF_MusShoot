extern int MouseL;
extern int MouseR;
extern int MouseMid;
extern int MouseWheelRot;
extern int MouseX;
extern int MouseY;
extern int MouseMoveUpdateLevel;
extern int MouseMoveX;
extern int MouseMoveY;

void InputMouseEachFrame(void);
void UpdateMousePos(void);
void ApplyMousePos(void);
void UpdateMouseMove(void);
void FreezeMouseMove(void);
