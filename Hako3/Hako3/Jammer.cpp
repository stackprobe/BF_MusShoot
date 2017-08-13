#include "Stdinc.h"

#define MULTIVAL 157
#define POWERVAL 31

static int SubJammer(autoList<uchar> *block, int doEncode)
{
	int tznum = block->UnaddRepeat(0x00);
	int value = 0;

	if(!block->GetCount())
	{
		if(doEncode)
		{
			tznum++;
		}
		else
		{
			if(!tznum)
				return 0;

			tznum--;
		}
	}
	else if(doEncode)
	{
		for(int index = 0; index < block->GetCount() || value; index++)
		{
			value += block->RefElement(index, 0x00) * MULTIVAL;
			block->PutElement(index, value & 0xff, 0x00);
			value >>= 8;
		}
	}
	else
	{
		for(int index = block->GetCount(); index; )
		{
			index--;
			value |= block->GetElement(index);
			block->SetElement(index, value / MULTIVAL);
			value %= MULTIVAL;
			value <<= 8;
		}
		if(value)
			return 0;

		block->UnaddRepeat(0x00);
	}
	block->AddRepeat(0x00, tznum);
	return 1;
}
int Jammer(autoList<uchar> *block, int doEncode)
{
	for(int count = POWERVAL; count; count--)
		if(!SubJammer(block, doEncode))
			return 0;

	return 1;
}
