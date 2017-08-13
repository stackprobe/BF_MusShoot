class bitList
{
private:
	autoList<uchar> *List;

public:
	bitList()
	{
		this->List = new autoList<uchar>();
	}
	bitList(const bitList &source)
	{
		error();
	}
	~bitList()
	{
		delete this->List;
	}

	void PutBit(int index, int value)
	{
		uchar c = this->List->RefElement(index / 8, 0);

		if(value)
			c |= 1 << (index % 8);
		else
			c &= ~(1 << (index % 8));

		this->List->PutElement(index / 8, c, 0);
	}
	int RefBit(int index)
	{
		return (this->List->RefElement(index / 8, 0) >> (index % 8)) & 1;
	}
};
