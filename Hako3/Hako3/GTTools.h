void GTWaitFadeout(int resno_wallpic, double whiteLevel, int frmcnt);

void GTDrawBox(int x, int y, int w, int h, int color);
void GTDrawCircle(double x, double y, double r, int color);

void GTSetFullScreenMode(int mode);

typedef enum DPOEType_et
{
	DPOE_FREE,
	DPOE_CENTER,
	DPOE_MAX, // num of member
}
DPOEType_t;

typedef struct DPOE_st
{
	int PicResno;
	int BlendAddMode;
	double A;
	DPOEType_t Type;

	union
	{
		struct
		{
			double LTX;
			double LTY;
			double RTX;
			double RTY;
			double RBX;
			double RBY;
			double LBX;
			double LBY;
		}
		Free;

		struct
		{
			double X;
			double Y;
			double R;
			double Z;
		}
		Center;
	}
	u;

	int FadeOutMode;
	double FadeOut_A;
}
DPOE_t;
DPOE_t *CreateDPOE(void);

void AddDPOE(taskGroup_t *el, DPOE_t *i);
int DrawPicOnEffect(DPOE_t *i);

// Print ...

void GTPrintSet(int x, int y, int miniFlag, int xStep, int yStep);
void GTPrintSet(int x, int y, int miniFlag);
void GTPrint(char *line);
void GTPrint_x(char *line);
