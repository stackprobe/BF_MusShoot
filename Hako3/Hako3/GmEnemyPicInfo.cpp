#include "Stdinc.h"

static singleton_VTI(EnemyPicInfoList, autoList<EnemyPicInfo_t *>, makeList(P_MAX, (EnemyPicInfo_t *)NULL))

EnemyPicInfo_t *GetEnemyPicInfo(int resno)
{
	EnemyPicInfo_t *epi = S_EnemyPicInfoList()->GetElement(resno);

	if(epi)
		return epi;

	autoList<uchar> *image = Pub_LoadResource(Pic_Res(), resno);
	int h = LoadSoftImageToMem(image->ElementAt(0), image->GetCount());
	errorCase(h == -1); // ? Ž¸”s
	int isBmp = PL_ImageIsBmp(image);
	delete image;

	int x_size;
	int y_size;

	errorCase(GetSoftImageSize(h, &x_size, &y_size) != 0); // ? Ž¸”s
	errorCase(x_size < 1 || IMAX < x_size);
	errorCase(y_size < 1 || IMAX < y_size);

	bitTable *silhouette = new bitTable(x_size, y_size);
	int noTrans = 0;

	EnterRGBA();

	for(int x = 0; x < x_size; x++)
	for(int y = 0; y < y_size; y++)
	{
		SILoadPixel(h, x, y);

		if(isBmp)
			Color_A = Color_R || Color_G || Color_B;

		silhouette->SetBit(x, y, Color_A);

		if(Color_A)
			noTrans = 1;
	}
	LeaveRGBA();

	errorCase(DeleteSoftImage(h) != 0); // ? Ž¸”s

	epi = nb(EnemyPicInfo_t);
	epi->Silhouette = silhouette;
	epi->STSilhouette = new bitSubTable(silhouette, 0, 0, x_size, y_size);
	epi->NoTrans = noTrans;
	epi->Width = x_size;
	epi->Height = y_size;

	S_EnemyPicInfoList()->SetElement(resno, epi);
	return epi;
}

static singleton_VTI(WallSilhouettes, autoList<bitSubTable *>, new autoList<bitSubTable *>())

bitSubTable *GetWallSilhouette(int picIndex, int picXPos, int picYPos)
{
	errorCase(picIndex < 0 || KABE_NUM <= picIndex);
	errorCase(picXPos < 0 || KABE_W <= picXPos);
	errorCase(picYPos < 0 || KABE_H <= picYPos);

	int index =
		picIndex * KABE_W * KABE_H +
		picYPos * KABE_W +
		picXPos;

	bitSubTable *ws = S_WallSilhouettes()->RefElement(index, NULL);

	if(!ws)
	{
		ws = new bitSubTable(
			GetEnemyPicInfo(P_KABE_00 + picIndex)->Silhouette,
			picXPos * 16,
			picYPos * 16,
			16,
			16
			);

		S_WallSilhouettes()->PutElement(index, ws, NULL);
	}
	return ws;
}
