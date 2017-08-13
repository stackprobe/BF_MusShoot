#define _CRT_SECURE_NO_WARNINGS

#include <conio.h>
#include <ctype.h>
#include <direct.h>
#include <dos.h>
#include <fcntl.h>
#include <io.h>
#include <limits.h>
#include <malloc.h>
#include <math.h>
#include <mbstring.h>
#include <process.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys\types.h> // sys\\stat.h より先に include すること。
#include <sys\stat.h>
#include <time.h>

#include <DxLib.h>

// ====

/*
	0 or 1
*/
#define ALL_LOG 0

#define APPLOG_ENABLED ALL_LOG
#define LOG_ENABLED ALL_LOG
#define SW_ENABLED ALL_LOG

#define SCOPE_ENABLED 0

// ====

typedef unsigned char uchar;
typedef unsigned __int32 uint;
typedef unsigned __int64 uint64;

#define SCREEN_W 640
#define SCREEN_H 480

#define SCREEN_CENTER_X (SCREEN_W / 2)
#define SCREEN_CENTER_Y (SCREEN_H / 2)

#define IMAX 1000000000

#define HANDLE_CLOSED -1
#define PI 3.141592653589793

// app >

#define ENEMY_X_MIN (-SCREEN_W)
#define ENEMY_X_MAX (SCREEN_W * 2)
#define ENEMY_Y_MIN (-SCREEN_H)
#define ENEMY_Y_MAX (SCREEN_H * 2)

#define KABE_NUM 9
#define KABE_W (256 / 16)
#define KABE_H (6000 / 16)

enum
{
	WEAPON_NORMAL,
	WEAPON_LASER,
	WEAPON_ROCK,
	WEAPON_SLOW,
	WEAPON_BLADE,
	WEAPON_DOUBLE,
	WEAPON_06,
	WEAPON_07,
	WEAPON_08,

	WEAPON_MAX, // num of member
};

#define ROCK_HAMMER_TAIL_MAX 32 // 画像は 10 x 128

#define ESHOT_PIC_MAX 8
#define ESHOT_COLOR_MAX 5 // D_ESHOT_00_00 - D_ESHOT_(ESHOT_COLOR_MAX - 1)1_00 になること。

// < app

/*
	ex.
		singleton_VTI(IntList, int, (int *)na(int, 100))           <- プロトタイプは singleton_proto_VT(IntList, int)
		static singleton_VTI(ClassABC, ClassABC, new ClassABC())   <- static にも出来るよ。
*/
#define singleton_VTI(var_name, type_t, init_op) \
	type_t *S_##var_name(void) { \
		static type_t *p; \
		if(!p) { \
			p = (init_op); \
		} \
		return p; \
	}

#define singleton_proto_VT(var_name, type_t) \
	type_t *S_##var_name(void);

/*
	counter ... (-1): 放した, 0: 放している, 1: 押した, 2-: 押している
*/
#define UPDATEINPUT(status, counter) \
	if((status)) { \
		(counter) = m_max(0, (counter)); \
		(counter)++; \
	} \
	else { \
		(counter) = 0 < (counter) ? -1 : 0; \
	}

#define ENUM_RANGE(member_name, num) \
	member_name, \
	member_name##_LAST = member_name + (num) - 1,

#define lengthof(list) \
	(sizeof((list)) / sizeof(*(list)))

#define m_min(value1, value2) \
	((value1) < (value2) ? (value1) : (value2))

#define m_max(value1, value2) \
	((value1) < (value2) ? (value2) : (value1))

#define m_minim(var, value) \
	((var) = m_min((var), (value)))

#define m_maxim(var, value) \
	((var) = m_max((var), (value)))

#define m_range(var, minval, maxval) \
	do { \
	m_maxim((var), (minval)); \
	m_minim((var), (maxval)); \
	} while(0)

#define ec_range(value, minval, maxval) \
	errorCase((value) < (minval) || (maxval) < (value))

#define m_iSign(value) \
	((value) < 0 ? -1 : 0 < (value) ? 1 : 0)

#define m_isRange(value, minval, maxval) \
	((minval) <= (value) && (value) <= (maxval))

#define m_compCond(status1, status2) ((status1) ? (status2) : !(status2))
#define m_d2i(value) ((int)((value) + 0.5))
#define m_pow(value) ((value) * (value))

#define m_d2i_s(value) \
	((value) < 0.0 ? \
		-m_d2i(-(value)) : \
		+m_d2i(+(value)) \
		)

#define m_countDown(var) \
	((var) < 0 ? (var)++ : 0 < (var) ? (var)-- : (var))

#define m_abssub(value1, value2) \
	((value1) < (value2) ? (value2) - (value1) : (value1) - (value2))

/*
	rate: 0.0 -> 1.0 == fast -> slow
*/
#define m_countApprox(var, dest, rate, margin) \
	do { \
	(var) -= (dest); \
	(var) *= (rate); \
	(var) += (dest); \
	m_abssub((var), (dest)) <= (margin) && ((var) = (dest)); \
	} while(0)

// var1 -> var2, var2 -> var1 する。
#define m_swap(var1, var2, vartmp) \
	do { \
	(vartmp) = (var1); \
	(var1) = (var2); \
	(var2) = (vartmp); \
	} while(0)

// var1 -> var2, var2 -> var3, var3 -> var1 する。
#define m_rot3(var1, var2, var3, vartmp) \
	do { \
	(vartmp) = (var1); \
	(var1) = (var2); \
	(var2) = (var3); \
	(var3) = (vartmp); \
	} while(0)

// var1 <= var2 となる様にする。
#define m_sort2(var1, var2, vartmp) \
	do { \
	if((var2) < (var1)) { \
		m_swap((var1), (var2), (vartmp)); \
	} \
	} while(0)

// var1 <= var2 <= var3 となる様にする。
#define m_sort3(var1, var2, var3, vartmp) \
	do { \
	m_sort2((var1), (var2), (vartmp)); \
	m_sort2((var2), (var3), (vartmp)); \
	m_sort2((var1), (var2), (vartmp)); \
	} while(0)

#define m_isNear(x1, y1, x2, y2, r) \
	(m_pow((x1) - (x2)) + m_pow((y1) - (y2)) < m_pow((r)))
