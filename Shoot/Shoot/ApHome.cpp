/*
	�X�N���[���T�C�Y�� 640 x 480 �Ƃ���B

	float, double ���[���N���A�����l (�ȏ����l) �� 0.0 �Ƃ���B
	IEEE754���đSCPU���������Ă邩�ǂ����m��Ȃ����ǁA���Ă�ƐM����B

	----

	�t���[�����[�v�̌`

	GTFreezeInput();
	LFrmCnt = 0;

	for(; ; )
	{
		// UpdateMouseMove(); // as needed

		1. ���� // *1
		2. �`��
		3. GTEndFrame();
	}

	*1 ... ���[�v�̒E�o�A���̃��[�v�ւ̊��荞��(�|�[�Y��ʂȂ�)�� 1. �ōs���B
		�߂��Ă����Ƃ��� GTFreezeInput(); �͌Ăяo�����ōs���B
		�Ăяo����ł�����������n�����s���ƁA�Ăяo�����̓s�����l���ł��Ȃ����߁B
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
			if(2 < FRDLevel) // �����ŏ�����������Ȃ烊�t���b�V�����[�g�� 60 Hz ����Ȃ��񂾂낤�B
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
		BMP -> ���𓧖�
		PNG -> ���e�ɏ]��
		�Ƃ������Ɍ��܂����̂Ŏ����g��Ȃ��B���̓����� -> Pic_Load()
	*/
//	S_EnableTransList() default: 1
//	S_EnableTransList()->SetElement(P_DUMMY, 0);

//	S_MusicVolumeList() default: 0.5 (0.0-1.0) �}�X�^�����O�␳
//	S_MusicVolumeList()->SetElement(MUSIC_DUMMY, 0.1);

//	S_SEVolumeList() default: 0.5 (0.0-1.0) �}�X�^�����O�␳
//	S_SEVolumeList()->SetElement(SE_DUMMY, 0.1);

	// < �����l�Ȃ�

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
