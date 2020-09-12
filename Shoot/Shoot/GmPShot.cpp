#include "Stdinc.h"

PShot_t *CreatePShot(PShTyp_t pShTyp, double x, double y, double r)
{
	PShot_t *i = nb_(PShot_t);

	i->PShTyp = pShTyp;
	i->X = x;
	i->Y = y;
	i->R = r;

	return i;
}
void ReleasePShot(PShot_t *i)
{
	if(GmDc.CurrRockHammer == i)
		GmDc.CurrRockHammer = NULL;

	if(GmDc.CurrSlowBarrier == i)
		GmDc.CurrSlowBarrier = NULL;

	if(GmDc.CurrBlade == i)
		GmDc.CurrBlade = NULL;

	memFree(i);
}

static void PutWallCrash(PShot_t *ps, double cx, double cy, double r, int p_max, double sideSpan, double sidePMax)
{
	for(int c = 0; c <= p_max; c++)
	{
		double rot = (PI * c) / p_max;
		double x = sin(rot) * r;
		double y = cos(rot) * r;

		PutPShotWallCrash(ps, ps->X + x, ps->Y + y);
	}
	for(int c = 1; c <= sidePMax; c++)
	{
		double x = (sideSpan * c) / sidePMax;

		PutPShotWallCrash(ps, ps->X - x, ps->Y - r);
		PutPShotWallCrash(ps, ps->X - x, ps->Y + r);
	}
}
static int ProcPShot(PShot_t *ps)
{
	if(ps->PShTyp == PST_SLOW) // Slow death
	{
#define SLOW_DEATH_TARGET_R 10.0
#define SLOW_DEATH_R 20.0
		if(
			ps->u.Slow.TargetR <= SLOW_DEATH_TARGET_R && 
			ps->u.Slow.R <= SLOW_DEATH_R
			)
		{
			ps->Death = 1;
		}
	}

	if(ps->Crashed)
	{
		// 0.0 as alive
		double z = 0.0;
		double zRock = 0.0;

		switch(ps->PShTyp)
		{
		case PST_NORMAL:
			z = 1.0;
			break;
		case PST_LV1:
			z = 1.5;
			break;
		case PST_LV2:
			z = 1.75;
			break;
		case PST_LV3:
			z = 2.0;
			break;
		case PST_MIRACLE_MINI:
			z = 2.25;
			break;

		case PST_ROCK:
		case PST_ROCK_HAMMER:
			zRock = ps->u.Rock.Hankei / 32.0; // P_BOMB_00 ‚Í 128 x 128
			break;

		case PST_SLOW_SHOT:
			z = 1.0;
			break;
		case PST_SLOW:
			ps->u.Slow.TargetR = SLOW_DEATH_TARGET_R;
			break;
		case PST_BLADE_SHOT:
			z = 1.5;
			break;
		case PST_BLADE:
			ps->Death = 1; // HACK
			break;
		case PST_DBL_SPREAD:
			z = 1.0; // dummy
			break;
		case PST_DBL_BOUNCE:
			z = 1.0; // dummy
			break;

		default:
			break;
		}
		if(0.0 < z)
		{
			GTACE_BlendAddMode = 1;
			GTACE_PicResnoIncDelay = 1;
			GTACE_PicResnoEnd = P_NEWSHOT_DEATH_00 + 8;
			GTAddCommonEffect_ZR(
				GmDc.EffectList,
				P_NEWSHOT_DEATH_00,
				1,
				0,
				ps->X, ps->Y, z
				);
			GTACE_Reset();

			ps->Death = 1;
		}
		if(0.0 < zRock) // ROCK_CRASH
		{
			GTACE_BlendAddMode = 1;
			GTACE_PicResnoIncDelay = 2;
			GTACE_PicResnoEnd = P_BOMB_00 + 8;
			GTAddCommonEffect_ZR(
				GmDc.EffectList,
				P_BOMB_00,
				1,
				0,
				ps->X, ps->Y, zRock
				);
			GTACE_Reset();

			ps->Death = 1;
		}
	}
	if(ps->Death)
	{
		return 0;
	}
	int death = 0;
	int screenOutAlive = 0;

	switch(ps->PShTyp)
	{
	case PST_NORMAL:
		{
			ps->X += 13.0;
			death = 20 <= ps->Frame;

			for(int c = 0; c < 2; c++)
			{
				PutPShotCrashCircle(ps, ps->X - c * 6.5, ps->Y, 9.0); // (16 / 2) -> 8
			}
			PutPShotWallCrash(ps, ps->X - 8.0, ps->Y);
//			PutWallCrash(ps, ps->X, ps->Y, 8.0, 3, 13.0, 3); // old
			PutPShotWallCrash(ps, ps->X, ps->Y);
		}
		break;

	case PST_LV1:
		ps->X += 15.0;
		PutPShotCrashCircle(ps, ps->X, ps->Y, 17.0); // (32 / 2) -> 16
		PutWallCrash(ps, ps->X, ps->Y, 16.0, 5, 15.0, 5);
		break;

	case PST_LV2:
		ps->X += 15.0;
		PutPShotCrashCircle(ps, ps->X, ps->Y, 17.0); // (32 / 2) -> 16
		PutWallCrash(ps, ps->X, ps->Y, 16.0, 5, 15.0, 5);
		break;

	case PST_LV3:
		ps->X += 15.0;
		PutPShotCrashCircle(ps, ps->X, ps->Y, 33.0); // (64 / 2) -> 32
		PutWallCrash(ps, ps->X, ps->Y, 32.0, 7, 15.0, 5);
		break;

	case PST_MIRACLE:
		{
			if(ps->Frame == 0)
			{
				ps->u.Miracle.Speed = 13.0;
			}

			if(ps->Crashed)
			{
				if(ps->Crashed == 2) // ? by wall
				{
					ps->X -= GmDc.ScrollSpeed;
				}
			}
			else
			{
				ps->X += ps->u.Miracle.Speed;
				m_minim(ps->X, (double)SCREEN_W);
				m_countApprox(ps->u.Miracle.Speed, 0.0, 0.95, 0.0);
			}

			PutPShotCrashCircle(ps, ps->X, ps->Y, 33.0); // (64 / 2) -> 32
			PutWallCrash(ps, ps->X, ps->Y, 32.0, 9, 0.0, 0);

#define MIRACLE_HAJIKE_FRAME 50 // == ps->Frame ‚Ì‚Æ‚«Proc‚É‚Ä’e‚¯‚éB

			if(ps->Frame < MIRACLE_HAJIKE_FRAME)
			{
				// noop
			}
			else // ? ‚Í‚¶‚¯‚é
			{
				const int DIV_NUM = 24;

				for(int c = 0; c < DIV_NUM; c++)
				{
					/*
						¡ƒtƒŒ[ƒ€‚ÅA‰‰ñProc‚³‚ê‚é‚±‚Æ‚É’ˆÓ
					*/
					GmDc.PShotList->AddElement(CreatePShot(
						PST_MIRACLE_MINI,
						ps->X,
						ps->Y,
						(c * PI * 2.0) / DIV_NUM
						));
				}
				death = 1;
			}
		}
		break;

	case PST_MIRACLE_MINI:
		{
			const double SPEED = 13.0;

			ps->X += cos(ps->R) * SPEED;
			ps->Y += sin(ps->R) * SPEED;

			PutPShotCrashCircle(ps, ps->X, ps->Y, 9.0); // (16 / 2) -> 8
			PutPShotWallCrash(ps, ps->X, ps->Y);
		}
		break;

	case PST_LASER:
		{
			if(ps->Frame == 0) // ? ‰‰ñ
			{
				ps->u.Laser.ShotX = ps->X;
				ps->u.Laser.ShotY = ps->Y;
				ps->u.Laser.TailX = ps->X;
				ps->u.Laser.TailY = ps->Y;
			}
			const double SPEED = 30.0;

			ps->X += SPEED;

#define LASER_HANKEI 4.0
			double laser_hankei = LASER_HANKEI * ps->u.Laser.HankeiRate;

			if(ps->u.Laser.ShotEndFrame < ps->Frame)
				ps->u.Laser.TailX += SPEED;

			m_minim(ps->X, (double)SCREEN_W);
			m_maxim(ps->X, ps->u.Laser.TailX + 0.1); // + margin

			PutPShotCrashRect(
				ps,
				ps->u.Laser.TailX,
				ps->u.Laser.TailY - laser_hankei,
				ps->X - ps->u.Laser.TailX,
				laser_hankei * 2.0
				);
		}
		break;

	case PST_LASER_CUTTER:
		{
			ps->X += 13.0;

			PutPShotCrashRect(
				ps,
				ps->X - 16.0,
				ps->Y - 8.0,
				32.0,
				16.0
				);
		}
		break;

	case PST_ROCK:
		{
			// ‘¬“x§ŒÀ {
			errorCase(ps->u.Rock.Hankei <= 0.0); // 2bs

			m_range(ps->u.Rock.XAdd, -ps->u.Rock.Hankei, ps->u.Rock.Hankei);
			m_range(ps->u.Rock.YAdd, -ps->u.Rock.Hankei, ps->u.Rock.Hankei);
			// }

			ps->X += ps->u.Rock.XAdd;
			ps->Y += ps->u.Rock.YAdd;

			// ‹ó‹C‚Ì’ïR {
			ps->u.Rock.XAdd *= 0.98;
			ps->u.Rock.YAdd *= 0.98;
			// }

			ps->u.Rock.YAdd += 0.2; // G
			ps->u.Rock.Rot += ps->u.Rock.RotAdd;

			PutPShotCrashCircle(ps, ps->X, ps->Y, ps->u.Rock.Hankei);
			PutPShotWallCrash(ps, ps->X - ps->u.Rock.Hankei, ps->Y);
			PutPShotWallCrash(ps, ps->X + ps->u.Rock.Hankei, ps->Y);
			PutPShotWallCrash(ps, ps->X, ps->Y - ps->u.Rock.Hankei);
			PutPShotWallCrash(ps, ps->X, ps->Y + ps->u.Rock.Hankei);
		}
		break;

	case PST_ROCK_HAMMER:
		{
			// ƒoƒl‚Ì‰Á‘¬“x {
			double xadd2 = (GmDc.Player.X - ps->X) * 0.015;
			double yadd2 = (GmDc.Player.Y - ps->Y) * 0.015;
			// }

			yadd2 += 1.5; // G

			ps->u.Rock.XAdd += xadd2;
			ps->u.Rock.YAdd += yadd2;

			double lx = ps->X;
			double ly = ps->Y;

			ps->X += ps->u.Rock.XAdd;
			ps->Y += ps->u.Rock.YAdd;

			double nx = ps->X;
			double ny = ps->Y;

			{
				int C_MAX;

				switch(ps->Level)
				{
				case 0: C_MAX = 4; break;
				case 1: C_MAX = 3; break;
				case 2: C_MAX = 2; break;

				default:
					error();
				}

				for(int c = 0; c < C_MAX; c++)
				{
					double cx = lx + ((nx - lx) * c) / C_MAX;
					double cy = ly + ((ny - ly) * c) / C_MAX;

					GTACE_BlendAddMode = 1;
					GTAddCommonEffect_ZR(
						GmDc.EffectList_BS,
						P_ROCK_HAMMER_TAILBALL,
						0,
						0,
						cx, cy, ps->u.Rock.Hankei / 24.0, 0.0, 0.1,
						0.0, 0.0, 0.0, 0.0, -0.005
						);
					GTACE_BlendAddMode = 0;
				}
			}

			// ‹ó‹C‚Ì’ïR {
			ps->u.Rock.XAdd *= 0.95;
			ps->u.Rock.YAdd *= 0.95;
			// }

			ps->u.Rock.Rot += ps->u.Rock.RotAdd;
			ps->u.Rock.RotAdd += abs(ps->u.Rock.XAdd) * 0.001;
			ps->u.Rock.RotAdd -= abs(ps->u.Rock.YAdd) * 0.001;

			if(0.01 < abs(ps->u.Rock.RotAdd))
				ps->u.Rock.RotAdd *= 0.97;
			else
				ps->u.Rock.RotAdd *= 0.999;

			PutPShotCrashCircle(ps, ps->X, ps->Y, ps->u.Rock.Hankei);

			screenOutAlive = 1;
		}
		break;

	case PST_SLOW_SHOT:
		{
			ps->X += ps->u.Slow.Speed;
			m_countApprox(ps->u.Slow.Speed, ps->u.Slow.TargetSpeed, 0.95, 0.0);

			switch(ps->Level)
			{
			case 0:
				PutPShotCrashCircle(ps, ps->X, ps->Y, 6.5);
				PutPShotWallCrash(ps, ps->X, ps->Y);
				break;
			case 1:
				PutPShotCrashCircle(ps, ps->X, ps->Y, 13.0);
				PutWallCrash(ps, ps->X, ps->Y, 14.0, 3, 0.0, 0);
				break;

			default:
				error();
			}
		}
		break;

	case PST_SLOW:
		{
			m_countApprox(ps->u.Slow.R, ps->u.Slow.TargetR, 0.9, 0.0);
			ps->u.Slow.Rot += ps->u.Slow.RotAdd;

			AddTask(GmDc.EffectList, DrawSlowBarrier_Cover, ps);
		}
		break;

	case PST_BLADE_SHOT:
		{
			double speed;

			switch(ps->Level)
			{
			case 0:
				death = 15 <= ps->Frame;
				speed = 13.0;
				break;
			case 1:
				speed = 17.0;
				break;

			default:
				error();
			}
			ps->X += cos(ps->R) * speed;
			ps->Y += sin(ps->R) * speed;

			PutPShotCrashCircle(ps, ps->X, ps->Y, 10.0);
			PutPShotWallCrash(ps, ps->X, ps->Y);
		}
		break;

	case PST_BLADE:
		{
			GmDc.Player.LastMoveX;
		}
		break;

	case PST_DBL_SPREAD:
		{
			double speed;
			double cr;

			switch(ps->Level)
			{
			case 0:
				speed = 8.0;
				cr = 9.0;
				break;
			case 1:
				speed = 13.0;
				cr = 14.0;
				break;

			default:
				error();
			}

			ps->X += cos(ps->R) * speed;
			ps->Y += sin(ps->R) * speed;

			PutPShotCrashCircle(ps, ps->X, ps->Y, cr);
			PutPShotWallCrash(ps, ps->X, ps->Y);
		}
		break;

	case PST_DBL_BOUNCE:
		{
			double h = ps->u.Double.Hankei;
			double speed = h * 0.4;

			ps->X += cos(ps->R) * speed;
			ps->Y += sin(ps->R) * speed;

			PutPShotCrashCircle(ps, ps->X, ps->Y, h);
			PutPShotWallCrash(ps, ps->X - h, ps->Y);
			PutPShotWallCrash(ps, ps->X + h, ps->Y);
			PutPShotWallCrash(ps, ps->X, ps->Y - h);
			PutPShotWallCrash(ps, ps->X, ps->Y + h);
		}
		break;

	default:
		error();
	}
	if(!death && !screenOutAlive)
	{
		const int MARGIN = 10;

		if(
			ps->X < -MARGIN || SCREEN_W + MARGIN < ps->X ||
			ps->Y < -MARGIN || SCREEN_H + MARGIN < ps->Y
			)
		{
			death = 1;
		}
	}
	ps->Death = death;
	ps->Frame++;

	// reset {
	ps->Crashed = 0;
	// }

	return 1;
}
void GmProcPShot(void)
{
	for(int index = 0; index < GmDc.PShotList->GetCount(); index++)
	{
		PShot_t *ps = GmDc.PShotList->GetElement(index);

		if(!ProcPShot(ps)) // ? ŽE‚é
		{
			ReleasePShot(ps);
			GmDc.PShotList->FastDesertElement(index);
			index--;
		}
	}
}
static void DrawPShot(PShot_t *ps)
{
	switch(ps->PShTyp)
	{
	case PST_NORMAL:
		DrawPic(ps->X, ps->Y, Pic((D_PSHOT_NORMAL_00 + (ps->Frame / 3) % 4) | DTP));
		break;

	case PST_LV1:
		SetPictureGroup(S_HSTEffectPicGrp());
		//SetBlendAdd(1.0);
		DrawBegin(ps->X - 16.0, ps->Y, Pic(P_NEWSHOT_00 + ps->Frame % 13)); // ’¼Œa 32 px
		DrawZoom(0.5);
		DrawEnd();
		//ResetBlend();
		SetPictureGroup(NULL);
		break;

	case PST_LV2:
		SetPictureGroup(S_HSTEffectPicGrp());
		//SetBlendAdd(1.0);
		DrawBegin(ps->X - 24.0, ps->Y, Pic(P_NEWSHOT_00 + ps->Frame % 13)); // ’¼Œa 48 px
		DrawZoom(0.75);
		DrawEnd();
		//ResetBlend();
		SetPictureGroup(NULL);
		break;

	case PST_LV3:
		SetPictureGroup(S_HSTEffectPicGrp());
		//SetBlendAdd(1.0);
		DrawBegin(ps->X - 32.0, ps->Y, Pic(P_NEWSHOT_00 + ps->Frame % 13)); // ’¼Œa 64 px
		//DrawZoom(1.0);
		DrawEnd();
		//ResetBlend();
		SetPictureGroup(NULL);
		break;

	case PST_MIRACLE:
		{
			SetPictureGroup(S_HSTEffectPicGrp());
			//SetBlendAdd(1.0);
			DrawBegin(ps->X, ps->Y, Pic(P_NEWMIRACLE));
			DrawZoom(1.185); // -> ’¼Œa 64 px
			DrawRotate(ps->Frame / 5.0);
			DrawEnd();
			//ResetBlend();
			SetPictureGroup(NULL);

			double frmRate = (double)ps->Frame / MIRACLE_HAJIKE_FRAME;
			m_range(frmRate, 0.0, 1.0);

			SetBlendAdd(1.0 - frmRate);
			DrawBegin(
				ps->X,
				ps->Y,
				Pic(P_NEWMIRACLE_FIRE_00 + ps->Frame % 11)
				);
			DrawMove(-26.0, -4.0); // •â³
			DrawZoom(2.0);
			DrawEnd();
			ResetBlend();

			GTACE_BlendAddMode = 1;
			GTACE_ReverseX = 1;
			GTAddCommonEffect_ZR(
				GmDc.EffectList,
				P_NEWMIRACLE_JIN,
				0,
				2,
				ps->X, ps->Y, 5.0 - 4.5 * frmRate, 10.0 * m_pow(frmRate), m_pow(frmRate) * 0.75
				);
			GTACE_Reset();
		}
		break;

	case PST_MIRACLE_MINI:
		{
			SetPictureGroup(S_HSTEffectPicGrp());
			//SetBlendAdd(1.0);
			DrawBegin(ps->X, ps->Y, Pic(P_NEWMIRACLE));
			DrawZoom(1.185 / 2.0); // -> ’¼Œa 32 px
			DrawRotate(ps->Frame / 5.0);
			DrawEnd();
			//ResetBlend();
			SetPictureGroup(NULL);

			SetBlendAdd(0.75);
			DrawBegin(
				ps->X,
				ps->Y,
				Pic(P_NEWMIRACLE_FIRE_00 + ps->Frame % 11)
				);
			DrawMove(-26.0, -4.0); // •â³
			DrawRotate(ps->R);
			DrawEnd();
			ResetBlend();
		}
		break;

	case PST_LASER:
		{
			double hankei = 8.0 * ps->u.Laser.HankeiRate; // ‰æ‘œ‚Ì‚‚³ 16px
//			double hankei = LASER_HANKEI * ps->u.Laser.HankeiRate; // old

			SetBlendAdd(0.6);
			DrawPicFree(
				ps->u.Laser.TailX, ps->u.Laser.TailY - hankei,
				ps->X, ps->Y - hankei,
				ps->X, ps->Y + hankei,
				ps->u.Laser.TailX, ps->u.Laser.TailY + hankei,
				Pic(D_LASER | DTP)
				);
			ResetBlend();

			{
				DPOE_t *i = CreateDPOE();

				i->PicResno = D_LASER | DTP;
				i->BlendAddMode = 1;
				i->A = 0.4;
				i->Type = DPOE_FREE;

				i->u.Free.LTX = ps->u.Laser.TailX;
				i->u.Free.LTY = ps->u.Laser.TailY - hankei;
				i->u.Free.RTX = ps->X;
				i->u.Free.RTY = ps->Y - hankei;
				i->u.Free.RBX = ps->X;
				i->u.Free.RBY = ps->Y + hankei;
				i->u.Free.LBX = ps->u.Laser.TailX;
				i->u.Free.LBY = ps->u.Laser.TailY + hankei;

				AddDPOE(GmDc.EffectList, i);
			}

			if(ps->Frame <= ps->u.Laser.ShotEndFrame)
			{
				double z = (ps->u.Laser.ShotEndFrame - ps->Frame) / (double)ps->u.Laser.ShotEndFrame;

				z = 0.3 + 0.2 * z;
				z *= ps->u.Laser.HankeiRate;

				SetBlendAdd(1.0);
				DrawBegin(ps->u.Laser.ShotX, ps->u.Laser.ShotY, Pic(P_LASER_SHOT));
				DrawZoom(z);
				DrawEnd();
				ResetBlend();

#if 0 // ‚ ‚Ü‚èãY—í‚¶‚á‚È‚¢
				/*
					‚·‚Å‚É EffectList_BS ‚Í•`‰æÏ‚Ý‚È‚Ì‚ÅA¡ƒtƒŒ[ƒ€‚Å“ñd‚É•`‰æ‚³‚ê‚é‚±‚Æ‚Í‚È‚¢B
				*/
				if(ps->Frame == ps->u.Laser.ShotEndFrame)
				{
					GTACE_BlendAddMode = 1;
					GTAddCommonEffect_ZR(
						GmDc.EffectList_BS,
						P_LASER_SHOT,
						0,
						0,
						ps->u.Laser.ShotX, ps->u.Laser.ShotY, 0.2 * ps->u.Laser.HankeiRate, 0.0, 1.0,
						0.0, 0.0, 0.0, 0.0, -0.1
						);
					GTACE_Reset();
				}
#endif
			}
		}
		break;

	case PST_LASER_CUTTER:
		{
			SetBlendAdd(0.7);
			DrawPic(ps->X, ps->Y, Pic(P_LASER_CUTTER));
			ResetBlend();

			{
				DPOE_t *i = CreateDPOE();

				i->PicResno = P_LASER_CUTTER;
				i->BlendAddMode = 1;
				i->A = 0.3;
				i->Type = DPOE_CENTER;

				i->u.Center.X = ps->X;
				i->u.Center.Y = ps->Y;

				AddDPOE(GmDc.EffectList, i);
			}
		}
		break;

	case PST_ROCK:
		{
			/*
				P_ROCK ... ‰æ‘œƒTƒCƒY 64 x 64, Šâ‚ÌƒTƒCƒY 50 x 50 ‚­‚ç‚¢
			*/
			DrawBegin(ps->X, ps->Y, Pic(P_ROCK));
			DrawRotate(ps->u.Rock.Rot);
			DrawZoom(ps->u.Rock.Hankei / 25.0);
			DrawEnd();
		}
		break;

	case PST_ROCK_HAMMER:
		{
			double vx = ps->X - GmDc.Player.X;
			double vy = ps->Y - GmDc.Player.Y;

			P2Vector(vx, vy, 4.0);
			Rot90HT(vx, vy);

			double x1 = GmDc.Player.X - vx;
			double y1 = GmDc.Player.Y - vy;
			double x2 = GmDc.Player.X + vx;
			double y2 = GmDc.Player.Y + vy;
			double x3 = ps->X + vx;
			double y3 = ps->Y + vy;
			double x4 = ps->X - vx;
			double y4 = ps->Y - vy;

			SetBlendAdd(0.7);
			DrawPicFree(
				x1, y1,
				x2, y2,
				x3, y3,
				x4, y4,
				Pic(P_ROCK_HAMMER_HIMO)
				);
			ResetBlend();

			// 64 x 64 (Šâ: 50 x 50)
			DrawBegin(ps->X, ps->Y, Pic(P_ROCK));
			DrawRotate(ps->u.Rock.Rot);
			DrawZoom(ps->u.Rock.Hankei / 25.0);
			DrawEnd();

			// 256 x 256
			GTACE_BlendAddMode = 1;
			GTAddCommonEffect_ZR(
				GmDc.EffectList,
				P_ROCK_HAMMER_JIN,
				0,
				2,
				ps->X, ps->Y, ps->u.Rock.Hankei / 64.0, ps->u.Rock.Rot / 3.0, 0.3
				);
			GTACE_BlendAddMode = 0;
		}
		break;

	case PST_SLOW_SHOT:
		{
			switch(ps->Level)
			{
			case 0:
				SetPictureGroup(S_HSTEffectPicGrp());
				DrawBegin(ps->X, ps->Y, Pic(P_SLOW_SHOT));
				DrawZoom(0.5);
				DrawEnd();
				SetPictureGroup(NULL);
				break;

			case 1:
				SetPictureGroup(S_HSTEffectPicGrp());
				DrawPic(ps->X, ps->Y, Pic(P_SLOW_SHOT));
				SetPictureGroup(NULL);
				break;

			default:
				error();
			}
		}
		break;

	case PST_SLOW:
		DrawSlowBarrier_Main(ps);
		break;

	case PST_BLADE_SHOT:
		{
			double z;

			switch(ps->Level)
			{
			case 0:
				z = 1.0;
				break;
			case 1:
				z = 2.0;
				break;

			default:
				error();
			}

			SetPictureGroup(S_HSTEffectPicGrp());
			DrawBegin(ps->X, ps->Y, Pic(P_BLADE_SHOT));
			DrawZoom(z);
			DrawRotate(ps->R);
			DrawEnd();
			SetPictureGroup(NULL);
		}
		break;

	case PST_BLADE:
		{
			double r = 40.0 + 64.0 * ps->u.Blade.Scale / 110.0;

			DrawBegin(
				GmDc.Player.X + cos(ps->R) * r,
				GmDc.Player.Y + sin(ps->R) * r,
				Pic(P_BLADE)
				);
			DrawZoom(ps->u.Blade.Scale / 110.0);
			DrawRotate(ps->R);
			DrawEnd();
		}
		break;

	case PST_DBL_SPREAD:
		{
			double z;

			switch(ps->Level)
			{
			case 0:
				z = 0.5;
				break;
			case 1:
				z = 0.75;
				break;

			default:
				error();
			}

			SetPictureGroup(S_HSTEffectPicGrp());
			DrawBegin(ps->X, ps->Y, Pic(P_SPREAD));
			DrawZoom(z);
			DrawRotate(ps->R);
			DrawEnd();
			SetPictureGroup(NULL);
		}
		break;

	case PST_DBL_BOUNCE:
		{
			SetPictureGroup(S_HSTEffectPicGrp());
			DrawBegin(ps->X, ps->Y, Pic(P_BOUNCE + LFrmCnt % 12));
			DrawZoom(ps->u.Double.Hankei / 60.0); // P_BOUNCE -> ’¼Œa 120.0 ‚­‚ç‚¢
			DrawEnd();
			SetPictureGroup(NULL);
		}
		break;

	default:
		error();
	}
}
void GmDrawPShot(void)
{
	for(int index = 0; index < GmDc.PShotList->GetCount(); index++)
	{
		PShot_t *ps = GmDc.PShotList->GetElement(index);

		if(!ps->Frame) // ‰‰ñProc‘O‚É•`‰æ‚³‚¹‚È‚¢B
			continue;

		ps->Frame--; // ProcŽž‚ÌƒtƒŒ[ƒ€‚É‚·‚éB
		DrawPShot(ps);
		ps->Frame++; // –ß‚·B
	}
}

void DestroyCurrRockHammer(void)
{
	if(GmDc.CurrRockHammer)
		GmDc.CurrRockHammer->Crashed = 1;
}
void DestroyCurrSlowBarrier(void)
{
	if(GmDc.CurrSlowBarrier)
		GmDc.CurrSlowBarrier->Crashed = 1;
}
void DestroyCurrBlade(void)
{
	if(GmDc.CurrBlade)
		GmDc.CurrBlade->Crashed = 1;
}
