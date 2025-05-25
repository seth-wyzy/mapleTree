#include "camera.h"
#include "SDL_render.h"
#include "objects.h"
#include "raster.h"
#include <iostream>
#include <array>

std::array<double, 3> camera::takeInput(const SDL_Event e){
    std::array<double, 3> transOut{0,0,0};
     if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
            case SDLK_w: 
                transOut[2] = -1;
                std::cout<< "w Pressed, trying forward" << std::endl;
                return transOut;
            case SDLK_d:
                transOut[0] = -1;
                 std::cout<< "d Pressed, trying forward" << std::endl;
                return transOut;
            case SDLK_s:
                transOut[2] = 1;
                std::cout <<"s pressed, trying backwards" << std::endl;
                return transOut;
            case SDLK_a: 
                transOut[0] = 1;
                std::cout << "a pressed, tyring backwards" << std::endl;
                return transOut;
            default:
                return transOut;
        }
    }
    return transOut;
}


void camera::handleTransform(const SDL_Event e, Raster& ras, std::vector<cube*> scene, SDL_Renderer* ren) {
    std::array<double, 3> trans = takeInput(e);
    SDL_SetRenderDrawColor(ren, 255,255, 255, 255);
    SDL_RenderClear(ren);
    ras.updateScene(scene, ren, trans);
    SDL_RenderPresent(ren);
}

void camera::handleMotion(const int dx, Raster& ras, std::vector<cube*> scene, SDL_Renderer* ren){
    const float sensitivity = -0.005;
    double rotate = dx * sensitivity;
    SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
    SDL_RenderClear(ren);
    ras.updateScene(scene, ren, {0,0,0}, rotate);
    SDL_RenderPresent(ren); 
}

