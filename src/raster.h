#ifndef RASTER
#define RASTER
#include <vector>
#include <SDL2/SDL.h>
#include "objects.h"



#define WIDTH_SCREEN 1200
#define HEIGHT_SCREEN 960
#define VIEWPORT_WIDTH 1
#define VIEWPORT_HEIGHT 1
#define VIEWPORT_DEPTH 1
#define DISTANCE 1



class Raster {
public: 
    void drawLine(point start, point end, std::vector<int> color, SDL_Renderer * ren);
    void drawWireTriangle(point p0, point p2, point p3, std::vector<int> color, SDL_Renderer *ren );
    void swap(point &x, point &y);
    void fillInTriangle(point p0, point p1, point p3, std::vector<int> color, SDL_Renderer *ren);

    template <typename T>
    std::vector<double> interpolate(T i0,T d0,T i1,T d1);
    point toScreenCords(const point& p);
    point viewportToCanvas(const point& p);
    point projectVertex(const point& p);
    void renderTriangle(triangle t, std::vector<point> proj,SDL_Renderer* ren);
    void renderObject(std::vector<point> verticies, std::vector<triangle> triangle,SDL_Renderer* ren);
    //TODO: Create Render Scene Function
        // should be pretty easy, like just a for loop to itterate over a scene, and each cube could have like elements to transform
        // like as part of their struct, or just creating like another struct of an instnace and using that
    // once render scene function is created, update scene can be created by transforming everything and then using that 
    // also should be storing every element that is in a scene in a vector 
    void renderScene(std::vector<cube> scene);

};




#endif