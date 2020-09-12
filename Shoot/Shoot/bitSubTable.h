class bitSubTable
{
private:
	bitTable *Parent;
	int Left;
	int Top;
	int Width;
	int Height;
	int NoTrans; // -1: uninited 0: no 1: yes 2: yes(“§–¾ŠF–³)

public:
	double HD; // Half of Diagonal

	bitSubTable(bitTable *parent, int l, int t, int w, int h)
	{
		errorCase(!parent);
		errorCase(l < 0 || parent->GetWidth() <= l);
		errorCase(t < 0 || parent->GetHeight() <= t);
		errorCase(w < 1 || parent->GetWidth() + l < w);
		errorCase(h < 1 || parent->GetHeight() + t < h);

		parent->HandleBySubTable();

		this->Parent = parent;
		this->Left = l;
		this->Top = t;
		this->Width = w;
		this->Height = h;
		this->NoTrans = -1;
		this->HD = sqrt(m_pow((double)w) + m_pow((double)h)) / 2.0;
	}
	bitSubTable(const bitSubTable &source)
	{
		error();
	}
	~bitSubTable()
	{
		this->Parent->UnhandleBySubTable();
	}

	/*
	void SetBit(int x, int y, int value)
	{ }
	*/
	int GetBit(int x, int y)
	{
		errorCase(x < 0 || this->Width <= x);
		errorCase(y < 0 || this->Height <= y);

		return this->Parent->GetBit(this->Left + x, this->Top + y);
	}
	int RefBit(int x, int y)
	{
		if(
			x < 0 || this->Width <= x ||
			y < 0 || this->Height <= y
			)
		{
			return 0;
		}
		return this->Parent->GetBit(this->Left + x, this->Top + y);
	}

	int GetWidth()
	{
		return this->Width;
	}
	int GetHeight()
	{
		return this->Height;
	}

	int IsNoTrans()
	{
		if(this->NoTrans == -1)
		{
			int noTrans = 0;
			int trans = 0;

			for(int x = 0; x < this->Width; x++)
			for(int y = 0; y < this->Height; y++)
			{
				if(this->GetBit(x, y))
					noTrans = 1;
				else
					trans = 1;
			}
			this->NoTrans = noTrans ? (trans ? 1 : 2) : 0;
		}
		return this->NoTrans;
	}
};
