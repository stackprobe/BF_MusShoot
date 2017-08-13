#include "Stdinc.h"

typedef struct DerInfo_st
{
	int ParentPic; // as resno
	int X;
	int Y;
	int W;
	int H;
	int Handle; // HANDLE_CLOSED == 未ロード
}
DerInfo_t;

static int DerListInited;
static DerInfo_t DerList[D_MAX];
static int DerIndex;

static void AddDerInfo(int parent_pic, int x, int y, int w, int h)
{
	errorCase(D_MAX <= DerIndex);

	errorCase(parent_pic < 0 || P_MAX <= parent_pic);
	errorCase(x < 0 || IMAX < x);
	errorCase(y < 0 || IMAX < y);
	errorCase(w < 1 || IMAX < w);
	errorCase(h < 1 || IMAX < h);

	CheckPicSize(Pic(parent_pic));

	if(Pic_W < x + w || Pic_H < y + h) // ? out of range
	{
		// dummy value {
		parent_pic = P_DUMMY;
		x = 0;
		y = 0;
		w = 30;
		h = 30;
		// }
	}

	DerInfo_t *i = DerList + DerIndex;

	i->ParentPic = parent_pic;
	i->X = x;
	i->Y = y;
	i->W = w;
	i->H = h;
	i->Handle = HANDLE_CLOSED;

	DerIndex++;
}
static void AddSubAnimation(int parent_pic, int l, int t, int w, int h, int xnum, int ynum)
{
	errorCase(l < 0 || IMAX < l);
	errorCase(t < 0 || IMAX < t);
	errorCase(w < 0 || IMAX < w);
	errorCase(h < 0 || IMAX < h);
	errorCase(xnum < 1 || IMAX < xnum);
	errorCase(ynum < 1 || IMAX < ynum);

	for(int y = 0; y < ynum; y++)
	for(int x = 0; x < xnum; x++)
	{
		AddDerInfo(parent_pic, l + x * w, t + y * h, w, h);
	}
}
static void AddAnimation(int parent_pic, int w, int h, int xnum, int ynum)
{
	AddSubAnimation(parent_pic, 0, 0, w, h, xnum, ynum);
}
static void CreateDerList(void)
{
	AddDerInfo(P_DUMMY, 0, 0, 50, 50);

	AddSubAnimation(P_SYS_00, 0, 192, 16, 16, 4, 1);
	AddSubAnimation(P_SYS_00, 128, 384, 32, 32, 4, 1);
	AddSubAnimation(P_SYS_00, 0, 3264, 48, 48, 4, 1);

	AddSubAnimation(P_SYS_01, 0, 0, 8, 8, 32, 2);
	AddSubAnimation(P_SYS_01, 0, 16, 16, 16, 16, 4);

	AddSubAnimation(P_SYS_00, 0, 352, 64, 16, 2, 2); // D_MODE_*
	AddSubAnimation(P_SYS_00, 0, 5312, 64, 64, 3, 4);

	for(int kabeidx = 0; kabeidx < KABE_NUM; kabeidx++)
	{
		AddAnimation(P_KABE_00 + kabeidx, 16, 16, KABE_W, KABE_H);
	}
	AddSubAnimation(P_SYS_00, 0, 10704, 48, 48, 4, 2); // D_PLAYER_CRASH_00 + D_PLAYER_DEATH_00

	AddDerInfo(P_SYS_00, 192, 960, 64, 16);
	AddSubAnimation(
		P_ROCK_HAMMER_TAIL,
		0,
		0,
		10,
		128 / ROCK_HAMMER_TAIL_MAX,
		1,
		ROCK_HAMMER_TAIL_MAX
		);

	for(int colorIdx = 0; colorIdx < ESHOT_COLOR_MAX; colorIdx++)
	{
		AddSubAnimation(P_SYS_00, 0, 11312 + colorIdx * 40, 24, 24, ESHOT_PIC_MAX, 1);
		AddSubAnimation(P_SYS_00, 0, 11336 + colorIdx * 40, 16, 16, ESHOT_PIC_MAX, 1);
	}
	errorCase(DerIndex != D_MAX);
}
int Der(int derno)
{
	if(!DerListInited) {
		DerListInited = 1;
		CreateDerList();
	}
	errorCase(derno < 0 || D_MAX <= derno);

	DerInfo_t *i = DerList + derno;

	if(i->Handle == HANDLE_CLOSED)
	{
		i->Handle = DerivationGraph(i->X, i->Y, i->W, i->H, Pic(i->ParentPic));
		errorCase(i->Handle == HANDLE_CLOSED);
	}
	EnableTrans = S_EnableTransList()->GetElement(i->ParentPic);
	return i->Handle;
}
void ReleaseDer(int parent_pic)
{
	if(DerListInited)
	{
		for(int derno = 0; derno < D_MAX; derno++)
		{
			DerInfo_t *i = DerList + derno;

			if(i->ParentPic == parent_pic && i->Handle != HANDLE_CLOSED)
			{
				if(DeleteGraph(i->Handle) != 0) // ? エラー
				{
					error();
				}
				i->Handle = HANDLE_CLOSED;
			}
		}
	}
}
