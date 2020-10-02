#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "APSimulator.h"

#define MAIN_SCREEN_HEIGHT 24
#define WAIT_TURN 200
#define WAIT_EVENT 1000
#define BUFFER_SIZE 8192
#define UNIT_WAIT 10

#define millisecondDiff(begin, end) (((double) (end.tv_sec - begin.tv_sec) + (end.tv_nsec - begin.tv_nsec) * 1.0e-9) * 1000)

#ifdef __unix__

#include <termios.h>
#include <unistd.h>

void gotoxy(int x, int y) {
    printf("\033[%d;%df", y, x);
    fflush(stdout);
}

/* Source from
 * https://www.linuxquestions.org/questions/programming-9/kbhit-34027/
 * https://stackoverflow.com/questions/448944/c-non-blocking-keyboard-input
*/
static struct termios initialSettings, newSettings;

int kbhit() {
    struct timeval tv = {0L, 0L};
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(0, &fds);
    return select(1, &fds, NULL, NULL, &tv);
}

int getch() {
    int r;
    unsigned char c;
    if ((r = read(0, &c, sizeof(c))) < 0) {
        return r;
    } else {
        return c;
    }
}

void initKeyboard() {
    tcgetattr(0, &initialSettings);
    newSettings = initialSettings;
    newSettings.c_lflag &= ~ICANON;
    newSettings.c_lflag &= ~ECHO;
    newSettings.c_lflag &= ~ISIG;
    newSettings.c_cc[VMIN] = 1;
    newSettings.c_cc[VTIME] = 0;
    tcsetattr(0, TCSANOW, &newSettings);
}

void init() {
    srand(time(NULL));
    initKeyboard();
}

#define clear() system("clear")
#define wait(ms) usleep(ms * 1000)
#elif defined(_WIN32) || defined(WIN32)
#include <Windows.h>
#define getchar() getch()
#define clear() system("cls")
#define wait(ms) Sleep(ms)
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

/* Source from
 * https://stackoverflow.com/questions/5404277/porting-clock-gettime-to-windows
*/
#define CLOCK_MONOTONIC 1
#define exp7           10000000i64     //1E+7     //C-file part
#define exp9         1000000000i64     //1E+9
#define w2ux 116444736000000000i64     //1.jan1601 to 1.jan1970
void unix_time(struct timespec* spec) {
    __int64 wintime; GetSystemTimeAsFileTime((FILETIME*)&wintime);
    wintime -= w2ux;  spec->tv_sec = wintime / exp7;
    spec->tv_nsec = wintime % exp7 * 100;
}

int clock_gettime(int X, struct timespec* spec) {
    static  struct timespec startspec; static double ticks2nano;
    static __int64 startticks, tps = 0;    __int64 tmp, curticks;
    QueryPerformanceFrequency((LARGE_INTEGER*)&tmp); //some strange system can
    if (tps != tmp) {
        tps = tmp; //init ~~ONCE         //possibly change freq ?
        QueryPerformanceCounter((LARGE_INTEGER*)&startticks);
        unix_time(&startspec); ticks2nano = (double)exp9 / tps;
    }
    QueryPerformanceCounter((LARGE_INTEGER*)&curticks); curticks -= startticks;
    spec->tv_sec = startspec.tv_sec + (curticks / tps);
    spec->tv_nsec = startspec.tv_nsec + (double)(curticks % tps) * ticks2nano;
    if (!(spec->tv_nsec < exp9)) { spec->tv_sec++; spec->tv_nsec -= exp9; }
    return 0;
}

