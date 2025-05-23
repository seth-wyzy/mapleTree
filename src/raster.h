#ifndef RASTER
#define RASTER
#include <vector>
#include <SDL2/SDL.h>


#define WIDTH_SCREEN 1200
#define HEIGHT_SCREEN 960
#define VIEWPORT_WIDTH 1
#define VIEWPORT_HEIGHT 1
#define VIEWPORT_DEPTH 1
#define DISTANCE 1

struct point {
    double x,y;
    int z = 1;
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
    point toScreenCords(const point& p);
    point viewportToCanvas(const point& p);
    point projectVertex(const point& p);

};




#endif