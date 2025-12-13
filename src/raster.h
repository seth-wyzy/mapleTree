#ifndef RASTER
#define RASTER
#include <vector>
#include <SDL2/SDL.h>
#include "objects.h"



#define WIDTH_SCREEN 1200
#define HEIGHT_SCREEN 960
#define PI 3.14159265358979323846
#define VIEWPORT_WIDTH 1
#define VIEWPORT_HEIGHT 1
#define VIEWPORT_DEPTH 1
#define DISTANCE 1
#define FARDISTANCE 100
#define FOVDEGREES 90



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
    void renderScene(std::vector<cube*> scene, SDL_Renderer* ren,std::array<Plane, 4> planes);
    void updateObj(cube& cub, std::array<double, 3> transform = {0,0,0}, double rotate = 0, std::array<double, 3> scale = {1,1,1});
    void updateScene(std::vector<cube*> scene, SDL_Renderer* ren, std::array<Plane, 4> planes, std::array<double, 3> transform = {0,0,0}, double rotate = 0, std::array<double, 3> scale = {1,1,1});
    void clipWhole(const std::vector<cube*> scene, std::vector<cube*>& clippedScene, const std::array<Plane, 4> planes);
    void clipAll(const std::vector<cube*> scenel, std::vector<cube*>& clippedScene, const std::array<Plane, 4> planes);
    std::vector<cube*> cutTriangles(std::vector<cube*> clipedScene);
}; 
//TODO: add a ceiling and floor before rendering frame (put it in renderScene probabaly)


#endif