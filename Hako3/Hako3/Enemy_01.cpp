#include "Stdinc.h"

// ---- Wall ----

ED_Wall_t *CreateED_Wall(int picIndex, int picXPos, int picYPos)
{
	ED_Wall_t *i = nb(ED_Wall_t);

	/*
		îwåiÇÕãCïtÇ´Ç…Ç≠Ç¢ÇÃÇ≈ÉGÉâÅ[àµÇ¢ÅB
	*/
	errorCase(picIndex < 0 || KABE_NUM <= picIndex);
	errorCase(picXPos < 0 || KABE_W < picXPos);
	errorCase(picYPos < 0 || KABE_H < picYPos);

	i->PicIndex = picIndex;
	i->PicXPos = picXPos;
	i->PicYPos = picYPos;

	return i;
}
ED_Wall_t *CreateED_Wall(autoList<char *> *lines)
{
	return CreateED_Wall(
		PL_ReadInt(lines, 0, -1),
		PL_ReadInt(lines, 1, -1),
		PL_ReadInt(lines, 2, -1)
		);
}
void ReleaseED_Wall(ED_Wall_t *i)
{
	memFree(i);
}
int EProc_Wall(Enemy_t *i, ED_Wall_t *ed)
{
	i->X -= GmDc.ScrollSpeed;

	PutEnemyCrashArea(
		i,
		GetWallSilhouette(ed->PicIndex, ed->PicXPos, ed->PicYPos),
		i->X,
		i->Y,
		0.0,
		1.0
		);

	return 1;
}
void EDraw_Wall(Enemy_t *i, ED_Wall_t *ed)
{
	if(!GmDc.WallBaseOk)
	{
		GmDc.WallBaseOk = 1;
		GmDc.WallBaseX = m_d2i(i->X);
	}
	double xd = (i->X - GmDc.WallBaseX) / 16.0;
	int xdi = m_d2i_s(xd);
	int xPos = GmDc.WallBaseX + xdi * 16;

	DrawPic(xPos, (int)i->Y, Der(
		D_KABE_00_00 +
		ed->PicIndex * KABE_W * KABE_H +
		ed->PicYPos * KABE_W +
		ed->PicXPos
		));

#if 0 // test
	if(GetWallSilhouette(ed->PicIndex, ed->PicXPos, ed->PicYPos)->IsNoTrans() == 2)
	{
		SetBright(255, 255, 0);
		DrawBegin(i->X, i->Y, Pic(P_WHITECIRCLE));
		DrawZoom(0.1);
		DrawEnd();
		ResetBright();
	}
#endif
}

// ---- Fei ----

ED_Fei_t *CreateED_Fei(double speed, double rot, double rotSpeed, double rotZoom, int shotfrm)
{
	ED_Fei_t *i = nb(ED_Fei_t);

	m_range(speed, 1.0 / 60, 1000.0);
	m_range(rot, -1000.0, 1000.0);
	m_range(rotSpeed, -1000.0, 1000.0);
	m_range(rotZoom, 0.0, 1000.0);
	m_range(shotfrm, 0, 1000);

	i->Speed = speed;
	i->Rot = rot;
	i->RotSpeed = rotSpeed;
	i->RotZoom = rotZoom;
	i->ShotFrame = shotfrm;

	return i;
}
ED_Fei_t *CreateED_Fei(autoList<char *> *lines)
{
	return CreateED_Fei(
		PL_ReadDouble(lines, 0, 1.75),
		PL_ReadDouble(lines, 1, 0.0),
		PL_ReadDouble(lines, 2, 0.05),
		PL_ReadDouble(lines, 3, 40.0),
		PL_ReadInt(lines, 4, 0)
		);
}
void ReleaseED_Fei(ED_Fei_t *i)
{
	memFree(i);
}
int EProc_Fei(Enemy_t *i, ED_Fei_t *ed)
{
	if(!i->Frame) // ? èââÒ
	{
		ed->TrueY = i->Y;
	}
	i->X -= ed->Speed;
	i->Y = ed->TrueY + sin(ed->Rot) * ed->RotZoom;
	ed->Rot += ed->RotSpeed;

	if(ed->ShotFrame && ed->ShotFrame == i->Frame)
	{
		ShotEnemy_XYS(i->X, i->Y, GmDc.Player.X - i->X, GmDc.Player.Y - i->Y, 3.0);
	}
	PutEnemyPicInfo(i, P_FEI_00 + (LFrmCnt / 4) % 4, i->X, i->Y);
	PutEnemyCrashAreaByPI(i);

	return ProcPShotEnemyCrashByPI(i);
}
void EDraw_Fei(Enemy_t *i, ED_Fei_t *ed)
{
	DrawEnemyByPI(i);
}

