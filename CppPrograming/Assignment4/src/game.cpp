#include "game.h"

void Game::start() {
    init_game();
    GameData data;
    change_status(&data, GS_MAIN);
    while (true) {
        game_loop(&data);
    }
}

int Game::handle_game_key(int c, void *param) {
    void **list = (void **) param;
    Game *game = (Game *) list[0];
    GameData *data = (GameData *) list[1];
    switch (c) {
        case UP_KEY:
            if (data->puzzle.move(UP)) {
                memcpy(data->save.current_map, data->puzzle.map, sizeof(int) * DIM * DIM);
                data->save.move_log[data->save.move++] = L'U';
                PLAY_SELECTION_SOUND1();
            } else {
                PLAY_FAIL_SOUND();
            }
            break;
        case DOWN_KEY:
            if (data->puzzle.move(DOWN)) {
                memcpy(data->save.current_map, data->puzzle.map, sizeof(int) * DIM * DIM);
                data->save.move_log[data->save.move++] = L'D';
                PLAY_SELECTION_SOUND1();
            } else {
                PLAY_FAIL_SOUND();
            }
            break;
        case RIGHT_KEY:
            if (data->puzzle.move(RIGHT)) {
                memcpy(data->save.current_map, data->puzzle.map, sizeof(int) * DIM * DIM);
                data->save.move_log[data->save.move++] = L'R';
                PLAY_SELECTION_SOUND1();
            } else {
                PLAY_FAIL_SOUND();
            }
            break;
        case LEFT_KEY:
            if (data->puzzle.move(LEFT)) {
                memcpy(data->save.current_map, data->puzzle.map, sizeof(int) * DIM * DIM);
                data->save.move_log[data->save.move++] = L'L';
                PLAY_SELECTION_SOUND1();
            } else {
                PLAY_FAIL_SOUND();
            }
            break;
        case ESCAPE_KEY:
            data->save.move_log[data->save.move] = L'\0';
            PLAY_EXIT_SOUND();
            return HANDLE_SAVE_AND_EXIT;
    }
    game->draw_puzzle(data);
    game->bm.draw();
    if (data->puzzle.is_done()) {
        return HANDLE_GAME_DONE;
    }
    return HANDLE_NULL;
}

void Game::init_game() {
    ConsoleUtils::set_encoding_utf8();
    ConsoleUtils::set_console_title(u8"Fifteen Puzzle");
    ConsoleUtils::set_default_mode();
    ConsoleUtils::set_cursor_visibility(false);
    ConsoleUtils::set_console_size(CONSOLE_COLS, CONSOLE_LINES);
    bm.init(CONSOLE_COLS, CONSOLE_LINES);
    bm.set_cursor_visibility(false);
    srand(time(NULL));
}

MainMenu Game::run_main_menu() {
    MenuData menu;
    menu.name = L"      메뉴";
    wchar_t **list = (wchar_t **) malloc(sizeof(wchar_t *) * 6);
    list[0] = L"게임 시작 (숫자)";
    list[1] = L"게임 시작 (코룡)";
    list[2] = L"게임 시작 (레나)";
    list[3] = L"    불러오기";
    list[4] = L" 랭킹 (리플레이)";
    list[5] = L"     나가기";
    menu.list = list;
    menu.length = 6;
    menu.current_index = 0;

    menu.element_tbcolor = TO_TBCOLOR(BLUE, RED);
    menu.name_tbcolor = TO_TBCOLOR(WHITE, BLACK);
    menu.outline_tbcolor = TO_TBCOLOR(GRAY, BLACK);
    menu.selected_tbcolor = TO_TBCOLOR(LIGHT_JADE, LIGHT_PURPLE);
    menu.non_selected_tbcolor = TO_TBCOLOR(WHITE, GRAY);

    menu.x = 30;
    menu.y = 10;

    int index = InterfaceUtils::run_menu(&menu, true);
    free(list);
    return (MainMenu) index;
}

void Game::game_loop(GameData *data) {
    switch (data->status) {
        case GS_MAIN:
            run_main(data);
            break;
        case GS_GAME:
            run_game(data);
            break;
        case GS_RANKING:
            run_ranking(data);
            break;
    }
}