#define STD_OUTPUT_HANDLE -11
void gotoxy(int x, int y) {
    COORD Pos;
    Pos.X = x;
    Pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void init() {
    srand((unsigned int) time(NULL));
}
#endif

const char MAIN_SCREEN[MAIN_SCREEN_HEIGHT][BUFFER_SIZE] = {
        "       d8888                            888      8888888b.                  888      888                        ",
        "      d88888                            888      888   Y88b                 888      888                        ",
        "     d88P888                            888      888    888                 888      888                        ",
        "    d88P 888 88888b.   .d88b.   .d88b.  888      888   d88P 888d888 .d88b.  88888b.  888  .d88b.  88888b.d88b.  ",
        "   d88P  888 888 \"88b d88P\"88b d8P  Y8b 888      8888888P\"  888P\"  d88\"\"88b 888 \"88b 888 d8P  Y8b 888 \"888 \"88b ",
        "  d88P   888 888  888 888  888 88888888 888      888        888    888  888 888  888 888 88888888 888  888  888 ",
        " d8888888888 888  888 Y88b 888 Y8b.     888      888        888    Y88..88P 888 d88P 888 Y8b.     888  888  888 ",
        "d88P     888 888  888  \"Y88888  \"Y8888  888      888        888     \"Y88P\"  88888P\"  888  \"Y8888  888  888  888 ",
        "                           888                                                                                  ",
        "                      Y8b d88P                                                                                  ",
        "                       \"Y88P\"                                                                                   ",
        " .d8888b.  d8b                        888          888                                                          ",
        "d88P  Y88b Y8P                        888          888                                                          ",
        "Y88b.                                 888          888                                                          ",
        " \"Y888b.   888 88888b.d88b.  888  888 888  8888b.  888888 .d88b.  888d888                                       ",
        "    \"Y88b. 888 888 \"888 \"88b 888  888 888     \"88b 888   d88\"\"88b 888P\"                                         ",
        "      \"888 888 888  888  888 888  888 888 .d888888 888   888  888 888                                           ",
        "Y88b  d88P 888 888  888  888 Y88b 888 888 888  888 Y88b. Y88..88P 888                                           ",
        " \"Y8888P\"  888 888  888  888  \"Y88888 888 \"Y888888  \"Y888 \"Y88P\"  888      by refracta                          ",
        "",
        "\tGitHub: https://github.com/refracta/koreatech-assignment",
        "\t\tCPrograming2 - MyProblem4",
        "\t\tPress the key!",
        "\t\t(a)uto, (m)anual (c)lose"
};

void printMainScreen() {
    for (int i = 0; i < MAIN_SCREEN_HEIGHT; i++) {
        printf("%s\n", MAIN_SCREEN[i]);
    }
}

struct Position {
    int x;
    int y;
};

struct Position toPos(int index) {
    int y = index / GRID_WIDTH;
    int x = index - y * GRID_WIDTH;
    return (struct Position) {x, y};
}

int toIndex(int x, int y) {
    return y * GRID_WIDTH + x;
}

int toIndexByPos(struct Position *pos) {
    return toIndex(pos->x, pos->y);
}

int to2DY(int index) {
    return index / GRID_WIDTH;
}

int to2DX(int index) {
    return index - to2DY(index) * GRID_WIDTH;
}

int checkRange(int index) {
    return 0 <= index && index <= toIndex(GRID_WIDTH - 1, GRID_HEIGHT - 1);
}


enum AngelStrategy {
    CENTER, LEFT, RIGHT
};

int angleStrategyArray[3] = {CENTER, LEFT, RIGHT};

struct AngelProblem {
    struct Position angel;
    int angelStrategy;
    struct Position devil;
    int turn;
    int readyToEnd;

    int (*controlDevil)(char[GRID_WIDTH][GRID_HEIGHT], int, int);

    char grid[GRID_WIDTH][GRID_HEIGHT];
    char result[GRID_HEIGHT + 1][BUFFER_SIZE];
    int resultIndex;
    int lastAngelStatus;
};

void initGrid(char grid[GRID_WIDTH][GRID_HEIGHT]) {
    for (int x = 0; x < GRID_WIDTH; x++) {
        for (int y = 0; y < GRID_HEIGHT; y++) {
            grid[x][y] = '.';
        }
    }
}

void printGrid(char grid[GRID_WIDTH][GRID_HEIGHT]) {
    for (int y = GRID_HEIGHT - 1; y >= 0; y--) {
        for (int x = 0; x < GRID_WIDTH; x++) {
            printf("%c", grid[x][y]);
        }
        printf("\n");
    }
}

void printGridToBuffer(char grid[GRID_WIDTH][GRID_HEIGHT], char *buffer) {
    int index = strlen(buffer);
    for (int y = GRID_HEIGHT - 1; y >= 0; y--) {
        for (int x = 0; x < GRID_WIDTH; x++) {
            buffer[index++] = grid[x][y];
        }
        buffer[index++] = '\n';
    }
    buffer[index] = '\0';
}

enum AngelStatus {
    MOVE, ESCAPE, STUCK
};

enum DevilStatus {
    SUCCESSFULLY_REMOVED, FAIL_BY_ALREADY_REMOVED_BLOCK, FAIL_BY_ANGEL_POSITION, OUT_OF_RANGE
};

enum UserSelection {
    AUTO, MANUAL, CLOSE, FAST, SLOW, PREVIOUS, NEXT, DUMP, RETURN, UNKNOWN
};

int toSelectionEnum(int key) {
    switch (key) {
        case 'a':
        case 'A':
            return AUTO;
        case 'm':
        case 'M':
            return MANUAL;
        case 'c':
        case 'C':
            return CLOSE;
        case 'f':
        case 'F':
            return FAST;
        case 's':
        case 'S':
            return SLOW;
        case 'p':
        case 'P':
            return PREVIOUS;
        case 'n':
        case 'N':
            return NEXT;
        case 'd':
        case 'D':
            return DUMP;
        case 'r':
        case 'R':
            return RETURN;
        default:
            UNKNOWN;
    }
}

int getKeyInput() {
    while (kbhit()) {
        return getch();
    }
}

int getMainScreenSelection() {
    for (int key = getKeyInput();; key = getKeyInput()) {
        int selection = toSelectionEnum(key);
        if (selection == AUTO || selection == MANUAL || selection == CLOSE) {
            return selection;
        }
    }
}

int getManualScreenSelection() {
    for (int key = getKeyInput();; key = getKeyInput()) {
        int selection = toSelectionEnum(key);
        if (selection == PREVIOUS || selection == NEXT || selection == DUMP ||
            selection == RETURN) {
            return selection;
        }
    }
}

int (*userControlDevil)(char[GRID_WIDTH][GRID_HEIGHT], int, int);

void initSimulator(int (*controlDevil)(char[GRID_WIDTH][GRID_HEIGHT], int, int)) {
    init();
    userControlDevil = controlDevil;
}

int simulateProbability(int percent) {
    return rand() % 100 < percent;
}

int controlAngel(struct AngelProblem *angelProblem) {
    int x = angelProblem->angel.x;
    int y = angelProblem->angel.y;
    if (y == GRID_HEIGHT - 1) {
        return ESCAPE;
    }
    angelProblem->grid[x][y] = EMPTY_GLYPH;
    int xIxArr[3] = {x - 1, x, x + 1};
    int selXIxArr[3];
    int selXArrSize = 0;
    for (int i = 0; i < 3; i++) {
        if (0 <= xIxArr[i] && xIxArr[i] < GRID_WIDTH && angelProblem->grid[xIxArr[i]][y + 1] == EMPTY_GLYPH) {
            selXIxArr[selXArrSize++] = xIxArr[i];
        }
    }
    if (selXArrSize != 0) {
        int ix;
        switch (angelProblem->angelStrategy) {
            case CENTER:
                ix = rand() % selXArrSize;
                break;
            case LEFT:
                ix = simulateProbability(50) ? 0 : rand() % selXArrSize;
                break;
            case RIGHT:
                ix = simulateProbability(50) ? selXArrSize - 1 : rand() % selXArrSize;
                break;
        }
        int targetX = selXIxArr[ix];
        angelProblem->grid[targetX][y + 1] = ANGEL_GLYPH;
        angelProblem->angel.x = targetX;
        angelProblem->angel.y = y + 1;
        return MOVE;
    } else {
        angelProblem->grid[x][y] = ANGEL_GLYPH;
        return STUCK;
    }
}

int removeBlock(struct AngelProblem *angelProblem, int index) {
    int isValidRange = checkRange(index);
    if (!isValidRange) {
        return OUT_OF_RANGE;
    }
    struct Position targetPos = toPos(index);
    char glyph = angelProblem->grid[targetPos.x][targetPos.y];
    switch (glyph) {
        case REMOVED_BLOCK_GLYPH:
            return FAIL_BY_ALREADY_REMOVED_BLOCK;
        case ANGEL_GLYPH:
            return FAIL_BY_ANGEL_POSITION;
        case EMPTY_GLYPH:
            angelProblem->grid[targetPos.x][targetPos.y] = DEVIL_GLYPH;
            return SUCCESSFULLY_REMOVED;
    }
}

int controlUserDevil(struct AngelProblem *angelProblem) {
    if (angelProblem->turn != 0 && checkRange(toIndexByPos(&angelProblem->devil))) {
        angelProblem->grid[angelProblem->devil.x][angelProblem->devil.y] = REMOVED_BLOCK_GLYPH;
    }
    char copyGrid[GRID_WIDTH][GRID_HEIGHT];
    memcpy(copyGrid, angelProblem->grid, sizeof(copyGrid));
    angelProblem->devil = toPos(
            angelProblem->controlDevil(copyGrid, toIndexByPos(&angelProblem->angel), angelProblem->turn));
    return removeBlock(angelProblem, toIndexByPos(&angelProblem->devil));
}

void dump(char *fileName, char bufArr[GRID_HEIGHT][BUFFER_SIZE], int size) {
    FILE *fp = fopen(fileName, "w");
    for (int i = 0; i < size; i++) {
        fputs(bufArr[i], fp);
        fputs("\n", fp);
    }
    fclose(fp);
}

char *generateDumpFileName() {
    char *fileName = malloc(sizeof(char) * BUFFER_SIZE);
    time_t currentTime = time(NULL);
    struct tm t1 = *localtime(&currentTime);
    struct timespec t2;
    clock_gettime(CLOCK_MONOTONIC, &t2);

    sprintf(fileName, "%d-%d-%d%d.H%dM%dS.%lf.txt",
            t1.tm_year + 1900, t1.tm_mon + 1, t1.tm_mday,
            t1.tm_hour, t1.tm_min, t1.tm_sec, ((double) t2.tv_sec + 1.0e-9 * t2.tv_nsec));
    return fileName;
}


struct AngelProblem *simulate() {
    struct AngelProblem *angelProblem = malloc(sizeof(struct AngelProblem));
    initGrid(angelProblem->grid);
    angelProblem->turn = 0;
    angelProblem->readyToEnd = false;
    angelProblem->angel = toPos(toIndex(GRID_WIDTH / 2, 0));
    angelProblem->angelStrategy = angleStrategyArray[rand() % sizeof(angleStrategyArray) / sizeof(int)];
    angelProblem->devil = (struct Position) {-1, -1};
    angelProblem->grid[angelProblem->angel.x][angelProblem->angel.y] = ANGEL_GLYPH;
    angelProblem->resultIndex = 0;
    angelProblem->controlDevil = userControlDevil;

    while (true) {
        char buffer[BUFFER_SIZE] = {0,};
        printGridToBuffer(angelProblem->grid, buffer + strlen(buffer));
        sprintf(buffer + strlen(buffer), "Turn: %d \n", angelProblem->turn);
        if (angelProblem->readyToEnd) {
            sprintf(buffer + strlen(buffer), "Result: %s          \n",
                    angelProblem->lastAngelStatus == STUCK ? "WIN" : "LOSE");
            sprintf(buffer + strlen(buffer), "                                                  \n");
            memcpy(angelProblem->result[angelProblem->resultIndex++], buffer, strlen(buffer) + 1);
            break;
        }

        int angelStatus = controlAngel(angelProblem);
        if (angelStatus == MOVE) {
            sprintf(buffer + strlen(buffer), "NextAngel: MOVE(%d, %d)  \n", angelProblem->angel.x,
                    angelProblem->angel.y);
        } else if (angelStatus == ESCAPE) {
            sprintf(buffer + strlen(buffer), "NextAngel: ESCAPE        \n");
            angelProblem->readyToEnd = true;
            angelProblem->lastAngelStatus = angelStatus;
        } else if (angelStatus == STUCK) {
            sprintf(buffer + strlen(buffer), "NextAngel: STUCK         \n");
            angelProblem->readyToEnd = true;
            angelProblem->lastAngelStatus = angelStatus;
        }

        int devilStatus = controlUserDevil(angelProblem);
        if (devilStatus == SUCCESSFULLY_REMOVED) {
            sprintf(buffer + strlen(buffer), "NextDevil: SUCCESSFULLY_REMOVED(%d, %d)           \n",
                    angelProblem->devil.x,
                    angelProblem->devil.y);
        } else if (devilStatus == FAIL_BY_ALREADY_REMOVED_BLOCK) {
            sprintf(buffer + strlen(buffer), "NextDevil: FAIL_BY_ALREADY_REMOVED_BLOCK(%d, %d)  \n",
                    angelProblem->devil.x,
                    angelProblem->devil.y);
        } else if (devilStatus == FAIL_BY_ANGEL_POSITION) {
            sprintf(buffer + strlen(buffer), "NextDevil: FAIL_BY_ANGEL_POSITION(%d, %d)         \n",
                    angelProblem->devil.x,
                    angelProblem->devil.y);
        } else if (devilStatus == OUT_OF_RANGE) {
            sprintf(buffer + strlen(buffer), "NextDevil: OUT_OF_RANGE(%d, %d)                   \n",
                    angelProblem->devil.x,
                    angelProblem->devil.y);
        }
        angelProblem->turn++;
        memcpy(angelProblem->result[angelProblem->resultIndex++], buffer, strlen(buffer) + 1);
    }
    return angelProblem;
}


double speedRateArray[] = {0.001, 0.01, 0.02, 0.03, 0.04, 0.05, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1, 1.25,
                           1.5, 1.75,
                           2, 3, 4, 5, 10, 15, 20, 30, 40, 50, 75, 100};
int speedRateArraySize = sizeof(speedRateArray) / sizeof(double);
int speedRateIndex = 15;

int handleKey(int selection) {
    switch (selection) {
        case FAST:
            if (speedRateIndex + 1 < speedRateArraySize) {
                speedRateIndex++;
            }
            gotoxy(0, GRID_HEIGHT + 5);
            printf("Speed: %.3lfx     ", speedRateArray[speedRateIndex]);
            break;
        case SLOW:
            if (speedRateIndex - 1 >= 0) {
                speedRateIndex--;
            }
            gotoxy(0, GRID_HEIGHT + 5);
            printf("Speed: %.3lfx     ", speedRateArray[speedRateIndex]);
            break;
        case RETURN:
            return RETURN;
    }
}

int waitWithKeyHandling(unsigned long ms) {
    struct timespec begin, end;
    clock_gettime(CLOCK_MONOTONIC, &begin);
    while (true) {
        wait(UNIT_WAIT);
        if (kbhit()) {
            return handleKey(toSelectionEnum(getch()));
        }
        clock_gettime(CLOCK_MONOTONIC, &end);
        if (millisecondDiff(begin, end) >= ms) {
            return UNKNOWN;
        }
    }
}

void runAuto() {
    int winCount = 0;
    int totalCount = 0;

    clear();
    gotoxy(0, GRID_HEIGHT + 4);
    printf("Total: %d, Win: %d, Lose %d         \n", totalCount, winCount, totalCount - winCount);
    gotoxy(0, GRID_HEIGHT + 5);
    printf("(s)low <-> (f)ast");
    gotoxy(0, GRID_HEIGHT + 6);
    printf("(r)eturn to the main screen");
    while (true) {
        gotoxy(0, GRID_HEIGHT + 7);
        struct AngelProblem *angelProblem = simulate();
        for (int i = 0; i < angelProblem->resultIndex; i++) {
            gotoxy(0, 0);
            printf("%s", angelProblem->result[i]);
            gotoxy(0, GRID_HEIGHT + 7);
            if (waitWithKeyHandling((unsigned long) (WAIT_TURN * 1 / speedRateArray[speedRateIndex])) == RETURN) {
                return;
            }
        }
        winCount += angelProblem->lastAngelStatus == STUCK ? 1 : 0;
        totalCount++;
        if (angelProblem->lastAngelStatus == ESCAPE) {
            gotoxy(0, GRID_HEIGHT + 7);
            char *fileName = generateDumpFileName();
            dump(fileName, angelProblem->result, angelProblem->resultIndex);
            printf("EscapeDump: %s\n", fileName);
            free(fileName);
        }
        gotoxy(0, GRID_HEIGHT + 4);
        printf("Total: %d, Win: %d, Lose %d         \n", totalCount, winCount, totalCount - winCount);
        gotoxy(0, GRID_HEIGHT + 7);
        if (waitWithKeyHandling((unsigned long) (WAIT_EVENT * 1 / speedRateArray[speedRateIndex])) == RETURN) {
            return;
        }
        free(angelProblem);
    }
}

void runManual() {
    clear();
    struct AngelProblem *angelProblem = simulate();
    int currentIndex = 0;
    while (true) {
        gotoxy(0, 0);
        printf("%s", angelProblem->result[currentIndex]);
        printf("(p)revious <-> (n)ext / (d)ump\n");
        printf("(r)eturn to the main screen\n");
        int manualSelection = getManualScreenSelection();
        char *fileName;
        switch (manualSelection) {
            case PREVIOUS:
                if (currentIndex > 0) {
                    currentIndex--;
                }
                break;
            case NEXT:
                if (currentIndex < angelProblem->resultIndex - 1) {
                    currentIndex++;
                }
                break;
            case DUMP:
                gotoxy(0, GRID_HEIGHT + 6);
                fileName = generateDumpFileName();
                dump(fileName, angelProblem->result, angelProblem->resultIndex);
                printf("Dump: %s\n", fileName);
                free(fileName);
                break;
            case RETURN:
                free(angelProblem);
                return;
        }
    }
}


void runSimulator() {
    while (true) {
        clear();
        printMainScreen();
        int mainSelection = getMainScreenSelection();
        switch (mainSelection) {
            case AUTO:
                runAuto();
                break;
            case MANUAL:
                runManual();
                break;
            case CLOSE:
                exit(0);
        }
    }
}
