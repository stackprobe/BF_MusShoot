typedef struct EnemyPicInfo_st
{
	bitTable *Silhouette;
	bitSubTable *STSilhouette;
	int NoTrans;
	int Width;
	int Height;
}
EnemyPicInfo_t;

EnemyPicInfo_t *GetEnemyPicInfo(int resno);

bitSubTable *GetWallSilhouette(int picIndex, int picXPos, int picYPos);