void Game::change_status(GameData *data, GameStatus status) {
    data->status = status;
    bm.set_print_color(DEFAULT_TBCOLOR);
    bm.clear();
}

void Game::run_main(GameData *data) {
    GameSave empty_save;
    empty_save.move = 0;
    empty_save.time = 0.;
    empty_save.is_loaded_save = false;

    data->save = empty_save;
    FILE *fp;
    switch (run_main_menu()) {
        case MM_GAME_NUMBER:
            data->save.render_type = RT_NUMBER;
            change_status(data, GS_GAME);
            break;
        case MM_GAME_KORYONGI:
            data->save.render_type = RT_ASCIIART;
            data->save.asciiart_type = AAT_KORYONGI;
            change_status(data, GS_GAME);
            break;
        case MM_GAME_LENA:
            data->save.render_type = RT_ASCIIART;
            data->save.asciiart_type = AAT_LENA;
            change_status(data, GS_GAME);
            break;
        case MM_LOAD:
            fp = fopen("save.bin", "rb");
            if (fp != NULL) {
                fread(&data->save, sizeof(GameSave), 1, fp);
                fclose(fp);
                data->save.is_loaded_save = true;
                remove("save.bin");
                change_status(data, GS_GAME);
            } else {
                PLAY_FAIL_SOUND();
            }
            break;
        case MM_RANKING:
            fp = fopen("ranking.bin", "rb");
            if (fp != NULL) {
                fclose(fp);
                change_status(data, GS_RANKING);
            } else {
                PLAY_FAIL_SOUND();
            }
            break;
        case MM_EXIT:
            exit(0);
            break;
    }
}

void Game::run_game(GameData *data) {
    if (!data->save.is_loaded_save) {
        run_player_name_prompt(data);
        bm.clear();
        draw_complete_puzzle(data);
        data->puzzle.init_puzzle();
        bm.xywprintf(40, 0, L"Name:%s", data->save.player_name);
        bm.xywprintf(60, 27, L"ESC: Save & Return to Menu");
        bm.xywprintf(40, 27, L"Time: %.1lfs", 0);
        bm.xywprintf(40, 28, L"Move: %d", 0);
        shuffle_with_draw(data);
    } else {
        draw_complete_puzzle(data);
        memcpy(data->puzzle.map, data->save.current_map, sizeof(int) * DIM * DIM);
        bm.xywprintf(40, 0, L"Name:%s", data->save.player_name);
        bm.xywprintf(60, 27, L"ESC: Save & Return to Menu");
        bm.xywprintf(40, 27, L"Time: %.1lfs", 0);
        bm.xywprintf(40, 28, L"Move: %d", 0);
        draw_puzzle(data);
    }

    void *param[] = {this, data};
    struct timespec begin, end;
    SystemUtils::clock_gettime(CLOCK_MONOTONIC, &begin);
    while (true) {
        int handle_code = ConsoleUtils::wait_with_handler(10, handle_game_key, param);
        SystemUtils::clock_gettime(CLOCK_MONOTONIC, &end);
        double diff = MILLISECOND_DIFF(begin, end) / 1000.0;
        if (handle_code == HANDLE_NULL) {
            bm.xywprintf(40, 27, L"Time: %.1lfs", diff + data->save.time);
            bm.xywprintf(40, 28, L"Move: %d", data->save.move);
            bm.draw();
        } else if (handle_code == HANDLE_GAME_DONE || handle_code == HANDLE_SAVE_AND_EXIT) {
            data->save.time += diff;
            if (handle_code == HANDLE_GAME_DONE) {
                bm.xywprintf(40, 27, L"Time: %.1lfs", data->save.time);
                bm.xywprintf(40, 28, L"Move: %d", data->save.move);
                bm.xywprintf(43, 26, L"WIN!             Any Key: Return to Menu");
                bm.draw();
                PLAY_VICTORY_FANFARE();
                ConsoleUtils::get_key_input();
                RankingData ranking_data;
                FILE *fp = fopen("ranking.bin", "rb");
                if (fp != NULL) {
                    fread(&ranking_data, sizeof(RankingData), 1, fp);
                    fclose(fp);
                } else {
                    ranking_data.last_index = 0;
                }

                if (ranking_data.last_index < 10) {
                    ranking_data.list[ranking_data.last_index++] = data->save;
                } else {
                    if (ranking_data.list[ranking_data.last_index - 1].time > data->save.time) {
                        ranking_data.list[ranking_data.last_index - 1] = data->save;
                    }
                }

                GameSave temp;
                for (int i = 0; i < ranking_data.last_index; i++) {
                    for (int j = 0; j < ranking_data.last_index - 1; j++) {
                        if (ranking_data.list[j].time >
                            ranking_data.list[j + 1].time) {
                            temp = ranking_data.list[j];
                            ranking_data.list[j] = ranking_data.list[j + 1];
                            ranking_data.list[j + 1] = temp;
                        }
                    }
                }

                fp = fopen("ranking.bin", "wb");
                fwrite(&ranking_data, sizeof(RankingData), 1, fp);
                fclose(fp);
            } else if (handle_code == HANDLE_SAVE_AND_EXIT) {
                FILE *fp = fopen("save.bin", "wb");
                fwrite(&data->save, sizeof(GameSave), 1, fp);
                fclose(fp);
            }
            change_status(data, GS_MAIN);
            break;
        }
    }
}

