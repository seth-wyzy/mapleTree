#ifndef RASTER
#define RASTER
#include <vector>
#include <SDL2/SDL.h>


struct point {
    int x,y;
    float h = 1;
};

class Raster {
public: 
    void drawLine(point start, point end, std::vector<int> color, SDL_Renderer * ren);
    void drawWireTriangle(point p0, point p2, point p3, std::vector<int> color, SDL_Renderer *ren );
    void swap(point &x, point &y);
    void fillInTriangle(point p0, point p1, point p3, std::vector<int> color, SDL_Renderer *ren);

    template <typename T>
    std::vector<double> interpolate(T i0,T d0,T i1,T d1);

};




#endif