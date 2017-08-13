typedef struct EnemyCommonData_st
{
	double HaichiX;
	int StartHP; // 0 == ���G (-1 == �f�t�H���g���g�p <- "*" �̏ꍇ)
}
EnemyCommonData_t;

EnemyCommonData_t *CreateEnemyCommonData(void);
EnemyCommonData_t *CreateEnemyCommonData(
	double haichiX,
	int start_hp
	);
EnemyCommonData_t *CreateEnemyCommonData(autoList<char *> *lines);
void ReleaseEnemyCommonData(EnemyCommonData_t *);

// <== ECD

typedef struct Enemy_st
{
	int (*ProcFunc)(struct Enemy_st *, void *);
	void (*DrawFunc)(struct Enemy_st *, void *); // �~�X���ȂǂP�t���[���ŕ�����Ăяo���ꍇ�����邱�Ƃɗv����!!
	void (*ReleaseFunc)(void *);
	int HP; // 0 == ���G
	EnemyCommonData_t *CommonData;
	void *ExtraData;
	int Frame;
	double X;
	double Y;
	int MapXPos;
	int MapYPos;

	struct
	{
		int Enabled;
		int PicResno;
		double X;
		double Y;
		double R;
		double Z;
	}
	PicInfo;

	int CrashFrame; // 0: �ʏ�, 1-: �N���b�V����
	int Crashed;
}
Enemy_t;

Enemy_t *CreateEnemy_ved(
	int (*funcProc)(Enemy_t *, void *),
	void (*funcDraw)(Enemy_t *, void *),
	void (*funcRelease)(void *),
	int hp,
	EnemyCommonData_t *commonData,
	void *extraData
	);
void ReleaseEnemy(Enemy_t *);

void GmProcEnemy(void);
void GmDrawEnemy(int wall_mode);

void PutEnemyPicInfo(Enemy_t *e, int picResno, double x, double y, double r = 0.0, double z = 1.0);
void PutEnemyCrashAreaByPI(Enemy_t *e);
void DrawEnemyByPI(Enemy_t *e);
int ProcPShotEnemyCrash(Enemy_t *e, double z, double y, double r);
int ProcPShotEnemyCrashByPI(Enemy_t *e, double zoom = 1.0);

template <class ExtraData_t>
Enemy_t *CreateEnemy(
	int (*funcProc)(Enemy_t *, ExtraData_t *),
	void (*funcDraw)(Enemy_t *, ExtraData_t *),
	void (*funcRelease)(ExtraData_t *),
	int hp,
	EnemyCommonData_t *commonData,
	ExtraData_t *extraData
	)
{
	if(!extraData)
		extraData = nb(ExtraData_t);

	return CreateEnemy_ved(
		(int (*)(Enemy_t *, void *))funcProc,
		(void (*)(Enemy_t *, void *))funcDraw,
		(void (*)(void *))funcRelease,
		hp,
		commonData,
		extraData
		);
}

// e: NULL ok
#define EProcIs(e, eProc) \
	((e) && (e)->ProcFunc == (int (*)(Enemy_t *, void *))(eProc))

#define IsWall(e) \
	EProcIs((e), EProc_Wall)

void LoadMapEnemyData(autoList<Enemy_t *> *outList, autoList<MapCellData_t *> *list);
void AddEnemy(double x, double y, Enemy_t *e);
void TamaCleanup(void);
