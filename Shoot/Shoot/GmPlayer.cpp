#include "Stdinc.h"

int GmPlayerIsCrash(double x, double y)
{
	return GetCrashedEnemy(x, y) != NULL;
}
static void AddMiracleShotEffect(double x, double y, double z, int rev_x)
{
	GTACE_BlendAddMode = 1;
	GTACE_PicResnoIncDelay = 1;
	GTACE_PicResnoEnd = P_NEWMIRACLE_HASSHA_00 + 9;
	GTACE_ReverseX = rev_x;
	GTAddCommonEffect_ZR(
		GmDc.EffectList,
		P_NEWMIRACLE_HASSHA_00,
		1,
		0,
		x, y, z
		);
	GTACE_Reset();
}
static void AddRockStarEffect(int c_max, double x, double y, double z, double xSpeed, double xSpBure, double ySpeed, double ySpBure, double lifeDecRate, double lifeDecRateBure)
{
	for(int c = 0; c < c_max; c++)
	{
		double ldr = lifeDecRate + lifeDecRateBure * eRnd();

		GTACE_BlendAddMode = 1;
		GTACE_SpeedRate = 1.0 - 0.2 * ldr;
		GTACE_RotSpeedRate = 1.0 - 0.1 * ldr;
		GTAddCommonEffect_ZR(
			GmDc.EffectList,
			P_ROCK_STAR,
			0,
			0,
			x, y, z, 0.0, 1.0,
			xSpeed + xSpBure * eRnd(), ySpeed + ySpBure * eRnd(), 0.0, (0.2 + 0.3 * dRnd()) * sRnd(), -0.05 * ldr
			);
		GTACE_Reset();
	}
}
void GmProcPlayer(void)
{
	double lx = GmDc.Player.X;
	double ly = GmDc.Player.Y;

	double dx = MouseMoveX * Sd.PlayerMouseMoveRate;
	double dy = MouseMoveY * Sd.PlayerMouseMoveRate;

	double dr = sqrt(m_pow(dx) + m_pow(dy));

	double nx = lx + dx;
	double ny = ly + dy;

	// 移動量計測
	{
		if(dr < 1.5)
		{
			m_countDown(GmDc.Player.XCant);
			m_countDown(GmDc.Player.YCant);

			if(GmDc.Player.XCant == 0 && GmDc.Player.YCant == 0)
				GmDc.Player.CantDir = 5;
		}
		else if(dr < 3.5)
		{
			// noop
		}
		else
		{
			const int ADD_PNT = 3;

			if(abs(dx) < abs(dy))
			{
				if(dy < 0.0)
				{
					GmDc.Player.YCant = m_min(GmDc.Player.YCant, 0);
					GmDc.Player.YCant -= ADD_PNT;
				}
				else
				{
					GmDc.Player.YCant = m_max(GmDc.Player.YCant, 0);
					GmDc.Player.YCant += ADD_PNT;
				}
//				m_countDown(GmDc.Player.XCant);
				GmDc.Player.XCant = 0;
			}
			else
			{
				if(dx < 0.0)
				{
					GmDc.Player.XCant = m_min(GmDc.Player.XCant, 0);
					GmDc.Player.XCant -= ADD_PNT;
				}
				else
				{
					GmDc.Player.XCant = m_max(GmDc.Player.XCant, 0);
					GmDc.Player.XCant += ADD_PNT;
				}
//				m_countDown(GmDc.Player.YCant);
				GmDc.Player.YCant = 0;
			}

			const int BDR_PNT = 15;

			m_range(GmDc.Player.XCant, -BDR_PNT, BDR_PNT);
			m_range(GmDc.Player.YCant, -BDR_PNT, BDR_PNT);

			if(abs(GmDc.Player.XCant) < abs(GmDc.Player.YCant))
			{
				     if(GmDc.Player.YCant <= -BDR_PNT) GmDc.Player.CantDir = 8;
				else if(GmDc.Player.YCant >=  BDR_PNT) GmDc.Player.CantDir = 2;
			}
			else
			{
				     if(GmDc.Player.XCant <= -BDR_PNT) GmDc.Player.CantDir = 4;
				else if(GmDc.Player.XCant >=  BDR_PNT) GmDc.Player.CantDir = 6;
			}
		}
	}

	// 当たり判定
	{
		int crashed = 0;
		int denom = (int)(dr / 10.0);

		if(2 <= denom)
		{
			for(int numer = 1; numer < denom; numer++)
			{
				double ax = lx + (dx * numer) / denom;
				double ay = ly + (dy * numer) / denom;

				if(GmPlayerIsCrash(ax, ay))
				{
					crashed = 1;
					nx = ax;
					ny = ay;
					break;
				}
			}
		}
		else
			crashed = GmPlayerIsCrash(nx, ny);

		if(!GmDc.Player.CrashFrame)
		{
			if(crashed)
			{
				m_countDown(GmDc.Player.HP);
				GmDc.Player.CrashFrame = PLAYER_CRASH_MAX;
			}
		}
		else
			m_countDown(GmDc.Player.CrashFrame);
	}

	m_range(nx, 0.0, (double)SCREEN_W);
	m_range(ny, 0.0, (double)SCREEN_H);

	GmDc.Player.X = nx;
	GmDc.Player.Y = ny;
	GmDc.Player.LastMoveX = dx;
	GmDc.Player.LastMoveY = dy;

	if(GmDc.Player.CrashFrame == PLAYER_CRASH_MAX) // ? PlayerCrashed (クラッシュ開始)
	{
		GmDc.Player.ToujouFrame = 0;
		GmDc.Player.T_X = -100.0; // HACK
		GmDc.Player.T_Y = -100.0; // HACK
		GmDc.Player.CrashedX = GmDc.Player.X;
		GmDc.Player.CrashedY = GmDc.Player.Y;
	}
	else if(GmDc.Player.CrashFrame == PLAYER_CRASH_MAX - 60)
	{
		TamaCleanup();
	}

	/*
		---- 加重移動平均速度 ----

		一方向に、普通に動かして 100 - 200
		めちゃくちゃ速く動かすと 1000 - 2000
	*/
	GmDc.Player.MASpeedX += dx;
	GmDc.Player.MASpeedY += dy;
	GmDc.Player.MASpeedX *= 0.9;
	GmDc.Player.MASpeedY *= 0.9;

// test
//clsDx();
//printfDx("%f %f\n", GmDc.Player.LastSpeedX, GmDc.Player.LastSpeedY);

	{
		const double DIR_CHG = 3.0;

			 if(GmDc.Player.MASpeedX < DIR_CHG) GmDc.Player.LastDirX = -1;
		else if(GmDc.Player.MASpeedX > DIR_CHG) GmDc.Player.LastDirX = 1;
			 if(GmDc.Player.MASpeedY < DIR_CHG) GmDc.Player.LastDirY = -1;
		else if(GmDc.Player.MASpeedY > DIR_CHG) GmDc.Player.LastDirY = 1;
	}

	// change TraceR
	{
		const double R = 50.0;

		double x = cos(GmDc.Player.TraceR) * R;
		double y = sin(GmDc.Player.TraceR) * R;

		x -= dx;
		y -= dy;

		GmDc.Player.TraceR = P2Angle(0.0, 0.0, x, y);
	}

	// ... 移動ここまで

	if(GmDc.Player.CrashFrame)
	{
		GmDc.Player.Tame = 0;
		goto endShot;
	}
	if(1 <= MouseL)
	{
		const int TAME_SPEED = 8;

		if(GmDc.Player.Tame < TAME_MAX)
		{
			GmDc.Player.Tame += TAME_SPEED;
			m_minim(GmDc.Player.Tame, TAME_MAX);

			if(GmDc.Player.Tame == TAME_MAX)
				GmDc.Player.TameMaxFlash = 1.0;
		}
		int lv;

		     if(TAME_MAX == GmDc.Player.Tame) lv = TAME_LV_MAX;
		else if(TAME_LV3 <= GmDc.Player.Tame) lv = 3;
		else if(TAME_LV2 <= GmDc.Player.Tame) lv = 2;
		else if(TAME_LV1 <= GmDc.Player.Tame) lv = 1;
		else                                  lv = 0;

		if(GmDc.Player.TameLv < lv)
		{
			GmDc.Player.TameSemiFlash = 1.0;
			GmDc.Player.TameLv = lv;
		}
	}
	else if(GmDc.Player.Tame)
	{
		// 発射Pos
		double txd = 10.0;
		double tyd = 0.0;
		double tx = GmDc.Player.X + txd;
		double ty = GmDc.Player.Y + tyd;

		PShot_t *ps = NULL;

		switch(GmDc.Player.CurrWeapon)
		{
		case WEAPON_NORMAL:
			switch(GmDc.Player.TameLv)
			{
			case 0:
				ps = CreatePShot(PST_NORMAL, tx, ty);
				break;

			case 1:
				ps = CreatePShot(PST_LV1, tx, ty);
				break;

			case 2:
				ps = CreatePShot(PST_LV2, tx, ty);
				break;

			case 3:
				ps = CreatePShot(PST_LV3, tx, ty);
				break;

			case TAME_LV_MAX:
				ps = CreatePShot(PST_MIRACLE, tx, ty);

				AddMiracleShotEffect(tx + 70.0, ty, 1.5, 0); // 効果
				break;

			default:
				error();
			}
			break;

		case WEAPON_LASER:
			{
				ps = CreatePShot(PST_LASER, tx, ty);

				if(!GmDc.Player.TameLv)
					ps->PShTyp = PST_LASER_CUTTER;

				ps->Level = GmDc.Player.TameLv;

				double hr;
				int sef;

				switch(GmDc.Player.TameLv)
				{
				case 0:
					hr = 1.0; // dummy
					sef = 1; // dummy
					break;
				case 1:
					hr = 1.0;
					sef = 20;
					break;
				case 2:
					hr = 2.5;
					sef = 25;
					break;
				case 3:
					hr = 5.0;
					sef = 35;
					break;
				case TAME_LV_MAX:
					hr = 7.5;
					sef = 50;
					break;

				default:
					error();
				}
				ps->u.Laser.HankeiRate = hr;
				ps->u.Laser.ShotEndFrame = sef;
			}
			break;

			/*
				0 - PST_ROCK 小 -> Level 0
				1 - PST_ROCK 大 -> Level 1
				2 - PST_ROCK_HAMMER 小 -> Level 0
				3 - PST_ROCK_HAMMER 中 -> Level 1
				4 - PST_ROCK_HAMMER 大 -> Level 2
			*/
		case WEAPON_ROCK:
			{
				ps = CreatePShot(PST_ROCK_HAMMER, tx, ty);

				// 慣性
				double kx = GmDc.Player.MASpeedX / 100.0;
				double ky = GmDc.Player.MASpeedY / 100.0;
				P2Vector(kx, ky, 2.0);

				double ky2 = GmDc.Player.MASpeedY;
				m_range(ky2, -30.0, 30.0);

				switch(GmDc.Player.TameLv)
				{
				case 0:
					ps->PShTyp = PST_ROCK;
					ps->Level = 0;
					ps->u.Rock.Hankei = 8.0;
					ps->u.Rock.HaneRemCnt = 1;
					ps->u.Rock.XAdd = 4.0 + kx;
					ps->u.Rock.YAdd = 1.5 + ky;

					AddRockStarEffect(3, tx, ty, 0.5, 5.5, 4.5, 0.0, 5.0, 1.0, 0.1);
					break;
				case 1:
					ps->PShTyp = PST_ROCK;
					ps->Level = 1;
					ps->u.Rock.Hankei = 16.0;
					ps->u.Rock.HaneRemCnt = 3;
					ps->u.Rock.XAdd = 8.0;

					{
						PShot_t *ps2 = CreatePShot(
							PST_ROCK_HAMMER,
							GmDc.Player.X - 10.0,
							GmDc.Player.Y
							);

						ps2->PShTyp = PST_ROCK;
						ps->Level = 1;
						ps2->u.Rock.Hankei     = ps->u.Rock.Hankei;
						ps2->u.Rock.HaneRemCnt = ps->u.Rock.HaneRemCnt;
						ps2->u.Rock.XAdd      = -ps->u.Rock.XAdd;
						ps2->u.Rock.Rot        = dRnd() * PI * 2.0;
						ps2->u.Rock.RotAdd     = -0.05 - 0.05 * dRnd();

						GmDc.PShotList->AddElement(ps2);

						ps->u.Rock.XAdd += kx;
						ps->u.Rock.YAdd += ky;
						ps2->u.Rock.XAdd += kx;
						ps2->u.Rock.YAdd += ky;

						AddRockStarEffect(3, tx, ty, 0.75, 6.5, 5.5, 0.0, 6.0, 1.0, 0.1);
					}
					AddRockStarEffect(3, GmDc.Player.X - txd, GmDc.Player.Y - tyd, 0.75, -6.5, -5.5, 0.0, 6.0, 1.0, 0.1);
					break;

					// Hammer ...
				case 2:
					ps->Level = 0;
					ps->u.Rock.Hankei = 16.0;
					ps->u.Rock.XAdd = 70.0;

					AddRockStarEffect(10, tx, ty, 1.0, 10.5, 11.5, 0.0, 20.0, 0.8, 0.1);
					break;
				case 3:
					ps->Level = 1;
					ps->u.Rock.Hankei = 32.0;
					ps->u.Rock.XAdd = 80.0;

					AddRockStarEffect(15, tx, ty, 1.5, 13.5, 14.5, 0.0, 26.0, 0.6, 0.1);
					break;
				case TAME_LV_MAX:
					ps->Level = 2;
					ps->u.Rock.Hankei = 64.0;
					ps->u.Rock.XAdd = 90.0;

					AddRockStarEffect(20, tx, ty, 2.0, 16.5, 17.5, 0.0, 32.0, 0.4, 0.1);
					break;

				default:
					error();
				}

				ps->u.Rock.Rot = dRnd() * PI * 2.0;
				ps->u.Rock.RotAdd = 0.05 + 0.05 * dRnd();

				DestroyCurrRockHammer(); // 何か撃ったら消す。

				if(ps->PShTyp == PST_ROCK_HAMMER)
				{
					ps->u.Rock.YAdd = ky2;

//					DestroyCurrRockHammer(); // 新しいロックハンマーを作成したので、古いロックハンマーを削除
					GmDc.CurrRockHammer = ps;
				}
			}
			break;

			/*
				0 - PST_SLOW_SHOT 小 -> Level 0
				1 - PST_SLOW_SHOT 大 -> Level 1
				2 - PST_SLOW 小 -> Level 0
				3 - PST_SLOW 中 -> Level 1
				4 - PST_SLOW 大 -> Level 2
			*/
		case WEAPON_SLOW:
			{
				switch(GmDc.Player.TameLv)
				{
				case 0:
				case 1:
					ps = CreatePShot(PST_SLOW_SHOT, tx, ty);
					break;

				default:
					ps = CreatePShot(PST_SLOW, GmDc.Player.X, GmDc.Player.Y);

					ps->u.Slow.R = 10.0;
					ps->u.Slow.Rot = 2.0 * PI * dRnd();
					ps->u.Slow.RotAdd = 0.01;
					break;
				}

				double ky = GmDc.Player.MASpeedX / 200.0;
				m_range(ky, -1.0, 1.0);

				switch(GmDc.Player.TameLv)
				{
				case 0:
					ps->Level = 0;
					ps->u.Slow.Speed = 6.0 + ky;
					ps->u.Slow.TargetSpeed = 2.0;
					break;

				case 1:
					ps->Level = 1;
					ps->u.Slow.Speed = 4.0 + ky;
					ps->u.Slow.TargetSpeed = 1.5;
					break;

					// PST_SLOW ...
				case 2:
					{
						ps->Level = 0;
						ps->u.Slow.TargetR = 50.0;
					}
					break;

				case 3:
					{
						ps->Level = 1;
						ps->u.Slow.TargetR = 100.0;
					}
					break;

				case TAME_LV_MAX:
					{
						ps->Level = 2;
						ps->u.Slow.TargetR = 150.0;
					}
					break;

				default:
					error();
				}

				if(ps->PShTyp == PST_SLOW)
				{
					DestroyCurrSlowBarrier(); // 前のバリアを消す。
					GmDc.CurrSlowBarrier = ps;
				}
			}
			break;

			/*
				0 - PST_BLADE_SHOT 小 -> Level 0
				1 - PST_BLADE_SHOT 大 -> Level 1
				2 - PST_BLADE 小 -> Level 0
				3 - PST_BLADE 中 -> Level 1
				4 - PST_BLADE 大 -> Level 2
			*/
		case WEAPON_BLADE:
			{
				switch(GmDc.Player.TameLv)
				{
				case 0:
					for(double r = PI / 4.0; r < PI * 2.0; r += PI * 1.5)
					{
						const double R = 10.0;

						ps = CreatePShot(
							PST_BLADE_SHOT,
							GmDc.Player.X + cos(r) * R,
							GmDc.Player.Y + sin(r) * R,
							r
							);
						ps->Level = 0;
	
						GmDc.PShotList->AddElement(ps);
						ps = NULL;
					}
					break;

				case 1:
					for(double r = PI / 4.0; r < PI * 2.0; r += PI / 2.0)
					{
						const double R = 10.0;

						ps = CreatePShot(
							PST_BLADE_SHOT,
							GmDc.Player.X + cos(r) * R,
							GmDc.Player.Y + sin(r) * R,
							r
							);
						ps->Level = 1;

						GmDc.PShotList->AddElement(ps);
						ps = NULL;
					}
					break;

				default:
					{
						ps = CreatePShot(
							PST_BLADE,
							0.0, // dummy
							0.0, // dummy
							GmDc.Player.TraceR
							);
					}
					break;
				}

				switch(GmDc.Player.TameLv)
				{
				case 0:
				case 1:
					break;

					// PST_BLADE ...
				case 2:
					{
						ps->Level = 0;
						ps->u.Blade.Scale = 100.0;
					}
					break;

				case 3:
					{
						ps->Level = 1;
						ps->u.Blade.Scale = 150.0;
					}
					break;

				case TAME_LV_MAX:
					{
						ps->Level = 2;
						ps->u.Blade.Scale = 200.0;
					}
					break;

				default:
					error();
				}

				DestroyCurrBlade(); // 何か撃ったら消す。

				if(ps) // ? shot -> NULL
				{
					if(ps->PShTyp == PST_BLADE)
					{
						GmDc.CurrBlade = ps;
					}
				}
			}
			break;

			/*
				0 - PST_DBL_SPREAD 小 -> Level 0
				1 - PST_DBL_SPREAD 大 -> Level 1
				2 - PST_DBL_BOUNCE 小 -> Level 0
				3 - PST_DBL_BOUNCE 中 -> Level 1
				4 - PST_DBL_BOUNCE 大 -> Level 2
			*/
		case WEAPON_DOUBLE:
			{
				switch(GmDc.Player.TameLv)
				{
				case 0:
					{
						const double R = 10.0;
						double pTR = GmDc.Player.TraceR;

						ps = CreatePShot(
							PST_DBL_SPREAD,
							GmDc.Player.X + cos(pTR) * R,
							GmDc.Player.Y + sin(pTR) * R,
							pTR
							);
						ps->Level = 0;
					}
					break;

				case 1:
					for(int c = -3; c <= 3; c++)
					{
						const double R = 10.0;
						double pTR = GmDc.Player.TraceR;

						ps = CreatePShot(
							PST_DBL_SPREAD,
							GmDc.Player.X + cos(pTR) * R,
							GmDc.Player.Y + sin(pTR) * R,
							pTR + c * 0.05
							);
						ps->Level = 1;

						GmDc.PShotList->AddElement(ps);
						ps = NULL;
					}
					break; // ! ここだけ ps == NULL

				default:
					{
						const double R = 10.0;
						double pTR = GmDc.Player.TraceR;

						ps = CreatePShot(
							PST_DBL_BOUNCE,
							GmDc.Player.X + cos(pTR) * R,
							GmDc.Player.Y + sin(pTR) * R,
							pTR
							);
					}
					break;
				}

				switch(GmDc.Player.TameLv)
				{
				case 0:
				case 1:
					break;

					// PST_DBL_BOUNCE ...
				case 2:
					{
						ps->Level = 0;
						ps->u.Double.Hankei = 15.0;
						ps->u.Double.BounceRemCnt = 3;
					}
					break;

				case 3:
					{
						ps->Level = 1;
						ps->u.Double.Hankei = 20.0;
						ps->u.Double.BounceRemCnt = 5;
					}
					break;

				case TAME_LV_MAX:
					{
						ps->Level = 2;
						ps->u.Double.Hankei = 30.0;
						ps->u.Double.BounceRemCnt = 7;
					}
					break;

				default:
					error();
				}

				if(ps) // NULL 有り注意
				{
				}
			}
			break;

		default:
			break;
		}
		
		if(ps)
			GmDc.PShotList->AddElement(ps);

		// 効果
		{
			double a = (double)GmDc.Player.Tame / TAME_MAX;

			a *= a;
			a *= 0.8;

			for(int c = 1; c <= 3; c++)
			{
				GTACE_BlendAddMode = 1;
				GTAddCommonEffect_ZR(
					GmDc.EffectList,
					P_TAME_JIN_STAR,
					0,
					0,
					GmDc.Player.X, GmDc.Player.Y, 1.0, PI * 2.0 * dRnd(), a,
					0.0, 0.0, 0.02 * c, 0.02 * c, -0.02
					);
				GTACE_BlendAddMode = 0;
			}
		}

		GmDc.Player.Tame = 0;
		GmDc.Player.TameLv = 0;
		GmDc.Player.TameMaxFlash = 0.0;
		GmDc.Player.TameSemiFlash = 0.0;
	}
endShot:

	GmDc.Player.LastWeaponRotDir = 0;
	GmDc.Player.LastWeapon = GmDc.Player.CurrWeapon;

	if(MouseWheelRot)
	{
		if(
			GmDc.Player.WeaponRot < 0 && 0 < MouseWheelRot ||
			GmDc.Player.WeaponRot > 0 && 0 > MouseWheelRot
			)
			GmDc.Player.WeaponRot = 0;

		GmDc.Player.WeaponRot += MouseWheelRot;

		if(
			GmDc.Player.WeaponRot <= -Sd.WeaponRotMax ||
			Sd.WeaponRotMax <= GmDc.Player.WeaponRot
			)
		{
			int rotDir = m_iSign(GmDc.Player.WeaponRot);

			GmDc.Player.CurrWeapon = (GmDc.Player.CurrWeapon + rotDir + WEAPON_MAX) % WEAPON_MAX; // １フレームで最大１しか動かないこと。
			GmDc.Player.WeaponRot += -rotDir * Sd.WeaponRotMax;
			GmDc.Player.WeaponFrame = 0;
			GmDc.Player.LastWeaponRotDir = rotDir;
			
			// 武器変更Event
			{
				DestroyCurrRockHammer();
				DestroyCurrSlowBarrier();
				DestroyCurrBlade();
			}
		}
		else
		{
			if(GmDc.Player.WeaponFrame == 60)
				GmDc.Player.WeaponRot = 0;

			GmDc.Player.WeaponFrame++;
		}
	}

	switch(GmDc.Player.CurrWeapon)
	{
	case WEAPON_DOUBLE:
		{
			GmDc.DoDrawPlayerDir = 1;
			GmDc.D_PlayerDir = GmDc.Player.TraceR;
		}
		break;

	case WEAPON_BLADE:
		{
			if(2 <= GmDc.Player.TameLv)
			{
				GmDc.DoDrawPlayerDir = 1;
#if 1
				GmDc.D_PlayerDir = GmDc.Player.TraceR;
#else // 2468 only
				switch(m_d2i(GmDc.Player.TraceR / (PI * 0.5)))
				{
				case 1: GmDc.D_PlayerDir = PI * 0.5; break;
				case 2: GmDc.D_PlayerDir = PI * 1.0; break;
				case 3: GmDc.D_PlayerDir = PI * 1.5; break;

				default:
					GmDc.D_PlayerDir = 0.0;
					break;
				}
#endif
			}
		}
		break;

	default: // other weapon
		break;
	}
}
void GmDrawPlayer(void)
{
	if(GmDc.Player.CrashFrame)
	{
		int frm = PLAYER_CRASH_MAX - GmDc.Player.CrashFrame;
		int animidx = (frm / 6) % 4;

		double deadRate = GmDc.Player.CrashFrame / (double)PLAYER_CRASH_MAX;
		deadRate *= 2.0;
		deadRate -= 1.0;

		SetAlpha(deadRate);
		DrawPic(
			GmDc.Player.CrashedX,
			GmDc.Player.CrashedY,
			Der(D_PLAYER_CRASH_00 + animidx)
			);
		ResetBlend();
	}
	int picResno;

	switch(GmDc.Player.CantDir)
	{
	case 5:
		picResno = P_WILL_500 + (LFrmCnt / 4) % 8;
		break;
	case 8:
		picResno = P_WILL_800 + (LFrmCnt / 6) % 2;
		break;
	case 2:
		picResno = P_WILL_200 + (LFrmCnt / 6) % 2;
		break;
	case 6:
		picResno = P_WILL_600 + (LFrmCnt / 4) % 8;
		break;
	case 4:
		picResno = P_WILL_400 + (LFrmCnt / 4) % 8;
		break;

	default:
		error();
	}
	double charPosX = GmDc.Player.X;
	double charPosY = GmDc.Player.Y;

	if(GmDc.Player.ToujouFrame < PLAYER_TOUJOU_MAX)
	{
		charPosX = GmDc.Player.T_X;
		charPosY = GmDc.Player.T_Y;
	}
	DrawPic(charPosX, charPosY, Pic(picResno));

	if(GmDc.Player.Tame)
	{
		double tameRate = (double)GmDc.Player.Tame / TAME_MAX;
		double a = tameRate;
		static double colRot;

		a *= (1.0 + sin(colRot)) / 2.0;

		SetBlendAdd(a);
		DrawPic(charPosX, charPosY, Pic(picResno));
		ResetBlend();

		colRot += tameRate * 0.8;
	}

	// 効果 ...

	if(LFrmCnt % 10 == 0)
	{
		GTACE_BlendAddMode = 1;
		GTACE_Haneru = 1;
		GTAddCommonEffect_ZR(
			GmDc.EffectList,
			P_YELLOW_STAR,
			0,
			0,
			charPosX - 28.0 + 2.0 * eRnd(), charPosY + 4.0 + 2.0 * eRnd(), 0.5, PI * 2.0 * dRnd(), 1.0,
			-1.0 - 2.0 * dRnd(), 0.0, 0.0, 0.2 * eRnd(), -0.03 - 0.02 * dRnd(),
			0.0, 0.2
			);
		GTACE_Reset();
	}
	if(GmDc.Player.Tame)
	{
		double a = (double)GmDc.Player.Tame / TAME_MAX;

		a *= a;

		SetBlendAdd(a);
		DrawBegin(charPosX, GmDc.Player.Y, Pic(P_TAME_JIN));
		DrawRotate(LFrmCnt / 13.0);
		DrawEnd();
		DrawBegin(charPosX, GmDc.Player.Y, Pic(P_TAME_JIN_STAR));
		DrawRotate(LFrmCnt / 7.0);
		DrawEnd();
		ResetBlend();
	}

	if(GmDc.DoDrawPlayerDir)
	{
		const double R = 40.0;
		double pdR = GmDc.D_PlayerDir;

		DrawBegin(
			charPosX + cos(pdR) * R,
			charPosY + sin(pdR) * R,
			Pic(P_DIRECTION)
			);
		DrawRotate(pdR + PI / 2.0);
		DrawZoom(1.25 + sin(LFrmCnt / 5.0) * 0.25);
		DrawEnd();
	}

#if 0
	// test
	{
		int px = m_d2i(GmDc.Player.X);
		int py = m_d2i(GmDc.Player.Y);
		int cGB = GmDc.Player.Crashed ? 0 : 255;
		DrawLine(px, 0, px, 480, GetColor(255, cGB, cGB));
		DrawLine(0, py, 640, py, GetColor(255, cGB, cGB));
	}
#endif
}
void GmDrawPlayerStatus(void)
{
	static double north_a = 1.0;
	static double south_a = 1.0;

	if(GmDc.Player.Y < 80)
		m_countApprox(north_a, 0.3, 0.85, 0.0);
	else
		m_countApprox(north_a, 1.0, 0.95, 0.0);

	if(400 < GmDc.Player.Y)
		m_countApprox(south_a, 0.3, 0.85, 0.0);
	else
		m_countApprox(south_a, 1.0, 0.95, 0.0);

	// ==== FACE ====

	{
		static int animcnt;
		static int slpcnt;
		int face;

			 if(GmDc.Player.HP <=  3) face = 3;
		else if(GmDc.Player.HP <=  6) face = 2;
		else if(GmDc.Player.HP <= 10) face = 0;
		else                          face = 1;

		const int ANIM_CYC = 20;
		const int ANIM_STEP = 5;

		if(!animcnt && dRnd() < (slpcnt < 300 ? 0.0025 : 0.01))
			animcnt = bRnd(1, 2) * ANIM_CYC;

		if(!animcnt)
			slpcnt++;
		else
			slpcnt = 0;

		m_countDown(animcnt);

		int animidx = (ANIM_CYC - animcnt % ANIM_CYC) / ANIM_STEP + 1;

		if(2 < animidx)
			animidx = 0;

		SetAlpha(north_a);
		SimpleDrawPic(8, 8, Der(D_FACE_00 + 3 * face + animidx));
		ResetBlend();
	}

	// ==== LIFE ====

	SetAlpha(north_a); // *1

	GTPrintSet(80, 8, 1);
	GTPrint_x(xcout("LIFE %4d ", GmDc.Player.HP));

	for(int c = 0; c < GmDc.Player.HP; c++)
	{
		GTPrint("$");
	}

	// ==== SCORE ====

	GTPrintSet(320, 8, 1);
	GTPrint_x(xcout("SCORE %10I64d", GmDc.Score));

	// ==== MODE ====

	SimpleDrawPic(500, 8, Der(
		GmDc.ExtraMode ?
			D_MODE_EXTRA_00 + (LFrmCnt / 30) % 2 :
			D_MODE_NORMAL
		));
	SimpleDrawPic(564, 8, Der(D_MODE_MODE));

	ResetBlend(); // *1

	// ==== GAUGE ====

	const int GAUGE_X = SCREEN_W - 153 - 10;
	const int GAUGE_Y = SCREEN_H - 16 - 10;

	const int GAUGE_BAR_X = GAUGE_X + 42;
	const int GAUGE_BAR_Y = GAUGE_Y + 3;
	const int GAUGE_BAR_W = 100;
	const int GAUGE_BAR_H = 10;

	int tame = (GmDc.Player.Tame * GAUGE_BAR_W) / TAME_MAX;
	m_range(tame, 0, GAUGE_BAR_W);

	SetAlpha(south_a);
	SimpleDrawPic(GAUGE_BAR_X, GAUGE_BAR_Y, Pic(P_GAUGE_BAR));
	ResetBlend();

	if(GmDc.Player.Tame == TAME_MAX)
	{
		double a = 1.0 - GmDc.Player.TameMaxFlash;

		a *= (sin((LFrmCnt / 10.0) * (PI * 2.0)) + 1.0) / 2.0;
		a = 1.0 - a;

		SetAlpha(a * south_a);
		DrawPicRect(
			GAUGE_BAR_X,
			GAUGE_BAR_Y,
			GAUGE_BAR_W,
			GAUGE_BAR_H,
			Pic(P_WHITEBOX)
			);
		ResetBlend();

		m_countApprox(GmDc.Player.TameMaxFlash, 0.0, 0.75, 0.01);
	}
	if(0.0 < GmDc.Player.TameSemiFlash)
	{
		SetBlendAdd(GmDc.Player.TameSemiFlash * south_a);
		SimpleDrawPic(GAUGE_BAR_X, GAUGE_BAR_Y, Pic(P_GAUGE_BAR));
		ResetBlend();

		m_countApprox(GmDc.Player.TameSemiFlash, 0.0, 0.85, 0.01);
	}

	if(tame < GAUGE_BAR_W)
	{
		SetBright(0, 0, 0);
		DrawPicRect(
			GAUGE_BAR_X + tame,
			GAUGE_BAR_Y,
			GAUGE_BAR_W - tame,
			GAUGE_BAR_H,
			Pic(P_WHITEBOX)
			);
		ResetBright();
	}
	SetAlpha(south_a);
	SimpleDrawPic(GAUGE_X, GAUGE_Y, Pic(P_GAUGE_FRAME));
	ResetBlend();

	// ==== WEAPON ====

	{
		static double currWeaDiffRate; // 正位置からどれだけズレているか。

		if(GmDc.Player.LastWeaponRotDir)
			currWeaDiffRate -= (double)GmDc.Player.LastWeaponRotDir;

		for(int weaIndex = 0; weaIndex < WEAPON_MAX; weaIndex++)
		{
			double weaIRate = weaIndex - currWeaDiffRate - GmDc.Player.CurrWeapon;

			while(weaIRate < -2.0) weaIRate += (double)WEAPON_MAX;
			while(weaIRate >  2.0) weaIRate -= (double)WEAPON_MAX;

			if(abs(weaIRate) < 1.5)
			{
				double x = cos(weaIRate * 0.5 * PI);
				double y = sin(weaIRate * 0.5 * PI);

				const double DISP_X = 0.0;
				const double DISP_Y = 450.0;
				const double DISP_R = 30.0;

				double z = 1.0 - abs(weaIRate);
				m_range(z, 0.0, 1.0);
				z *= 0.5;
				z += 1.0;

				DrawBegin(x * 60.0, 450.0 + y * 30.0, Pic(P_WEAPON_00 + weaIndex));
				DrawZoom(z);
				SetAlpha(south_a);
				DrawEnd();
				ResetBlend();
			}
		}
		m_countApprox(currWeaDiffRate, 0.0, 0.9, 0.0);
	}
}
