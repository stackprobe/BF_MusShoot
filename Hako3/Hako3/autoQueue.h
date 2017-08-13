#include "Stdinc.h"

template <class Element_t>
class autoQueue
{
private:
	autoList<Element_t> *List;
	int DeadCountMax;
	int TopIndex;

	void init(autoList<Element_t> *list_bind, int deadCountMax)
	{
		errorCase(!list_bind);
		errorCase(deadCountMax < 0 || IMAX < deadCountMax);

		this->List = list_bind;
		this->DeadCountMax = deadCountMax;
		this->TopIndex = 0;
	}

public:
	autoQueue()
	{
		this->init(new autoList<Element_t>(), IMAX);
	}
	autoQueue(int deadCountMax)
	{
		this->init(new autoList<Element_t>(), deadCountMax);
	}
	autoQueue(autoList<Element_t> *list_bind)
	{
		this->init(list_bind, IMAX);
	}
	autoQueue(autoList<Element_t> *list_bind, int deadCountMax)
	{
		this->init(list_bind, deadCountMax);
	}
	autoQueue(const autoQueue &source)
	{
		error();
	}
	~autoQueue()
	{
		delete this->List;
	}

	autoList<Element_t> *GetList()
	{
		return this->List;
	}
	void Clear()
	{
		this->List->Clear();
		this->TopIndex = 0;
	}
	int GetCount()
	{
		int count = this->List->GetCount() - this->TopIndex;

		errorCase(count < 0); // ‰^—pã‚È‚Á‚Ä‚Í‚È‚ç‚È‚¢B
		return count;
	}
	Element_t Dequeue()
	{
		Element_t e = this->List->GetElement(this->TopIndex);

		this->TopIndex++;

		if(this->GetCount() == 0)
		{
			this->List->Clear();
			this->TopIndex = 0;
		}
		else if(this->DeadCountMax < this->TopIndex)
		{
			this->List->RemoveRange(0, this->TopIndex);
			this->TopIndex = 0;
		}
		return e;
	}
	Element_t Dequeue(Element_t defaultElement)
	{
		if(this->GetCount())
		{
			return this->Dequeue();
		}
		return defaultElement;
	}
};