// ---- EShot ----

ED_EShot_t *CreateED_EShot(double xSpeed, double ySpeed, int sm, int colorIdx)
{
	ED_EShot_t *i = nb(ED_EShot_t);

	m_range(xSpeed, -1000.0, 1000.0);
	m_range(ySpeed, -1000.0, 1000.0);
	m_range(colorIdx, 0, ESHOT_COLOR_MAX - 1);

	i->XAdd = xSpeed;
	i->YAdd = ySpeed;
	i->SmallMode = sm ? 1 : 0;
	i->ColorIndex = colorIdx;

	return i;
}
ED_EShot_t *CreateED_EShot(autoList<char *> *lines)
{
	return CreateED_EShot(
		PL_ReadDouble(lines, 0, -10.0),
		PL_ReadDouble(lines, 1, 0.0),
		PL_ReadInt(lines, 2, 0),
		PL_ReadInt(lines, 3, 0)
		);
}
void ReleaseED_EShot(ED_EShot_t *i)
{
	memFree(i);
}
int EProc_EShot(Enemy_t *i, ED_EShot_t *ed) // ? i ê∂ë∂
{
	if(!i->Frame) // ? èââÒ
	{
		/*
			âÊñ äOÇ©ÇÁÇÃî≠éÀÇëjé~Ç∑ÇÈÅB
		*/
		if(
			i->X < 0.0 || (double)SCREEN_W < i->X ||
			i->Y < 0.0 || (double)SCREEN_H < i->Y
			)
		{
			return 0;
		}
	}
	if(i->Crashed)
		return 0;

	i->X += ed->XAdd;
	i->Y += ed->YAdd;

	int eSP = ed->ColorIndex;

	eSP *= 2;
	eSP += ed->SmallMode ? 1 : 0;
	eSP *= ESHOT_PIC_MAX;
	eSP += (i->Frame / 3) % ESHOT_PIC_MAX;

	EWC_AddPoint(i, i->X, i->Y);

	PutEnemyPicInfo(i, P_ESHOT_00_R_00 + eSP, i->X, i->Y);
	PutEnemyCrashAreaByPI(i);

	return ProcPShotEnemyCrashByPI(i);
}
void EDraw_EShot(Enemy_t *i, ED_EShot_t *ed)
{
	DrawEnemyByPI(i);
}

// Shot Enemy ...

void ShotEnemy(double x, double y, ED_EShot_t *bind_ed)
{
	AddEnemy(x, y, CreateEnemy(
		EProc_EShot,
		EDraw_EShot,
		ReleaseED_EShot,
		0, CreateEnemyCommonData(),
		bind_ed
		));
}
void ShotEnemy_XY(double x, double y, double xSpeed, double ySpeed, int sm, int colorIdx)
{
	ShotEnemy(x, y, CreateED_EShot(
		xSpeed,
		ySpeed,
		sm,
		colorIdx
		));
}
void ShotEnemy_XYS(double x, double y, double xDir, double yDir, double speed, int sm, int colorIdx)
{
	double xSpeed = xDir;
	double ySpeed = yDir;

	P2Vector(xSpeed, ySpeed, speed);

	ShotEnemy_XY(x, y, xSpeed, ySpeed, sm, colorIdx);
}
void ShotEnemy_SR(double x, double y, double speed, double speedRot, int sm, int colorIdx)
{
	ShotEnemy(x, y, CreateED_EShot(
		cos(speedRot) * speed,
		sin(speedRot) * speed,
		sm,
		colorIdx
		));
}

