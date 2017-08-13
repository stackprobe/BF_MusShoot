enum
{
	P_DUMMY,
	P_WHITEBOX,
	P_WHITECIRCLE,

	P_WILL_500,
	P_WILL_501,
	P_WILL_502,
	P_WILL_503,
	P_WILL_504,
	P_WILL_505,
	P_WILL_506,
	P_WILL_507,

	P_WILL_800,
	P_WILL_801,

	P_WILL_200,
	P_WILL_201,

	P_WILL_600,
	P_WILL_601,
	P_WILL_602,
	P_WILL_603,
	P_WILL_604,
	P_WILL_605,
	P_WILL_606,
	P_WILL_607,

	P_WILL_400,
	P_WILL_401,
	P_WILL_402,
	P_WILL_403,
	P_WILL_404,
	P_WILL_405,
	P_WILL_406,
	P_WILL_407,

	P_WILL_BLUE_500,
	P_WILL_BLUE_501,
	P_WILL_BLUE_502,
	P_WILL_BLUE_503,
	P_WILL_BLUE_504,
	P_WILL_BLUE_505,
	P_WILL_BLUE_506,
	P_WILL_BLUE_507,

	P_WILL_BLUE_800,
	P_WILL_BLUE_801,

	P_WILL_BLUE_200,
	P_WILL_BLUE_201,

	P_WILL_BLUE_600,
	P_WILL_BLUE_601,
	P_WILL_BLUE_602,
	P_WILL_BLUE_603,
	P_WILL_BLUE_604,
	P_WILL_BLUE_605,
	P_WILL_BLUE_606,
	P_WILL_BLUE_607,

	P_WILL_BLUE_400,
	P_WILL_BLUE_401,
	P_WILL_BLUE_402,
	P_WILL_BLUE_403,
	P_WILL_BLUE_404,
	P_WILL_BLUE_405,
	P_WILL_BLUE_406,
	P_WILL_BLUE_407,

	P_WILL_BARRIER_00,
	P_WILL_BARRIER_01,
	P_WILL_BARRIER_02,
	P_WILL_BARRIER_03,
	P_WILL_BARRIER_04,
	P_WILL_BARRIER_05,

	P_SPACE_WALL,

	P_SYS_00,
	P_SYS_01,

	P_GAUGE_FRAME,
	P_GAUGE_BAR,

	P_TAMA_MIRACLE,
	P_TAMA_MIRACLE_MINI,

	ENUM_RANGE(P_KABE_00, KABE_NUM)

	ENUM_RANGE(P_NEWSHOT_00, 13)
	ENUM_RANGE(P_NEWMIRACLE_FIRE_00, 11)
	P_NEWMIRACLE,
	P_NEWMIRACLE_JIN,
	ENUM_RANGE(P_NEWSHOT_DEATH_00, 8)
	ENUM_RANGE(P_NEWMIRACLE_SPARK_00, 8)
	
	P_YELLOW_STAR,
	P_TAME_JIN,
	P_TAME_JIN_STAR,

	ENUM_RANGE(P_NEWMIRACLE_HASSHA_00, 9)
	ENUM_RANGE(P_WEAPON_00, WEAPON_MAX)
	P_LASER_SHOT,
	P_LASER_CUTTER,

	ENUM_RANGE(P_FEI_00, 4)

	P_ROCK,
	ENUM_RANGE(P_BOMB_00, 8)
	P_ROCK_HAMMER_HIMO,
	P_ROCK_HAMMER_TAIL, // ñv?
	P_ROCK_HAMMER_JIN_OLD, // ñv?
	P_ROCK_HAMMER_JIN,
	P_ROCK_HAMMER_TAILBALL,
	P_ROCK_STAR,

	P_DIRECTION,

	P_SLOW_SHOT,
	P_SLOW_BARRIER,
	P_BLADE_SHOT,
	P_BLADE,
	P_BLADE_SHADOW,
	P_SPREAD,
	ENUM_RANGE(P_BOUNCE, 12)

	ENUM_RANGE(P_ENEMY_DEATH_00, 10)

	ENUM_RANGE(P_ESHOT_00_R_00, ESHOT_PIC_MAX)
	ENUM_RANGE(P_ESHOT_00_S_00, ESHOT_PIC_MAX)
	ENUM_RANGE(P_ESHOT_01_R_00, ESHOT_PIC_MAX)
	ENUM_RANGE(P_ESHOT_01_S_00, ESHOT_PIC_MAX)
	ENUM_RANGE(P_ESHOT_02_R_00, ESHOT_PIC_MAX)
	ENUM_RANGE(P_ESHOT_02_S_00, ESHOT_PIC_MAX)
	ENUM_RANGE(P_ESHOT_03_R_00, ESHOT_PIC_MAX)
	ENUM_RANGE(P_ESHOT_03_S_00, ESHOT_PIC_MAX)
	ENUM_RANGE(P_ESHOT_04_R_00, ESHOT_PIC_MAX)
	ENUM_RANGE(P_ESHOT_04_S_00, ESHOT_PIC_MAX) // P_ESHOT_(ESHOT_COLOR_MAX - 1)_S_00

	ENUM_RANGE(P_HIKARU_00, 4)
	ENUM_RANGE(P_LINA_00, 4)
	ENUM_RANGE(P_LINA_USHIRO_00, 4)
	ENUM_RANGE(P_LINA_SAKASA_00, 4)
	ENUM_RANGE(P_NINGYO_JUMP_00, 8)
	ENUM_RANGE(P_NINGYO_00, 4)
	ENUM_RANGE(P_NINGYO_ATTACK_00, 4)
	ENUM_RANGE(P_NINGYO_DEAD_00, 6)

	P_MAX, // num of member
};

