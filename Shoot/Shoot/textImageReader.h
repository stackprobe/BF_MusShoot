class textImageReader
{
private:
	autoList<uchar> *Image;
	int ReadIndex;
	int ReadEOF;

public:
	textImageReader(autoList<uchar> *bind_image)
	{
		this->Image = bind_image;
		this->ReadIndex = 0;
		this->ReadEOF = 0;
	}
	textImageReader(const textImageReader &source)
	{
		error();
	}
	~textImageReader()
	{
		delete this->Image;
	}

	int IsReadEOF()
	{
		return this->ReadEOF;
	}
	int ReadChar()
	{
		if(this->Image->GetCount() <= this->ReadIndex)
		{
			this->ReadEOF = 1;
			return EOF;
		}
		return this->Image->GetElement(this->ReadIndex++);
	}
	char *ReadLine(int lenmax)
	{
		char *line = (char *)memAlloc(lenmax + 1);
		int index = 0;

		while(index < lenmax)
		{
			int chr = this->ReadChar();

			if(chr == '\r')
				continue;

			if(chr == '\n' || chr == EOF)
				break;

			line[index] = chr;
			index++;
		}
		if(index == 0 && this->ReadEOF)
		{
			memFree(line);
			return NULL;
		}
		line[index] = '\0';
		return line;
	}
	char *ReadLine()
	{
		return this->ReadLine(1023);
	}
	autoList<char *> *ReadLineListBlock()
	{
		autoList<char *> *result = new autoList<char *>();
		char *line;

		while(line = this->ReadLine())
		{
			if(!line)
				break;

			if(line[0] == '\0')
			{
				memFree(line);
				break;
			}
			result->AddElement(line);
		}
		return result;
	}
};
