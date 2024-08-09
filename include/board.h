#ifndef BOARD_H
#define BOARD_H

#include <SDL2/SDL.h>

typedef struct {
    int** cells;
    int width;
    int height;
} Board;

Board* create_board(int width, int height);
void init_board(Board* board);
void update_board(Board * board);
void render_board(Board* board, SDL_Renderer* renderer);
void print_board(Board* board);
void toggle_square(Board* board, SDL_Renderer* renderer, int mouseX, int mouseY);
void set_cell(Board* board, int x, int y, int value);
int get_cell(Board* board, int x, int y);
void cleanup_board(Board* board);

#endif