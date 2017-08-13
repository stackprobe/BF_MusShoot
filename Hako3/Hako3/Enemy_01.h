typedef struct ED_Wall_st
{
	int PicIndex;
	int PicXPos;
	int PicYPos;
}
ED_Wall_t;

ED_Wall_t *CreateED_Wall(int picIndex, int picXPos, int picYPos);
ED_Wall_t *CreateED_Wall(autoList<char *> *lines);
void ReleaseED_Wall(ED_Wall_t *i);
int EProc_Wall(Enemy_t *i, ED_Wall_t *ed);
void EDraw_Wall(Enemy_t *i, ED_Wall_t *ed);

typedef struct ED_Fei_st
{
	double Speed;
	double Rot;
	double RotSpeed;
	double RotZoom;
	int ShotFrame; // 0 == ñ≥å¯
	double TrueY;
}
ED_Fei_t;

ED_Fei_t *CreateED_Fei(double speed, double rot, double rotSpeed, double rotZoom);
ED_Fei_t *CreateED_Fei(autoList<char *> *lines);
void ReleaseED_Fei(ED_Fei_t *i);
int EProc_Fei(Enemy_t *i, ED_Fei_t *ed);
void EDraw_Fei(Enemy_t *i, ED_Fei_t *ed);

typedef struct ED_EShot_st
{
	double XAdd;
	double YAdd;
	int SmallMode;
	int ColorIndex;
}
ED_EShot_t;

ED_EShot_t *CreateED_EShot(double xSpeed, double ySpeed, int sm = 0, int colorIdx = 0);
ED_EShot_t *CreateED_EShot(autoList<char *> *lines);
void ReleaseED_EShot(ED_EShot_t *i);
int EProc_EShot(Enemy_t *i, ED_EShot_t *ed);
void EDraw_EShot(Enemy_t *i, ED_EShot_t *ed);

void ShotEnemy(double x, double y, ED_EShot_t *bind_ed);
void ShotEnemy_XY(double x, double y, double xSpeed, double ySpeed, int sm = 0, int colorIdx = 0);
void ShotEnemy_XYS(double x, double y, double xDir, double yDir, double speed, int sm = 0, int colorIdx = 0);
void ShotEnemy_SR(double x, double y, double speed, double speedRot, int sm = 0, int colorIdx = 0);

typedef struct ED_Hikaru_st
{
	int SekkinFrame; // 1-
	double SekkinRate;
	double TeishiXPos;
	double TeishiYRelPos; // èoåªà íuÇ©ÇÁÇÃëäëŒ
	int TeishiFrame; // 1-
	double RidatsuXAdd;
	double RidatsuYAdd;
	double RidatsuXAdd2;
	double RidatsuYAdd2;

	// ... init

	double TeishiYPos;
}
ED_Hikaru_t;

ED_Hikaru_t *CreateED_Hikaru(
	int sekkin_frm,
	double sekkin_rate,
	double teishi_x,
	double teishi_y,
	int teishi_frm,
	double ridatsu_xSpeed,
	double ridatsu_ySpeed,
	double ridatsu_xKasokudo,
	double ridatsu_yKasokudo
	);
ED_Hikaru_t *CreateED_Hikaru(autoList<char *> *lines);
void ReleaseED_Hikaru(ED_Hikaru_t *i);
int EProc_Hikaru(Enemy_t *i, ED_Hikaru_t *ed);
void EDraw_Hikaru(Enemy_t *i, ED_Hikaru_t *ed);

typedef struct ED_Lina_st
{
	int SakasaMode;
	int ShotCycle;
}
ED_Lina_t;

ED_Lina_t *CreateED_Lina(int sakasa_mode, int shot_cycle);
ED_Lina_t *CreateED_Lina(autoList<char *> *lines);
void ReleaseED_Lina(ED_Lina_t *i);
int EProc_Lina(Enemy_t *i, ED_Lina_t *ed);
void EDraw_Lina(Enemy_t *i, ED_Lina_t *ed);

typedef struct ED_Ningyo_st
{
	int JumpMode;
	int JumpFrame;

	// ... init

	double ChakuchiYPos;
	int ChakuchiOk;
	int AttackFrame;
	int AttackSleepFrame;
}
ED_Ningyo_t;

ED_Ningyo_t *CreateED_Ningyo(int jump_mode, int jump_frm);
ED_Ningyo_t *CreateED_Ningyo(autoList<char *> *lines);
void ReleaseED_Ningyo(ED_Ningyo_t *i);
int EProc_Ningyo(Enemy_t *i, ED_Ningyo_t *ed);
void EDraw_Ningyo(Enemy_t *i, ED_Ningyo_t *ed);

typedef struct ED_NingyoDead_st
{
	double YAdd;
}
ED_NingyoDead_t;

ED_NingyoDead_t *CreateED_NingyoDead(void);
void ReleaseED_NingyoDead(ED_NingyoDead_t *i);
int EProc_NingyoDead(Enemy_t *i, ED_NingyoDead_t *ed);
void EDraw_NingyoDead(Enemy_t *i, ED_NingyoDead_t *ed);
