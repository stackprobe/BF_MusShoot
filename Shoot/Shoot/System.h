#define error() \
	error2(__FILE__, __LINE__, __FUNCTION__)

#define errorCase(status) \
	do { \
	if((status)) error(); \
	} while(0)

void error2(char *source, int lineno, char *function);

// --- LOG ----

#define LOG_DIR "C:\\tmp"
#define LOG_FILE (LOG_DIR "\\Game.log")

FILE *GetLogFp(void);

#if LOG_ENABLED
#define LOG(format, ...) fprintf(GetLogFp(), format, ## __VA_ARGS__)
//#define LOG(format, ...) (fprintf(GetLogFp(), format, ## __VA_ARGS__), fflush(GetLogFp()))
#else
#define LOG(format, ...) 1
#endif

#define LOGPOS() LOG("[POS] %s (%d) %s\n", __FILE__, __LINE__, __FUNCTION__)

// ---

extern int fs_count;
extern int fs_max;
extern double fs_rate; // 0.0 - 1.0

#define NEL_forscene(frmmax) \
	for(fs_max = (frmmax), fs_count = 0; fs_count <= (frmmax) && (fs_rate = (double)fs_count / fs_max, 1); fs_count++)

#define NEL_ifsceneBegin_CM(frmcnt, frmmax) \
	if(fs_count = (frmcnt), 0) {} NEL_ifscene((frmmax))

#define NEL_ifscene(frmmax) \
	else if(fs_count <= (frmmax) ? (fs_max = (frmmax), fs_rate = (double)fs_count / (frmmax), 1) : (fs_count -= (frmmax) + 1, 0))

#define NEL_ifsceneEnd \
	else

int IsWindowActive(void);