void EnterRGBA(void);
void LeaveRGBA(void);

void SILoadPixel(int h, int x, int y);
void SISavePixel(int h, int x, int y);

extern int PL_Resno;

int PL_ImageIsBmp(autoList<uchar> *image);
int Pic_Load(int resno, autoList<uchar> *image);
void Pic_Unload(int resno, int h);
Resource_t *Pic_Res(void);

void ReleasePictures(void);

singleton_proto_VT(SoftImageFilterList, autoList<void (*)(int, int, int)>)
singleton_proto_VT(GraphicHandleFilterList, autoList<void (*)(int)>)
singleton_proto_VT(EnableTransList, autoList<int>)

extern int EnableTrans;

/*
	Pic(D_* | DTP) Ç±ÇÒÇ»ä¥Ç∂Ç≈égÇ§ÅB
*/
#define DTP 0x40000000 // D_* To P_*

int Pic(int resno);

void SetAlpha(double a);
void SetBlendAdd(double a);
void SetBlendInv(double a = 1.0);
void ResetBlend(void);
void SetBright(double r, double g, double b);
void ResetBright(void);

extern int Pic_W;
extern int Pic_H;

void CheckPicSize(int h);

extern int ScreenSlip_X;
extern int ScreenSlip_Y;

void SimpleDrawPic(int x, int y, int h);
void SimpleDrawPic(double x, double y, int h);
void SimpleDrawPicFloat(double x, double y, int h);
void DrawPic(int x, int y, int h);
void DrawPic(double x, double y, int h);
void DrawPicRect(int x, int y, int w, int h, int hdl);
void DrawPicFree(
	double ltx, double lty,
	double rtx, double rty,
	double rbx, double rby,
	double lbx, double lby,
	int hdl
	);

void DrawBegin(double x, double y, int h);
void DrawMove(double x, double y);
void DrawRotate(double rot);
void DrawRotate(int numer, int denom);
void DrawXZoom(double zoom);
void DrawYZoom(double zoom);
void DrawZoom(double zoom);
void DrawEnd(void);
