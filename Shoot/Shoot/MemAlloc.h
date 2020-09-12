void *REAL_memAlloc(int size);
void *REAL_memRealloc(void *block, int size);
void REAL_memFree(void *block);

void memAlloc_INIT(void);

void *memAlloc(int size);
void *memRealloc(void *block, int size);
void memFree(void *block);
void *memCalloc(int size);
void *memClone(void *block, int size);

// 'New Array'
#define na_(type_t, count) \
	((type_t *)memCalloc(sizeof(type_t) * (count)))

// 'New Block'
#define nb_(type_t) \
	(na_(type_t, 1))
