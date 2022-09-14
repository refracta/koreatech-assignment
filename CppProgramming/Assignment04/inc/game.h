#ifndef GAME_H
#define GAME_H

#include "interfaceutils.h"
#include "colortextutils.h"
#include "asciiart.h"
#include "gamedata.h"
#include "systemutils.h"
#include "keycode.h"
#include "memoryutils.h"
#include "puzzle.h"
#include <stdlib.h>
#include <string.h>

#define DEFAULT_TBCOLOR TO_TBCOLOR(WHITE, BLACK)

typedef enum
{
    MM_GAME_NUMBER, MM_GAME_KORYONGI, MM_GAME_LENA, MM_LOAD, MM_RANKING, MM_EXIT
} MainMenu;

class Game {
public:
    void start();

private:
    BufferingManager& bm = BufferingManager::instance();

    static int handle_game_key(int c, void * param);
    void init_game();
    MainMenu run_main_menu();
    void game_loop(GameData *data);
    void change_status(GameData *data, GameStatus status);
    void run_main(GameData *data);
    void run_game(GameData *data);
    void run_ranking(GameData *data);
    void run_replay(GameData *data);
    void draw_complete_puzzle(GameData *data);
    void draw_puzzle(GameData *data);
    void draw_number_block(int cursor_x, int cursor_y, int number);
    void shuffle_with_draw(GameData *data);
    void run_player_name_prompt(GameData *data);
};


#endif
