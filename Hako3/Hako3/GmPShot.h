typedef enum PShTyp_st // PlayerShotType
{
	PST_NORMAL,
	PST_LV1,
	PST_LV2,
	PST_LV3,
	PST_MIRACLE,
	PST_MIRACLE_MINI,

#define IsPSTNormal(e) m_isRange((e), PST_NORMAL, PST_MIRACLE_MINI)

	PST_LASER,
	PST_LASER_CUTTER,

#define IsPSTLaser(e) m_isRange((e), PST_LASER, PST_LASER_CUTTER)

	PST_ROCK,
	PST_ROCK_HAMMER,

#define IsPSTHoming(e) m_isRange((e), PST_ROCK, PST_ROCK_HAMMER)

	PST_SLOW,
	PST_SLOW_SHOT,

#define IsPSTSlow(e) m_isRange((e), PST_SLOW, PST_SLOW_SHOT)

	PST_BLADE,
	PST_BLADE_SHOT,

#define IsPSTBlade(e) m_isRange((e), PST_BLADE, PST_BLADE_SHOT)

	PST_DBL_SPREAD,
	PST_DBL_BOUNCE,

#define IsPSTDouble(e) m_isRange((e), PST_DBL_SPREAD, PST_DBL_BOUNCE)

	PST_MAX, // num of member
}
PShTyp_t;

typedef struct PShot_st // PlayerShot
{
	PShTyp_t PShTyp;
	double X;
	double Y;
	double R;

	// 個別Params {
	int Level; // TAME_LV とは別、武器固有のレベル(任意)
	// }

	int Crashed; // 何かとクラッシュしている。(PShotProcで初期化 -> EnemyProcで設定 -> 次のPShotProcで参照), 2 == 壁とクラッシュ
	int Death; // 次の Proc で開放する。
	int Frame;

	union // 個別Params
	{
		struct
		{
			double Speed;
		}
		Miracle;

		struct
		{
			double HankeiRate;
			int ShotEndFrame; // == ps->Frame を「発射中」最後のフレームとする。
			double ShotX;
			double ShotY;
			double TailX;
			double TailY;
		}
		Laser;

		struct
		{
			double Hankei; // == 見た目の半径
			int HaneRemCnt; // 跳ね返る回数
			double Rot;
			double RotAdd;
			double XAdd;
			double YAdd;
		}
		Rock;

		struct
		{
			double Speed;
			double TargetSpeed;
			double R;
			double TargetR;
			double Rot;
			double RotAdd;
		}
		Slow;

		struct
		{
			double Scale; // 剣の長さ
			int RotDir; // 0 == 未決定, 1 == 時計廻り, -1 == 反時計廻り
			double Rot; // PShot_t.R 相対
		}
		Blade;

		struct
		{
			double Hankei;
			int BounceRemCnt;
		}
		Double;
	}
	u;
}
PShot_t;

PShot_t *CreatePShot(PShTyp_t pShTyp, double x, double y, double r = 0.0);
void ReleasePShot(PShot_t *i);

void GmProcPShot(void);
void GmDrawPShot(void);

void DestroyCurrRockHammer(void);
void DestroyCurrSlowBarrier(void);
void DestroyCurrBlade(void);
