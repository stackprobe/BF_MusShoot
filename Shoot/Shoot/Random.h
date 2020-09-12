#define MT19937_N 624

void initRnd(int seed);

void enterRnd(unsigned long *lmt, int lmti);
void leaveRnd(void);

int rnd(int modulo);
int bRnd(int minval, int maxval);
int sRnd(void);
double dRnd(void);
double eRnd(void);

class Random
{
private:
	unsigned long *mt;
	int mti;

	void Enter()
	{
		enterRnd(this->mt, this->mti);
	}
	void Leave()
	{
		leaveRnd();
	}

public:
	Random(int seed)
	{
		this->mt = (unsigned long *)memAlloc(MT19937_N * sizeof(unsigned long));
		this->Enter();
		initRnd(seed);
		this->Leave();
	}
	Random(const Random &source)
	{
		error();
	}
	~Random()
	{
		memFree(this->mt);
	}

#define WRAPPER(RET_TYPE, DEF_FUNC, CALL_FUNC) \
	DEF_FUNC \
	{ \
		this->Enter(); \
		RET_TYPE retval = CALL_FUNC; \
		this->Leave(); \
		return retval; \
	}

	WRAPPER(int, int rnd(int modulo), rnd(modulo))
	WRAPPER(int, int bRnd(int minval, int maxval), bRnd(minval, maxval))
	WRAPPER(int, int sRnd(), sRnd())
	WRAPPER(double, double dRnd(), dRnd())
	WRAPPER(double, double eRnd(), eRnd())

#undef WRAPPER
};
