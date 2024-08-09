#include <SDL2/SDL.h>
#include <time.h>
#include "board.h"

int main(){
    //Create and initialize board
    Board* board = create_board(20, 20);
    if(board == NULL){
        printf("Board failed to allocate");
        return 1;
    }
    set_cell(board, 1, 1, 1);
    set_cell(board, 1, 2, 1);
    set_cell(board, 1, 3, 1);

    //Initialize SDL video, window, and renderer
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("Failed to initialize video");
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Conway's Game of Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
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

    //Initialize variables used for the main loop and fps
    SDL_Event event;
    int running = 1;
    int isBoardRunning = 0;

    //Main loop
    while(running){
        //Check events
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT: running = 0; 
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if(event.button.button == SDL_BUTTON_LEFT){
                        int x;
                        int y;
                        SDL_GetMouseState(&x, &y);
                        toggle_square(board, renderer, x, y);
                    }
                    break;
                case SDL_KEYDOWN:
                    if(event.key.keysym.sym == SDLK_r) isBoardRunning = !isBoardRunning;
                    if(event.key.keysym.sym == SDLK_q) running = 0;
            }
        }

        //Render everything
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        if(isBoardRunning){
            update_board(board);
        }

        render_board(board, renderer);
        SDL_Delay(100);
        
        SDL_RenderPresent(renderer);
    }

    //Clean up allocated objects
    cleanup_board(board);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}