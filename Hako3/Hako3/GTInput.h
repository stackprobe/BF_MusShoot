enum
{
	// input ->

	INP_DIR_2,
	INP_DIR_4,
	INP_DIR_6,
	INP_DIR_8,
	INP_A,
	INP_B,
	INP_C,
	INP_D,
	INP_E,
	INP_F,
	INP_L,
	INP_R,
	INP_PAUSE,

	INP_MAX, // num of 'input' member

	// mode ->

	INP_PRESS,      // ? 押されている間 true
	INP_DOWN,       // ? 押した瞬間だけ true
	INP_PRESSCOUNT, // ? 押されている間 1, 2, 3, 4 ...
	INP_HIT,        // ? キーボード的な連打 ( 押した瞬間と連打の瞬間だけ true )
};

extern int GTPrimaryPadno;
extern int GTI_ResumeFrame;

int GTGetInput(int input, int mode);
void GTFreezeInput(void);
