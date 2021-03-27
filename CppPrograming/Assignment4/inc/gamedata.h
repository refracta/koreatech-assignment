/**
 @file gamedata.h
 @brief 게임에서 사용되는 구조체, 상수, 데이터, 유틸 매크로등이 정의된 헤더 파일
*/
#ifndef GAMEDATA_H
#define GAMEDATA_H


#include "puzzle.h"

#define HANDLE_NULL -1
#define HANDLE_GAME_DONE 0
#define HANDLE_SAVE_AND_EXIT 1

/**
 * @brief 게임이 가지는 상황 열거형
 */
typedef enum {
    GS_MAIN, GS_GAME, GS_RANKING
} GameStatus;

typedef enum {
    RT_NUMBER, RT_ASCIIART
} RenderType;

/**
 * @brief 게임에서 사용하는 데이터들을 포함하는 구조체
 */
typedef struct {
    wchar_t player_name[BUFSIZ];
    char move_log[BUFSIZ * 100];
    int move;
    double time;
    RenderType render_type;
    ASCIIArtType asciiart_type;
    int map[DIM][DIM];
    int current_map[DIM][DIM];
    bool is_loaded_save;
} GameSave;

/**
 * @brief 게임에서 사용하는 데이터들을 포함하는 구조체
 */
typedef struct {
    GameSave list[10];
    int last_index;
} RankingData;

/**
 * @brief 게임에서 사용하는 데이터들을 포함하는 구조체
 */
typedef struct {
    GameStatus status;
    Puzzle puzzle;
    GameSave save;
} GameData;

#endif