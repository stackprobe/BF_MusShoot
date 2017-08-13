#include "Stdinc.h"

typedef struct Scope_st
{
	SCPLAY_t Layer;
	int ScopeType; // "CRP"

	union
	{
		struct
		{
			double X;
			double Y;
			double R;
		}
		Circle;

		struct
		{
			double L;
			double T;
			double W;
			double H;
		}
		Rect;

		struct
		{
			double X;
			double Y;
		}
		Point;
	}
	u;
}
Scope_t;

static singleton_VTI(ScopeList, autoList<Scope_t>, new autoList<Scope_t>())

void AddScopeCircle(SCPLAY_t scpLay, double x, double y, double r)
{
	Scope_t i;

	m_range(x, -(double)IMAX, (double)IMAX);
	m_range(y, -(double)IMAX, (double)IMAX);
	m_range(r, 1.0, (double)IMAX);

	i.Layer = scpLay;
	i.ScopeType = 'C';
	i.u.Circle.X = x;
	i.u.Circle.Y = y;
	i.u.Circle.R = r;

	S_ScopeList()->AddElement(i);
}
void AddScopeRect(SCPLAY_t scpLay, double l, double t, double w, double h)
{
	Scope_t i;

	m_range(l, -(double)IMAX, (double)IMAX);
	m_range(t, -(double)IMAX, (double)IMAX);
	m_range(w, 1.0, (double)IMAX);
	m_range(h, 1.0, (double)IMAX);

	i.Layer = scpLay;
	i.ScopeType = 'R';
	i.u.Rect.L = l;
	i.u.Rect.T = t;
	i.u.Rect.W = w;
	i.u.Rect.H = h;

	S_ScopeList()->AddElement(i);
}
void AddScopePoint(SCPLAY_t scpLay, double x, double y)
{
	Scope_t i;

	m_range(x, -(double)IMAX, (double)IMAX);
	m_range(y, -(double)IMAX, (double)IMAX);

	i.Layer = scpLay;
	i.ScopeType = 'P';
	i.u.Point.X = x;
	i.u.Point.Y = y;

	S_ScopeList()->AddElement(i);
}
void ClearAllScope(void)
{
	S_ScopeList()->Clear();
}
void DrawAllScope(void)
{
	static int scoptEnabled;

	if(!scoptEnabled)
	{
		if(S_ScopeList()->GetCount() == 0)
			return;

		scoptEnabled = 1;
	}

	SetBright(0, 0, 0);
	SetAlpha(0.5);
	DrawPicRect(0, 0, SCREEN_W, SCREEN_H, Pic(P_WHITEBOX));
	ResetBlend();
	ResetBright();

	for(int index = 0; index < S_ScopeList()->GetCount(); index++)
	{
		Scope_t *scope = S_ScopeList()->ElementAt(index);
		double cR = 0.0;
		double cG = 0.0;
		double cB = 0.0;
		double a = 0.25;

		switch(scope->Layer)
		{
		case SCPLAY_PSHOT_CRASH:
			cR = 1.0;
			cG = 1.0;
			break;
		case SCPLAY_PS_WALL_CRASH:
			cR = 1.0;
			cB = 1.0;
			break;
		case SCPLAY_PS_ENEMY_CRASH:
			cG = 1.0;
			cB = 1.0;
			break;

		default:
			error();
		}
		switch(scope->ScopeType)
		{
		case 'C':
			{
				SetAlpha(a);
				SetBright(cR, cG, cB);
				DrawBegin(scope->u.Circle.X, scope->u.Circle.Y, Pic(P_WHITECIRCLE));
				DrawZoom(scope->u.Circle.R / 50.0);
				DrawEnd();
				ResetBright();
				ResetBlend();
			}
			break;

		case 'R':
			{
				SetAlpha(a);
				SetBright(cR, cG, cB);
				DrawPicRect(
					m_d2i(scope->u.Rect.L),
					m_d2i(scope->u.Rect.T),
					m_d2i(scope->u.Rect.W),
					m_d2i(scope->u.Rect.H),
					Pic(P_WHITEBOX)
					);
				ResetBright();
				ResetBlend();
			}
			break;

		case 'P':
			{
				SetAlpha(a);
				SetBright(cR, cG, cB);
				DrawPicRect(
					m_d2i(scope->u.Point.X) - 10,
					m_d2i(scope->u.Point.Y),
					20,
					1,
					Pic(P_WHITEBOX)
					);
				DrawPicRect(
					m_d2i(scope->u.Point.X),
					m_d2i(scope->u.Point.Y) - 10,
					1,
					20,
					Pic(P_WHITEBOX)
					);
				ResetBright();
				ResetBlend();
			}
			break;

		default:
			error();
		}
	}
}
