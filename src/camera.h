#ifndef CAMERA
#define CAMERA


#include "raster.h"
#include <array>


#define ACCEL 3
#define FRICTION 0.5

struct camera {
    int x, y, z;
    double x_velocity = 0;
    double y_velocity = 0;
    std::array<double, 3> takeInput(const SDL_Event e);
    void updateVelocity(const SDL_Event e, Raster& ras, std::vector<cube*> scene, SDL_Renderer* ren, std::array<double, 3>& currVel);
    void handleTransform(std::array<double, 3> friction, Raster& ras, std::vector<cube*> scene, SDL_Renderer* ren);
    void handleMotion(const int dx, Raster& ras, std::vector<cube*> scene, SDL_Renderer* ren);

};
// P'z = d, obviously
// P'y = Py*d / Pz
// P'x = Px*d / Pz
// Cx = P'x * Cw / Vw 
// Cy = P'y * Ch / Vh


#endif