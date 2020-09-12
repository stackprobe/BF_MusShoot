/*
	スクリーンサイズは 640 x 480 とする。

	float, double をゼロクリアした値 (な初期値) は 0.0 とする。
	IEEE754って全CPUが準拠してるかどうか知らないけど、してると信じる。

	----

	フレームループの形

	GTFreezeInput();
	LFrmCnt = 0;

	for(; ; )
	{
		// UpdateMouseMove(); // as needed

		1. 処理 // *1
		2. 描画
		3. GTEndFrame();
	}

	*1 ... ループの脱出、他のループへの割り込み(ポーズ画面など)は 1. で行う。
		戻ってきたときの GTFreezeInput(); は呼び出し側で行う。
		呼び出し先でそういった後始末を行うと、呼び出し側の都合を考慮できないため。
*/

#include "Stdinc.h"

/*
singleton_VTI(EnemyLv1PictureGroup, PictureGroup_t, MakePictureGroup(SIF_EnemyLv1, NULL))
singleton_VTI(EnemyLv2PictureGroup, PictureGroup_t, MakePictureGroup(SIF_EnemyLv2, NULL))
singleton_VTI(EnemyLv3PictureGroup, PictureGroup_t, MakePictureGroup(SIF_EnemyLv3, NULL))
*/
// singleton_VTI(EnemyPicGrp, PictureGroup_t, MakePictureGroup(SIF_EnemyPic, NULL))
singleton_VTI(HSTEffectPicGrp, PictureGroup_t, MakePictureGroup(SIF_DarkToTrans, NULL))

static void MiniLogo(void)
{
	const double kx = 320.0;
	const double ky = 240.0;

	NEL_forscene(60)
	{
		if(fs_count == 50)
		{
			if(2 < FRDLevel) // ここで処理落ちするならリフレッシュレートが 60 Hz じゃないんだろう。
			{
				SetVSyncFlag(0);
			}
		}
		GTDrawBlackWall();
		DrawBegin(kx, ky, Pic(P_DUMMY));
		DrawRotate(fs_rate * PI);
		DrawEnd();
		GTEndFrame();
	}
}
void ApHome(void)
{
//	S_SoftImageFilterList() default: NULL
//	S_SoftImageFilterList()->SetElement(P_DUMMY, SIF_DarkToTrans);

//	S_GraphicHandleFilterList() default: NULL
//	S_GraphicHandleFilterList()->SetElement(P_DUMMY, ?);

	/*
		BMP -> 黒を透明
		PNG -> 内容に従う
		という風に決まったので実質使わない。黒の透明化 -> Pic_Load()
	*/
//	S_EnableTransList() default: 1
//	S_EnableTransList()->SetElement(P_DUMMY, 0);

//	S_MusicVolumeList() default: 0.5 (0.0-1.0) マスタリング補正
//	S_MusicVolumeList()->SetElement(MUSIC_DUMMY, 0.1);

//	S_SEVolumeList() default: 0.5 (0.0-1.0) マスタリング補正
//	S_SEVolumeList()->SetElement(SE_DUMMY, 0.1);

	// < 初期値など

	MiniLogo();

	if(Sd.ScreenZoom != 1.0)
	{
		ApplyWindowSize();

		GTDrawBlackWall();
		GTEndFrame();
	}


	// test >

	GmDc.MapIndex = 0;
	GmDc.MapStartPos = 0;

	GmHome();

	// < test


	MusicFadeout(30);
//	GTWaitFadeout(P_TITLEWALL, -1.0, 40);
	GTWaitFadeout(P_DUMMY, -1.0, 40);
}
