typedef struct GTCommonEffect_st
{
	int PicResno;
	int PicResnoInc;
	int PicResnoIncPerFrame;
	int PicResnoEnd;
	int Haneru;
	int ReverseX;
	int ReverseY;
	double SpeedRate;
	double RotSpeedRate;
	int FrmCnt;
	double X;
	double Y;
	double Z;
	double R;
	double A;
	double XAdd;
	double YAdd;
	double ZAdd;
	double RAdd;
	double AAdd;
	double XAdd2;
	double YAdd2;
	double ZAdd2;
	double RAdd2;
	double AAdd2;
	int BlendAddMode;
}
GTCommonEffect_t;

int GTCommonEffect(GTCommonEffect_t *i);

extern int GTACE_BlendAddMode;
extern int GTACE_PicResnoIncDelay;
extern int GTACE_PicResnoEnd;
extern int GTACE_Haneru;
extern int GTACE_ReverseX;
extern int GTACE_ReverseY;
extern double GTACE_SpeedRate;
extern double GTACE_RotSpeedRate;

GTCommonEffect_t *GTAddCommonEffect_ZR(
	taskGroup_t *el,
	int pic_resno,
	int pic_resno_inc,
	int frmnum,
	double x, double y,
	double z = 1.0,
	double r = 0.0,
	double a = 1.0,
	double x_add = 0.0,
	double y_add = 0.0,
	double z_add = 0.0,
	double r_add = 0.0,
	double a_add = 0.0,
	double x_add2 = 0.0,
	double y_add2 = 0.0,
	double z_add2 = 0.0,
	double r_add2 = 0.0,
	double a_add2 = 0.0
	);
void GTACE_Reset(void);
