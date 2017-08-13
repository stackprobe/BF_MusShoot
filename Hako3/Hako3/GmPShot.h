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

	// ��Params {
	int Level; // TAME_LV �Ƃ͕ʁA����ŗL�̃��x��(�C��)
	// }

	int Crashed; // �����ƃN���b�V�����Ă���B(PShotProc�ŏ����� -> EnemyProc�Őݒ� -> ����PShotProc�ŎQ��), 2 == �ǂƃN���b�V��
	int Death; // ���� Proc �ŊJ������B
	int Frame;

	union // ��Params
	{
		struct
		{
			double Speed;
		}
		Miracle;

		struct
		{
			double HankeiRate;
			int ShotEndFrame; // == ps->Frame ���u���˒��v�Ō�̃t���[���Ƃ���B
			double ShotX;
			double ShotY;
			double TailX;
			double TailY;
		}
		Laser;

		struct
		{
			double Hankei; // == �����ڂ̔��a
			int HaneRemCnt; // ���˕Ԃ��
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
			double Scale; // ���̒���
			int RotDir; // 0 == ������, 1 == ���v���, -1 == �����v���
			double Rot; // PShot_t.R ����
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
