typedef enum SCPLAY_et
{
	SCPLAY_PSHOT_CRASH,
	SCPLAY_PS_WALL_CRASH,
	SCPLAY_PS_ENEMY_CRASH,
}
SCPLAY_t;

void AddScopeCircle(SCPLAY_t scpLay, double x, double y, double r);
void AddScopeRect(SCPLAY_t scpLay, double l, double t, double w, double h);
void AddScopePoint(SCPLAY_t scpLay, double x, double y);
void ClearAllScope(void);
void DrawAllScope(void);
