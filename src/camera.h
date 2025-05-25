#ifndef CAMERA
#define CAMERA

#include "SDL_events.h"
#include "raster.h"

struct camera {
    int x, y, z;
    std::array<double, 3> takeInput(const SDL_Event e);
    void handleTransform(const SDL_Event e, Raster& ras, std::vector<cube*> scene, SDL_Renderer* ren);

};
// P'z = d, obviously
// P'y = Py*d / Pz
// P'x = Px*d / Pz
// Cx = P'x * Cw / Vw 
// Cy = P'y * Ch / Vh


#endif