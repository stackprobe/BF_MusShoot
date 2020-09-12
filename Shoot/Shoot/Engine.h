extern int FrameCount;
extern int LFrmCnt;

extern int WindowIsActive;

extern int Hz;
extern int VSyncFlag;
extern int SyncWaitMillis;
extern int SyncNextTimeMillis;
extern int FRDLevel;

void SetVSyncFlag(int flag);
void EndFrame(void);
