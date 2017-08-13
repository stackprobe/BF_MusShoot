#include "Stdinc.h"

static void DrawWall(void)
{
	SimpleDrawPic(0, 0, Pic(P_SPACE_WALL));
}
static void DrawDeathCurtain(void)
{
	SetAlpha(GmDc.Death_A);
	SetBright(1.0, 0.0, 0.0);
	DrawPicRect(0, 0, SCREEN_W, SCREEN_H, Pic(P_WHITEBOX));
	ResetBright();
	ResetBlend();
}
static void Pause(void)
{
	GTSetCurtain(-0.5, 30);
	SetDispMouseCursorMode(1);
	GTFreezeInput();

	for(; ; )
	{
		DrawWall();

		clsDx();
		printfDx("ポーズ画面(仮)\n");
		printfDx("\n");
		printfDx("フルスクリーン切り替え %d\n", Sd.FullScreenMode);
		printfDx("\n");
		printfDx("ウィンドウ拡大率 %f\n", Sd.ScreenZoom);
		printfDx("\n");
		printfDx("プレイヤーキャラ移動速度 %f (CTRL=高速)\n", Sd.PlayerMouseMoveRate);
		printfDx("\n");
		printfDx("武器切り替え感度 %d (1=最高感度)\n", Sd.WeaponRotMax);
		printfDx("\n");
		printfDx("戻る\n");
		printfDx("\n");

		UpdateMousePos();

		switch(MouseY / 32)
		{
		case 1:
			if(MouseL == 1)
			{
				GTSetFullScreenMode(Sd.FullScreenMode ? 0 : 1);
			}
			break;

		case 2:
			{
				int v = m_d2i(Sd.ScreenZoom / 0.25);
				v += MouseWheelRot;
				Sd.ScreenZoom = v * 0.25;
				m_range(Sd.ScreenZoom, 1.0, 2.0);

				if(v)
				{
					ApplyWindowSize();
				}
			}
			break;

		case 3:
			{
				double vRate = 0.01;

				if(
					GetKeyPress(KEY_INPUT_LCONTROL) ||
					GetKeyPress(KEY_INPUT_RCONTROL)
					)
					vRate = 0.1;

				int v = m_d2i_s(Sd.PlayerMouseMoveRate / vRate);
				v += MouseWheelRot;
				Sd.PlayerMouseMoveRate = v * vRate;
				m_range(Sd.PlayerMouseMoveRate, -100.0, 100.0);
			}
			break;

		case 4:
			{
				Sd.WeaponRotMax += MouseWheelRot;
				m_range(Sd.WeaponRotMax, 1, 100);
			}
			break;

		case 5:
			if(MouseL == 1)
				goto endLoop;

		default:
			break;
		}
		GTEndFrame();
	}
endLoop:
	clsDx();
}
void GmMain(void)
{
	// ステージ設定デフォルト {

	GmDc.ScrollSpeed = 0.5;

	// }

	// Load _MapData
	{
		char *backMapFile = "WallData.txt";
		char *frontMapFile = "StageData.txt";

		if(!accessible(backMapFile)) // @ "out\\"
		{
			backMapFile = "..\\EditorData\\WallData.txt";
			frontMapFile = "..\\EditorData\\StageData.txt";
		}
		if(!accessible(backMapFile)) // @ "Hako3\\Release\\"
		{
			backMapFile = "..\\..\\EditorData\\WallData.txt";
			frontMapFile = "..\\..\\EditorData\\StageData.txt";
		}
		autoList<uchar> *backMapRes = readBinary(backMapFile);
		autoList<uchar> *frontMapRes = readBinary(frontMapFile);

		// <-- .rclu から読むようになる予定

		textImageReader *backMapReader = new textImageReader(backMapRes);
		textImageReader *frontMapReader = new textImageReader(frontMapRes);

		LoadMapData(GmDc.BackMapData, backMapReader);
		LoadMapData(GmDc.FrontMapData, frontMapReader);

		delete backMapReader;
		delete frontMapReader;
	}
	// Load _MapEnemyData
	{
		LoadMapEnemyData(GmDc.BackMapEnemyData, GmDc.BackMapData);
		LoadMapEnemyData(GmDc.FrontMapEnemyData, GmDc.FrontMapData);
	}
	if(ReqTestPlayStartPos) // 読み飛ばし
	{
		// 逆転
		GmDc.BackMapEnemyData->Reverse();
		GmDc.FrontMapEnemyData->Reverse();

		for(int c = 0; c < ReqTestPlayStartPos; c++)
		{
			for(int d = 0; d < 30; d++)
			{
				Enemy_t *e1 = GmDc.BackMapEnemyData->UnaddElement();
				Enemy_t *e2 = GmDc.FrontMapEnemyData->UnaddElement();

				ReleaseEnemy(e1);
				ReleaseEnemy(e2);
			}
		}

		// 復元
		GmDc.BackMapEnemyData->Reverse();
		GmDc.FrontMapEnemyData->Reverse();
	}

	// ステージ設定補正 {

	m_range(GmDc.ScrollSpeed, 1.0 / 60.0, 16.0);

	// }

	GmDc.Player.HP = PLAYER_HP_DEF;

	SetDispMouseCursorMode(0);
	GTFreezeInput();
	LFrmCnt = 0;

	// ==== ゲームループ開始 ====

	for(; ; )
	{
		UpdateMouseMove();

		if(GTGetInput(INP_PAUSE, INP_DOWN))
		{
			Pause();

			GTSetCurtain(0.0, 30);
			SetDispMouseCursorMode(0);
			GTFreezeInput();
		}


		// test >

		if(GTGetInput(INP_DIR_2, INP_DOWN))
		{
			GmDc.Player.HP--;
			m_maxim(GmDc.Player.HP, 0);
		}
		if(GTGetInput(INP_DIR_8, INP_DOWN))
		{
			GmDc.Player.HP++;
		}
		if(GTGetInput(INP_D, INP_DOWN))
		{
			GmDc.ExtraMode = GmDc.ExtraMode ? 0 : 1;
		}
		if(GTGetInput(INP_E, INP_PRESS))
		{
			GmDc.Score++;
		}
		if(GTGetInput(INP_F, INP_DOWN))
		{
			break;
		}

		// < test


		if(GmDc.Player.CrashFrame == 0) // Script
		{
			if(
				GmDc.NextMapX <= GmDc.Scroll &&
				(
					GmDc.ReadMapIndex < GmDc.BackMapEnemyData->GetCount() ||
					GmDc.ReadMapIndex < GmDc.FrontMapEnemyData->GetCount()
					)
				)
			{
				double xGosa = GmDc.Scroll - GmDc.NextMapX;

				for(int y = 0; y < 30; y++)
				{
					Enemy_t *be = GmDc.BackMapEnemyData->RefElement(GmDc.ReadMapIndex, NULL);
					Enemy_t *fe = GmDc.FrontMapEnemyData->RefElement(GmDc.ReadMapIndex, NULL);

					if(be) GmDc.BackMapEnemyData->SetElement(GmDc.ReadMapIndex, NULL);
					if(fe) GmDc.FrontMapEnemyData->SetElement(GmDc.ReadMapIndex, NULL);

					GmDc.ReadMapIndex++;

					Enemy_t *el[2] = { be, fe };

					for(int ei = 0; ei < 2; ei++)
					{
						Enemy_t *ee = el[ei];

						if(ee)
						{
							ee->X = (double)SCREEN_W + ee->CommonData->HaichiX - xGosa;
							ee->Y = 8.0 + y * 16.0;
							ee->MapXPos = GmDc.ReadMapXPos;
							ee->MapYPos = y;

							GmDc.EnemyList->AddElement(ee);
						}
					}
				}
				GmDc.ReadMapXPos++;
				GmDc.NextMapX += 16.0;
			}
			GmDc.Scroll += GmDc.ScrollSpeed;
		}

		// reset {
		GmDc.WallBaseOk = 0;
		GmDc.WallBaseX = 0; // 2bs

		GmDc.DoDrawPlayerDir = 0;
		GmDc.D_PlayerDir = 0.0; // 2bs
		// }

		if(GmDc.Player.ToujouFrame < PLAYER_TOUJOU_MAX)
		{
			if(GmDc.Player.ToujouFrame == 0) // ? 初回
			{
				GmDc.Player.X = SCREEN_W / 2.0;
				GmDc.Player.Y = SCREEN_H / 2.0;
				GmDc.Player.T_X = -50.0;
				GmDc.Player.T_Y = 50.0;
			}
			double rate = (double)GmDc.Player.ToujouFrame / PLAYER_TOUJOU_MAX;
			rate *= rate;
			rate = 1.0 - rate;
			m_range(rate, 0.0, 1.0);

			m_countApprox(GmDc.Player.T_X, GmDc.Player.X, rate, 0.0);
			m_countApprox(GmDc.Player.T_Y, GmDc.Player.Y, rate, 0.0);

			GmDc.Player.ToujouFrame++;
		}

		if(GmDc.Player.CrashFrame)
			m_countApprox(GmDc.Death_A, 0.5, 0.9, 0.0);
		else
			m_countApprox(GmDc.Death_A, 0.0, 0.95, 0.0);

		/*
			S = PShot
			E = Enemy
			W = Wall

		GmProcPShot:
			PutPShotCrash*()    -> S
			PutPShotWallCrash() -> SW
		GmProcEnemy:
			PutEnemyCrashArea() -> E
			EWC_AddPoint()      -> EW
			GetCrashedPShot()   <- S
		GmProcPlayer:
			GetCrashedEnemy()   <- E

		CheckPShotWallCrash:
			GetCrashedEnemy()   <- E, SW
		CheckEnemyWallCrash:
			GetCrashedEnemy()   <- E, EW

			! LFrmCnt はミスの回数によりスクロール位置と同期しない。
		*/

		if(GmDc.Player.CrashFrame)
		{
			GmProcPlayer();
		}
		else
		{
			GmProcPShot();
			GmProcEnemy();
			GmProcPlayer();

			CheckPShotWallCrash();
			CheckEnemyWallCrash();

			AllClearPShotCrashArea();
			AllClearEnemyCrashArea();
			AllClearPShotWallCrash();
			AllClearEnemyWallCrash();
		}

		// 描画ここから ...

		DrawWall();

		ExecuteTaskGroup(GmDc.EffectList_BS);
		GmDrawPShot();
		ExecuteTaskGroup(GmDc.EffectList_BP);
		GmDrawPlayer();
		ExecuteTaskGroup(GmDc.EffectList_BW);
		GmDrawEnemy(1);
		ExecuteTaskGroup(GmDc.EffectList_BE);
		GmDrawEnemy(0);
		ExecuteTaskGroup(GmDc.EffectList);
		DrawDeathCurtain();
		GmDrawPlayerStatus();

		DrawAllScope();
		ClearAllScope();

		GTEndFrame();
	}

	// ==== ゲームループ終了 ====

	GmDc.PShotList->Clear(ReleasePShot);
	GmDc.EnemyList->Clear(ReleaseEnemy);

	GTSetCurtain(-1.0, 40);
	MusicFadeout(30);

	while(-1.0 < GTActWhiteLevel)
	{
		DrawWall();
		GTEndFrame();
	}
}
