#include <stdlib.h>
#include "board.h"

//Create board and allocate memory
Board* create_board(int height, int width){
    Board* board = (Board*)malloc(sizeof(Board));
    if(board == NULL){
        return NULL;
    }
    
    board->width = width;
    board->height = height;

    board->cells = (int**)malloc(height * sizeof(int*));
    for(int i = 0; i < height; i++){
        board->cells[i] = (int*)malloc(width * sizeof(int));
    }

    init_board(board);
    return board;
}

//Initialize all cells to zero
void init_board(Board* board){
    for(int r = 0; r < board->height; r++){
        for(int c = 0; c < board->width; c++){
            board->cells[r][c] = 0;
        }
    }
}

//Check the next generation at cell r,c
int next_gen(int** cells, int r, int c, int height, int width){
    //Count neighbors
    int neighbors = 0;
    for(int x = -1; x <= 1; x++){
        for(int y = -1; y <= 1; y++){
            if(!(c + x < 0 || c + x >= width || r + y < 0 || r + y >= height)){
                if(x != 0 || y != 0){
                    if(cells[r + y][c + x]){
                        neighbors++;
                    }
                }
            }
        }
    }
    
    //Apply logic for if a cell is alive or not
    if(cells[r][c]){
        if(neighbors < 2 || neighbors > 3){
            return 0;
        }
        else{
            return 1;
        }
    }
    else{
        if(neighbors == 3){
            return 1;
        }
        return 0;
    }
}

//Update all cells in the board
void update_board(Board* board){
    int height = board->height;
    int width = board->width;
    int tempCells[height][width];

    //Apply next generation logic to the cells
    for(int r = 0; r < height; r++){
        for(int c = 0; c < width; c++){
            tempCells[r][c] = next_gen(board->cells, r, c, height, width);
        }
    }
    
    //Copy temp cells back to board cells
    for(int r = 0; r < height; r++){
        for(int c = 0; c < width; c++){
            board->cells[r][c] = tempCells[r][c];
        }
    }
}

void print_board(Board* board){
    for(int r = 0; r < board->height; r++){
        for(int c = 0; c < board->width; c++){
            printf("%d ", board->cells[r][c]);
        }
        printf("\n");
    }
}


//Draws rectangles for all the cells in the board
void render_board(Board* board, SDL_Renderer* renderer, SDL_Window* window){
    int width = 0;
    int height = 0;

    SDL_GetRendererOutputSize(renderer, &width, &height);

    int cellWidth =  width / board->width;
    int cellHeight = height / board->height;

    for(int r = 0; r < board->height; r++){
        for(int c = 0; c < board->width; c++){
            SDL_Rect rect;
            rect.w = cellWidth;
            rect.h = cellHeight;
            rect.x = c * cellWidth;
            rect.y = r * cellHeight;
            if(board->cells[r][c]){
                SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
            }
            else{
                SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
            }
            SDL_RenderFillRect(renderer, &rect);
            SDL_RenderDrawRect(renderer, &rect);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderDrawRect(renderer, &rect);
        }
    }
}

//Toggle the state of the square at the mouse coordinates
void toggle_square(Board* board, SDL_Renderer* renderer, int mouseX, int mouseY){
    int width = 0;
    int height = 0;

    SDL_GetRendererOutputSize(renderer, &width, &height);

    int x = ((double)mouseX / width) * board->width;
    int y = ((double)mouseY / height) * board->height;

    board->cells[y][x] = !board->cells[y][x];
}

void set_cell(Board* board, int x, int y, int value){
    board->cells[x][y] = value;
}

int get_cell(Board* board, int x, int y){
    return board->cells[x][y];
}

//Free the memory allocated for the board
void cleanup_board(Board* board){
    for(int i = 0; i < board->height; i++){
        free(board->cells[i]);
    }
    free(board->cells);
    free(board);
}