void Game::run_replay(GameData *data) {
    draw_complete_puzzle(data);
    memcpy(data->puzzle.map, data->save.map, sizeof(int) * DIM * DIM);
    draw_puzzle(data);
    int move = 0;
    bm.xywprintf(40, 27, L"Time: %.1lfs", data->save.time);
    bm.xywprintf(60, 27, L"ESC: Return to Menu");
    bm.xywprintf(40, 28, L"Move: %d/%d (←, →)", move, data->save.move);
    bm.xywprintf(40, 0, L"Name:%s (Replay)", data->save.player_name);
    bm.draw();
    while (true) {
        switch (ConsoleUtils::get_key_input()) {
            case RIGHT_KEY:
                if (move < data->save.move) {
                    data->puzzle.move(TO_PUZZLE_DIRECTION(data->save.move_log[move]));
                    move++;
                    PLAY_SELECTION_SOUND1();
                }
                bm.xywprintf(40, 28, L"Move: %d/%d (←, →)      ", move, data->save.move);
                break;
            case LEFT_KEY:
                if (move > 0) {
                    move--;
                    data->puzzle.move(TO_REVERSE_PUZZLE_DIRECTION(data->save.move_log[move]));
                    PLAY_SELECTION_SOUND1();
                }
                bm.xywprintf(40, 28, L"Move: %d/%d (←, →)      ", move, data->save.move);
                break;
            case ESCAPE_KEY:
                PLAY_EXIT_SOUND();
                change_status(data, GS_RANKING);
                return;
        }
        draw_puzzle(data);
        bm.draw();
    }
}

void Game::run_ranking(GameData *data) {
    FILE *fp = fopen("ranking.bin", "rb");
    RankingData ranking_data;
    fread(&ranking_data, sizeof(RankingData), 1, fp);
    fclose(fp);

    MenuData menu;
    menu.name = L"    랭킹 (리플레이)";
    wchar_t **list = (wchar_t **) MemoryUtils::malloc_double_pointer(sizeof(wchar_t), ranking_data.last_index, BUFSIZ);

    for (int i = 0; i < ranking_data.last_index; i++) {
        GameSave s = ranking_data.list[i];
        swprintf(list[i], BUFSIZ, L"%2d위 %s %.1lf초", i + 1, s.player_name, s.time);
    }

    menu.list = list;
    menu.length = ranking_data.last_index;
    menu.current_index = 0;

    menu.element_tbcolor = TO_TBCOLOR(BLUE, RED);
    menu.name_tbcolor = TO_TBCOLOR(WHITE, BLACK);
    menu.outline_tbcolor = TO_TBCOLOR(GRAY, BLACK);
    menu.selected_tbcolor = TO_TBCOLOR(LIGHT_RED, LIGHT_GREEN);
    menu.non_selected_tbcolor = TO_TBCOLOR(WHITE, GRAY);

    menu.x = 27;
    menu.y = 8;

    int index = InterfaceUtils::run_menu(&menu, false);
    MemoryUtils::free_double_pointer((void **) list, ranking_data.last_index);
    if (index == -1) {
        PLAY_EXIT_SOUND();
        change_status(data, GS_MAIN);
    } else {
        data->save = ranking_data.list[index];
        bm.clear();
        run_replay(data);
    }
}