// ---- Hikaru ----

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
	)
{
	ED_Hikaru_t *i = nb(ED_Hikaru_t);

	m_range(sekkin_frm, 1, 1000);
	m_range(sekkin_rate, 0.0, 1.0);
	m_range(teishi_x, -1000.0, 1000.0);
	m_range(teishi_y, -1000.0, 1000.0);
	m_range(teishi_frm, 1, 1000);
	m_range(ridatsu_xSpeed, -1000.0, 1000.0);
	m_range(ridatsu_ySpeed, -1000.0, 1000.0);
	m_range(ridatsu_xKasokudo, -1000.0, 1000.0);
	m_range(ridatsu_yKasokudo, -1000.0, 1000.0);

	i->SekkinFrame = sekkin_frm;
	i->SekkinRate = sekkin_rate;
	i->TeishiXPos = teishi_x;
	i->TeishiYRelPos = teishi_y;
	i->TeishiFrame = teishi_frm;
	i->RidatsuXAdd = ridatsu_xSpeed;
	i->RidatsuYAdd = ridatsu_ySpeed;
	i->RidatsuXAdd2 = ridatsu_xKasokudo;
	i->RidatsuYAdd2 = ridatsu_yKasokudo;

	return i;
}
ED_Hikaru_t *CreateED_Hikaru(autoList<char *> *lines)
{
	return CreateED_Hikaru(
		PL_ReadInt(lines, 0, 60),
		PL_ReadDouble(lines, 1, 0.93),
		PL_ReadDouble(lines, 2, 400.0),
		PL_ReadDouble(lines, 3, 0.0),
		PL_ReadInt(lines, 4, 30),
		PL_ReadDouble(lines, 5, 0.0),
		PL_ReadDouble(lines, 6, 0.0),
		PL_ReadDouble(lines, 7, 0.3),
		PL_ReadDouble(lines, 8, 0.0)
		);
}
void ReleaseED_Hikaru(ED_Hikaru_t *i)
{
	memFree(i);
}
int EProc_Hikaru(Enemy_t *i, ED_Hikaru_t *ed)
{
	if(!i->Frame) // ? èââÒ
	{
		ed->TeishiYPos = i->Y + ed->TeishiYRelPos;
	}

	NEL_ifsceneBegin_CM(i->Frame, ed->SekkinFrame) // ê⁄ãﬂíÜ
	{
		m_countApprox(i->X, ed->TeishiXPos, ed->SekkinRate, 0.0);
		m_countApprox(i->Y, ed->TeishiYPos, ed->SekkinRate, 0.0);
	}
	NEL_ifscene(ed->TeishiFrame) // í‚é~íÜ
	{
		if(!fs_count) // éÀåÇ
		{
			double r = P2Angle(i->X, i->Y, GmDc.Player.X, GmDc.Player.Y);

			{
				const int C_MAX = 8;

				for(int c = 0; c < C_MAX; c++)
				{
					ShotEnemy_SR(i->X, i->Y, 3.0, r + (c * PI * 2.0) / C_MAX, 0, 3);
				}
			}

			{
				const int C_MAX = 7;

				for(int c = 0; c < C_MAX; c++)
				{
					ShotEnemy_SR(i->X, i->Y, 4.0, r + (c * PI * 2.0) / C_MAX, 0, 4);
				}
			}
		}
	}
	NEL_ifsceneEnd // ó£íEíÜ
	{
		i->X += ed->RidatsuXAdd;
		i->Y += ed->RidatsuYAdd;

		ed->RidatsuXAdd += ed->RidatsuXAdd2;
		ed->RidatsuYAdd += ed->RidatsuYAdd2;
	}

	PutEnemyPicInfo(i, P_HIKARU_00 + (i->Frame / 3) % 4, i->X, i->Y);
	PutEnemyCrashAreaByPI(i);

	return ProcPShotEnemyCrashByPI(i);
}
void EDraw_Hikaru(Enemy_t *i, ED_Hikaru_t *ed)
{
	DrawEnemyByPI(i);
}

// ---- Lina ----

ED_Lina_t *CreateED_Lina(int sakasa_mode, int shot_cycle)
{
	ED_Lina_t *i = nb(ED_Lina_t);

	m_range(shot_cycle, 1, 1000);

	i->SakasaMode = sakasa_mode;
	i->ShotCycle = shot_cycle;

	return i;
}
ED_Lina_t *CreateED_Lina(autoList<char *> *lines)
{
	return CreateED_Lina(
		PL_ReadInt(lines, 0, 0),
		PL_ReadInt(lines, 1, 120)
		);
}
void ReleaseED_Lina(ED_Lina_t *i)
{
	memFree(i);
}
int EProc_Lina(Enemy_t *i, ED_Lina_t *ed)
{
	int ushiro = i->X < GmDc.Player.X ? 1 : 0;
	int pRN;
	double pRot;

	i->X -= GmDc.ScrollSpeed;

	if(ed->SakasaMode)
	{
		if(ushiro)
		{
			pRN = P_LINA_00;
			pRot = PI;
		}
		else
		{
			pRN = P_LINA_SAKASA_00;
			pRot = 0.0;
		}
	}
	else
	{
		if(ushiro)
		{
			pRN = P_LINA_SAKASA_00;
			pRot = PI;
		}
		else
		{
			pRN = P_LINA_00;
			pRot = 0.0;
		}
	}

	if(i->Frame % ed->ShotCycle == 0)
	{
		double r = P2Angle(i->X, i->Y, GmDc.Player.X, GmDc.Player.Y);

		for(int c = -1; c <= 1; c++)
		{
			ShotEnemy_SR(i->X, i->Y, 3.0, r + (c * 0.3));
		}
	}

	PutEnemyPicInfo(i, pRN + (i->Frame / 3) % 4, i->X, i->Y, pRot);
	PutEnemyCrashAreaByPI(i);

	return ProcPShotEnemyCrashByPI(i);
}
void EDraw_Lina(Enemy_t *i, ED_Lina_t *ed)
{
	DrawEnemyByPI(i);
}

