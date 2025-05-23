#ifndef CAMERA
#define CAMERA

#include "raster.h"

struct camera {
    int x, y, z;
    
      
};
// P'z = d, obviously
// P'y = Py*d / Pz
// P'x = Px*d / Pz
// Cx = P'x * Cw / Vw 
// Cy = P'y * Ch / Vh


#endif