void Game::draw_complete_puzzle(GameData *data) {
    int cursor_x = CONSOLE_COLS - ASCIIART_WIDTH - 4;
    int cursor_y = 2;
    switch (data->save.render_type) {
        case RT_NUMBER:
            for (int y = 0; y < DIM; y++) {
                for (int x = 0; x < DIM; x++) {
                    int number = x + y * DIM;
                    if (number != END_PUZZLE_INDEX) {
                        draw_number_block(cursor_x + x * 10, cursor_y + y * 6, number);
                    }
                }
            }
            break;
        case RT_ASCIIART:
            ColorTextUtils::draw_color_text(cursor_x, cursor_y, 0, 0, ASCIIART_WIDTH, ASCIIART_HEIGHT,
                                            TO_ASCIIART_VALUE(data->save.asciiart_type), ASCIIART_WIDTH,
                                            ASCIIART_HEIGHT);
            break;
    }
}

void Game::draw_puzzle(GameData *data) {
    int cursor_x = 4;
    int cursor_y = 2;
    for (int y = 0; y < DIM; y++) {
        for (int x = 0; x < DIM; x++) {
            int number = data->puzzle.map[x][y];
            if (number != END_PUZZLE_INDEX) {
                if (data->save.render_type == RT_NUMBER) {
                    draw_number_block(cursor_x + x * 10, cursor_y + y * 6, number);
                } else if (data->save.render_type == RT_ASCIIART) {
                    ColorTextUtils::draw_color_text(cursor_x + x * 10, cursor_y + y * 6, (number % DIM) * 10,
                                                    (number / DIM) * 6, 10, 6,
                                                    TO_ASCIIART_VALUE(data->save.asciiart_type), ASCIIART_WIDTH,
                                                    ASCIIART_HEIGHT);
                }
            } else {
                draw_number_block(cursor_x + x * 10, cursor_y + y * 6, END_PUZZLE_INDEX);
            }
        }
    }
}

void Game::draw_number_block(int cursor_x, int cursor_y, int number) {
    short color = bm.get_print_color();
    bm.set_print_color(TO_TBCOLOR((number + 1) % 16, (number + 1) % 16));
    bm.xywprintf(cursor_x, cursor_y,
                 L"          \n" L"          \n" L"          \n" L"          \n" L"          \n" L"          ");
    bm.set_print_color(TO_TBCOLOR((number + 15) % 16, (number + 1) % 16));
    if (number != END_PUZZLE_INDEX) {
        bm.xywprintf(cursor_x + 4, cursor_y + 2, L"%2d", number + 1);
    }
    bm.set_print_color(color);
}

void Game::shuffle_with_draw(GameData *data) {
    ConsoleUtils::set_console_title("Fifteen Puzzle (Shuffle)");
    for (int i = 0; i < 100; i++) {
        data->puzzle.shuffle_once();
        SystemUtils::wait(10);
        draw_puzzle(data);
        bm.draw();
    }
    memcpy(data->save.map, data->puzzle.map, sizeof(int) * DIM * DIM);
    memcpy(data->save.current_map, data->puzzle.map, sizeof(int) * DIM * DIM);
    ConsoleUtils::set_console_title("Fifteen Puzzle");
}

void Game::run_player_name_prompt(GameData *data) {
    PromptData prompt;
    prompt.message = L"플레이어의 이름을 입력하세요";
    prompt.x = 26;
    prompt.y = 13;
    prompt.rlen = 12;
    prompt.outline_tbcolor = TO_TBCOLOR(LIGHT_JADE, BLACK);
    prompt.text_tbcolor = TO_TBCOLOR(LIGHT_JADE, BLACK);
    prompt.message_tbcolor = TO_TBCOLOR(BLACK, WHITE);
    wchar_t *player_name = InterfaceUtils::run_prompt(&prompt);
    wcscpy(data->save.player_name, player_name);
    free(player_name);
}
