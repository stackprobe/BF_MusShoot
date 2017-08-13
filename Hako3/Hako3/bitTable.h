class bitTable
{
private:
	bitList *List; // [x + y * Width]
	int Width;
	int Height;
	int SubTableCount;

public:
	bitTable(int w, int h)
	{
		errorCase(w < 1 || IMAX < w);
		errorCase(h < 1 || IMAX < h);

		this->List = new bitList();
		this->Width = w;
		this->Height = h;
		this->SubTableCount = 0;
	}
	bitTable(const bitTable &source)
	{
		error();
	}
	~bitTable()
	{
		errorCase(this->SubTableCount); // ? ŽQÆ‚µ‚Ä‚¢‚é bitSubTable ‚ª‚ ‚éB

		delete this->List;
	}

	void SetBit(int x, int y, int value)
	{
		errorCase(x < 0 || this->Width <= x);
		errorCase(y < 0 || this->Height <= y);

		this->List->PutBit(x + y * this->Width, value);
	}
	int GetBit(int x, int y)
	{
		errorCase(x < 0 || this->Width <= x);
		errorCase(y < 0 || this->Height <= y);

		return this->List->RefBit(x + y * this->Width);
	}

	int GetWidth()
	{
		return this->Width;
	}
	int GetHeight()
	{
		return this->Height;
	}

	void HandleBySubTable()
	{
		this->SubTableCount++;
	}
	void UnhandleBySubTable()
	{
		this->SubTableCount--;
	}
};
