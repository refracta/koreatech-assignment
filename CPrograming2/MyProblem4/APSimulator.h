#define GRID_HEIGHT 20
#define GRID_WIDTH ((GRID_HEIGHT * 2) + 1)

#define ANGEL_GLYPH 'A'
#define DEVIL_GLYPH 'D'
#define REMOVED_BLOCK_GLYPH '#'
#define EMPTY_GLYPH '.'

int to2DX(int);
int to2DY(int);
int toIndex(int, int);
void initSimulator(int (*)(char[GRID_WIDTH][GRID_HEIGHT], int, int));
void runSimulator();
