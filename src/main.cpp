#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <cmath>
#include <iostream>

#include "raster.h"
#include "camera.h"
#include <SDL2/SDL.h>
#include <vector>
#include "objects.h"
#include "load.h"



bool start();
void close(std::vector<cube*> fullScene);

SDL_Window *win  = nullptr;
SDL_Surface *sur = nullptr;
SDL_Renderer *ren = nullptr;
//TODO: Why isn't the mouse being hidden on ROG?
// ! Kinda feels like an issue
// ? Why isn't it working? 
// I like the comment colors

int main(int argc, char* args[]) {
     if (!start()){
        std::cerr << "Initilization ERROR\n";
        return 1;  
    } 

    SDL_RaiseWindow(win);                           
    SDL_ShowCursor(SDL_DISABLE);
    SDL_SetRelativeMouseMode(SDL_TRUE);
    SDL_SetWindowGrab(win, SDL_TRUE);
    if (SDL_CaptureMouse(SDL_TRUE) < 0) {
        std::cerr << "Mouse capture failed: " << SDL_GetError() << "\n";
    }
    // Initillize stuff
    SDL_Event e;
    bool quit = false;
    std::array<double, 3> currVel {0,0,0};
    Raster ras;
    camera cam {0,0,0};
    Loader load;
    
    
    // TODO add the fulcrum planes or whatever they are called  // todone i think
    // Plane nearPlane(0,0,-1,-DISTANCE);
    // Plane farPlane(0,0,1,-FARDISTANCE);
    // double fovRad = FOVDEGREES * M_PI /180.0;
    // double halfWidth = DISTANCE* tan(fovRad/2.0);
    // double leftNormalZ = -halfWidth / DISTANCE;
    // Plane leftPlane(1,0,leftNormalZ, 0);
    // Plane rightPlane(-1,0,leftNormalZ, 0);

    // ? This is really weird, it like seems like the camera might be in the -z direction kinda
    Plane nearPlane(0, 0, 1, DISTANCE);      
    Plane farPlane(0, 0, -1, FARDISTANCE);       

    double fovRad = FOVDEGREES * M_PI / 180.0;
    double halfWidth = DISTANCE * tan(fovRad / 2.0);
    double leftNormalZ = halfWidth / DISTANCE;
    Plane leftPlane(1, 0, leftNormalZ, 0);    
    Plane rightPlane(-1, 0, leftNormalZ, 0);  
    
    objects obj;
    obj.planes = {nearPlane, farPlane, leftPlane, rightPlane};
    SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
    SDL_RenderClear(ren);
    if (argc == 1) {
        // cube *cube1 = new cube(-1.5, 0, -7,1,1,1,PI/4);
        // cube *cube2 = new cube(1,1.2, -9,1,1,1,PI/4);
        
        // obj.scene.push_back(cube1);
        // obj.scene.push_back(cube2);
        // cube2->transform({-1.5, 0, 7});
        // cube2->transform({-1,-1,-1});
        // cube2->scale({2,1,1});
        // ras.renderScene(obj.scene, ren, obj.planes);

        // SDL_RenderPresent(ren);
    } else if (argc == 2) {
        load.loadFromFile(args[1], obj.scene);
    } 

    while (!quit) {
       
        while (SDL_PollEvent(&e)) { //FIXME make this work so that keys being held down are smoother
            if (e.type == SDL_QUIT || e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
                quit = true;
            } else if (e.type == SDL_KEYDOWN) {
                cam.updateVelocity(e, ras, obj.scene, ren, currVel);
            }
        }
    
    int dx,dy;// FIXME: Fix acceleration and velocity to work at different framerates
    SDL_GetRelativeMouseState(&dx,&dy);
    cam.handleMotion(dx, ras, obj.scene, ren, obj.planes);
    cam.handleTransform(currVel, ras, obj.scene, ren, obj.planes);

    for (double& it: currVel) {
        if (it > 0) it = std::max(0.0, it - FRICTION);
        else if(it < 0) it = std::min(0.0, it + FRICTION);
        
    }
    // just some test points for the triangles
    // point p1 = {0,0}; //FIXME: Note that order has changed to x,y,z,h these points are in x,y,h,z
    // point p2 = {100,100, 1};
    // point p3 = {0, 0, 0.5};
    // point p4 = {-150, 200,0.25};
        // TODO: Note that this is for the shaded triangle
    // SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
    // SDL_RenderClear(ren);
    // // ras.drawWireTriangle(p2, p3, p4, {255,255,255}, ren);
    // ras.fillInTriangle(p2, p3, p4, {255,0,0}, ren);
    // SDL_RenderPresent(ren);
    
    // SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
    // SDL_RenderClear(ren);


    // // This is for the (theoretical) cube
    // // front
    // point vAf {-2, -0.5, 5};
    // point vBf {-2, 0.5, 5};
    // point vCf {-1,0.5, 5};
    // point vDf {-1, -0.5, 5};

    // // back 
    // point vAb {-2, -0.5, 6};
    // point vBb {-2, 0.5, 6};
    // point vCb {-1,0.5, 6};
    // point vDb {-1, -0.5, 6};

    // //front 
    // ras.drawLine(ras.projectVertex(vAf), ras.projectVertex(vBf), {0,0,255}, ren);
    // ras.drawLine(ras.projectVertex(vBf), ras.projectVertex(vCf), {0,0,255}, ren);
    // ras.drawLine(ras.projectVertex(vCf), ras.projectVertex(vDf), {0,0,255}, ren);
    // ras.drawLine(ras.projectVertex(vDf), ras.projectVertex(vAf), {0,0,255}, ren);

    // // back
    // ras.drawLine(ras.projectVertex(vAb), ras.projectVertex(vBb), {255,0,0}, ren);
    // ras.drawLine(ras.projectVertex(vBb), ras.projectVertex(vCb), {255,0,0}, ren);
    // ras.drawLine(ras.projectVertex(vCb), ras.projectVertex(vDb), {255,0,0}, ren);
    // ras.drawLine(ras.projectVertex(vDb), ras.projectVertex(vAb), {255,0,0}, ren);

    // // connection
    // ras.drawLine(ras.projectVertex(vAf), ras.projectVertex(vAb), {0,255,0}, ren);
    // ras.drawLine(ras.projectVertex(vBf), ras.projectVertex(vBb), {0,255,0}, ren);
    // ras.drawLine(ras.projectVertex(vCf), ras.projectVertex(vCb), {0,255,0}, ren);
    // ras.drawLine(ras.projectVertex(vDf), ras.projectVertex(vDb), {0,255,0}, ren);
    
    // SDL_RenderPresent(ren);
        // New Cube Method
    
    
    

    
    }
    close(obj.scene);
}
//TODO: Figure out out camera stuff




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

void close(std::vector<cube*> fullScene) {
    for (const auto& cub: fullScene) {
        delete cub;
    }
    SDL_FreeSurface(sur);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
