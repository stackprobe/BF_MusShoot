#define TAME_MAX 1000
#define TAME_LV_MAX 4

#define TAME_LV1 90
#define TAME_LV2 390
#define TAME_LV3 690

#define PLAYER_HP_DEF 10
#define PLAYER_CRASH_MAX 200
#define PLAYER_TOUJOU_MAX 90

typedef struct GmDataCenter_st // GmHome() 終了時に初期化する。(引数と広域)
{
	// 引数 >

	int MapIndex;
	int MapStartPos;

	// < 引数

	/*
		何も無いところは NULL であることに注意
	*/
	autoList<MapCellData_t *> *BackMapData;
	autoList<MapCellData_t *> *FrontMapData;
	autoList<Enemy_t *> *BackMapEnemyData;
	autoList<Enemy_t *> *FrontMapEnemyData;

	double NextMapX;
	int ReadMapIndex;
	int ReadMapXPos;

	struct
	{
		double X;
		double Y;
		double LastMoveX;
		double LastMoveY;
		double MASpeedX;
		double MASpeedY;
		int LastDirX; // (-1) - 1
		int LastDirY; // (-1) - 1
		double TraceR;

		int Tame; // 0 - TAME_MAX
		int TameLv; // 0 - TAME_LV_MAX
		double TameMaxFlash;
		double TameSemiFlash;

		int CantDir; // 2468+5
		int XCant;
		int YCant;

		int HP;
		int CrashFrame; // 0 - PLAYER_CRASH_MAX (無敵期間の判定に使う)
		double CrashedX;
		double CrashedY;
		double ToujouFrame; // 0 - PLAYER_TOUJOU_MAX
		double T_X;
		double T_Y;

		int LastWeaponRotDir; // 今フレームで変更されたら -1 or 1, それ以外は 0
		int LastWeapon;
		int CurrWeapon; // 0 - (WEAPON_MAX - 1)
		int WeaponRot;
		int WeaponFrame;
	}
	Player;

	// ステージ固有の設定 {
	double ScrollSpeed;
	// }

	double Scroll;
	__int64 Score;
	int ExtraMode;

	int WallBaseOk;
	int WallBaseX;

	double Death_A;

	int DoDrawPlayerDir;
	double D_PlayerDir;

	PShot_t *CurrRockHammer;
	PShot_t *CurrSlowBarrier;
	PShot_t *CurrBlade;

	autoList<PShot_t *> *PShotList;
	autoList<Enemy_t *> *EnemyList;

	taskGroup_t *EffectList_BS; // Back of pShot
	taskGroup_t *EffectList_BW; // Back of Wall(Enemy)
	taskGroup_t *EffectList_BP; // Back of Player
	taskGroup_t *EffectList_BE; // Back of Enemy
	taskGroup_t *EffectList;
}
GmDataCenter_t;

typedef struct GmResultCenter_st // GmHome() 開始時に初期化する。(戻り値)
{
	int Dummy;
}
GmResultCenter_t;

extern GmDataCenter_t GmDc;
extern GmResultCenter_t GmRc;

void GmResetDataCenter(void);
void GmResetResultCenter(void);

void GmHome(void);
