#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <iostream>
#include "raster.h"
#include <SDL2/SDL.h>

#define WIDTH_SCREEN 600
#define HEIGHT_SCREEN 480

bool start();
void close();

SDL_Window *win  = nullptr;
SDL_Surface *sur = nullptr;
SDL_Renderer *ren = nullptr;


int main(int argc, char* args[]) {
     if (!start()){
        std::cerr << "Initilization ERROR\n";
        return 1;  
    } 

    SDL_Event e;
    bool quit = false;

    Raster ras;

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } 
        }
    point p1 = {0,0};
    point p2 = {100,100, 1};
    point p3 = {300, 250, 0.5};
    point p4 = {150, 200,0.25};
    SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
    SDL_RenderClear(ren);
    // ras.drawWireTriangle(p2, p3, p4, {255,255,255}, ren);
    ras.fillInTriangle(p2, p3, p4, {255,0,0}, ren);

    SDL_RenderPresent(ren);

    }
}






bool start() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "ERROR: " << SDL_GetError() << "\n";
        return false;
    }
    win = SDL_CreateWindow("Ray Caster", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                             WIDTH_SCREEN, HEIGHT_SCREEN, SDL_WINDOW_SHOWN);
    if (!win) {
        std::cerr << "ERROR: " << SDL_GetError() << "\n";
        return false;
    }
    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!ren) {
        std::cerr << "ERROR: " << SDL_GetError() << "\n";
        return false;
    }
    return true;
}

void close() {
    SDL_FreeSurface(sur);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