ED_Ningyo_t *CreateED_Ningyo(int jump_mode, int jump_frm)
{
	ED_Ningyo_t *i = nb(ED_Ningyo_t);

	m_range(jump_frm, 0, 1000);

	i->JumpMode = jump_mode;
	i->JumpFrame = jump_frm;

	return i;
}
ED_Ningyo_t *CreateED_Ningyo(autoList<char *> *lines)
{
	return CreateED_Ningyo(
		PL_ReadInt(lines, 0, 1),
		PL_ReadInt(lines, 1, 120)
		);
}
void ReleaseED_Ningyo(ED_Ningyo_t *i)
{
	memFree(i);
}
int EProc_Ningyo(Enemy_t *i, ED_Ningyo_t *ed)
{
	if(!i->Frame) // ? èââÒ
	{
		ed->ChakuchiYPos = i->Y;
		ed->ChakuchiOk = 1;

		if(ed->JumpMode)
		{
			i->Y += 500;
			ed->ChakuchiOk = 0;
		}
	}

	i->X -= GmDc.ScrollSpeed;

	const int jumpFrmMax = 70;
	int jumpRemFrm = 0; // 0 - jumpFrmMax

	if(ed->JumpFrame <= i->Frame)
	{
		m_countApprox(i->Y, ed->ChakuchiYPos, 0.93, 0.0);

		if(ed->JumpMode)
		{
			// i->Frame: ed->JumpFrame ...

			jumpRemFrm = i->Frame - ed->JumpFrame;

			if(jumpRemFrm < jumpFrmMax)
				jumpRemFrm = jumpFrmMax - jumpRemFrm; // 1 ... jumpFrmMax
			else
				jumpRemFrm = 0;

			// jumpRemFrm: 0 ... jumpFrmMax

			if(!jumpRemFrm)
				ed->ChakuchiOk = 1;
		}
	}
	int pRN;

	if(jumpRemFrm)
	{
		int koma = (jumpRemFrm - 1) / 5 + 1;

		if(koma <= 8)
			koma = 8 - koma;
		else
			koma %= 2;

		pRN = P_NINGYO_JUMP_00 + koma;
	}
	else
	{
		pRN = P_NINGYO_00 + (LFrmCnt / 7) % 4;

		if(ed->AttackFrame)
		{
			int afrm = ed->AttackFrame - 1;

			afrm /= 7;

			if(afrm < 4)
			{
				pRN = P_NINGYO_ATTACK_00 + afrm;

				if(ed->AttackFrame == 22 && ed->ChakuchiOk) // shot
				{
					const double shot_x = i->X - 23.0;
					const double shot_y = i->Y - 23.0;

					double r = P2Angle(shot_x, shot_y, GmDc.Player.X, GmDc.Player.Y);

					for(int c = -1; c <= 1; c++)
					{
						ShotEnemy_SR(shot_x, shot_y, 4.0, r + (c * 0.1));
					}
				}
				ed->AttackFrame++;
			}
			else
			{
				ed->AttackFrame = 0;
				ed->AttackSleepFrame = 120;
			}
		}
		else
		{
			m_countDown(ed->AttackSleepFrame);

			if(!ed->AttackSleepFrame)
				ed->AttackFrame = 1;
		}
	}

	PutEnemyPicInfo(i, pRN, i->X, i->Y);
	PutEnemyCrashAreaByPI(i);

	return ProcPShotEnemyCrashByPI(i);
}
void EDraw_Ningyo(Enemy_t *i, ED_Ningyo_t *ed)
{
	DrawEnemyByPI(i);
}

ED_NingyoDead_t *CreateED_NingyoDead(void)
{
	return nb(ED_NingyoDead_t);
}
void ReleaseED_NingyoDead(ED_NingyoDead_t *i)
{
	memFree(i);
}
int EProc_NingyoDead(Enemy_t *i, ED_NingyoDead_t *ed)
{
	ed->YAdd += 0.1;
	i->Y += ed->YAdd;

	int koma = i->Frame;

	koma /= 7;

	if(6 <= koma)
		koma = 4 + koma % 2;

	PutEnemyPicInfo(i, P_NINGYO_DEAD_00 + koma, i->X, i->Y);
//	PutEnemyCrashAreaByPI(i);

	return ProcPShotEnemyCrashByPI(i);
}
void EDraw_NingyoDead(Enemy_t *i, ED_NingyoDead_t *ed)
{
	DrawEnemyByPI(i);
}
