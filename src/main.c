#include <SDL2/SDL.h>
#include "board.h"

int main(){
    Board* board = create_board(10, 10);
    if(board == NULL){
        printf("Board failed to allocate");
        return 1;
    }
    set_cell(board, 1, 1, 1);
    set_cell(board, 1, 2, 1);
    set_cell(board, 1, 3, 1);


    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("Failed to initialize video");
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Conway's Game of Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 480, 480, SDL_WINDOW_SHOWN);
    if(!window){
        printf("Failed to initialize window");
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer){
        printf("Failed to initialize renderer");
        SDL_Quit();
        return 1;
    }

    //print_board(board);
    //printf("\n");
    //update_board(board);
    //print_board(board);

    SDL_Event event;
    int running = 1;

    while(running){
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                running = 0;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        
        render_board(board, renderer, window);
        
        update_board(board);

        SDL_RenderPresent(renderer);
    }

    cleanup_board(board);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}