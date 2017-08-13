#include "Stdinc.h"

void SIF_DarkToTrans(int h, int x_size, int y_size)
{
	int x;
	int y;

	for(x = 0; x < x_size; x++)
	for(y = 0; y < y_size; y++)
	{
		SILoadPixel(h, x, y);

		Color_A = m_max(Color_R, m_max(Color_G, Color_B));
		Color_A *= Color_A;
		Color_A /= 255;

		SISavePixel(h, x, y);
	}
}
void SIF_BlackToTrans(int h, int x_size, int y_size)
{
	int x;
	int y;

	for(x = 0; x < x_size; x++)
	for(y = 0; y < y_size; y++)
	{
		SILoadPixel(h, x, y);

		// ? •
		if(
			Color_R == 0 &&
			Color_G == 0 &&
			Color_B == 0
			)
			Color_A = 0; // “§–¾
		else
			Color_A = 255; // •s“§–¾

		SISavePixel(h, x, y);
	}
}
void SIF_EnemyPic(int h, int x_size, int y_size)
{
	bitTable *silhouette = new bitTable(x_size, y_size);
	int noTrans = 0;

	for(int x = 0; x < x_size; x++)
	for(int y = 0; y < y_size; y++)
	{
		SILoadPixel(h, x, y);
		silhouette->SetBit(x, y, Color_A);

		if(Color_A)
			noTrans = 1;
	}

	error(); // silhouette, noTrans -> ?
}
