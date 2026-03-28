#include "objects.h"
#include <cmath>

cube::cube(double x, double y, double z, double x_scale, double y_scale, double z_scale, double rotation) {
    verticies.resize(8);
    tri.resize(12);

    point zero {1,1,1};
    point one {-1,1,1};
    point two {-1,-1,1};
    point three {1,-1,1};
    point four {1,1,-1};
    point five {-1,1,-1};
    point six {-1,-1,-1};
    point seven {1,-1,-1};
    verticies[0] = zero;
    verticies[1] = one;
    verticies[2] = two;
    verticies[3] = three;
    verticies[4] = four;
    verticies[5] = five;
    verticies[6] = six;
    verticies[7] = seven;


    // adding triangles
    tri[0] = {0, 1, 2, {255,0,0}};
    tri[1] = {0, 2, 3, {255,0,0}};
    tri[2] = {4, 0, 3, {0,255,0 }};
    tri[3] = {4, 3, 7, {0,255,255}};
    tri[4] = {5, 4, 7, {0,0,255}};
    tri[5] = {5, 7, 6, {0,0,255}};
    tri[6] = {1, 5, 6, {255,255, 0}};
    tri[7] = {1, 6, 2, {255,255,0}};
    tri[8] = {4, 5, 1, {0,255,255}};
    tri[9] = {4, 1, 0, {0,255,255}};
    tri[10]= {2, 6, 7, {255,0,255}};
    tri[11]= {2, 7, 3, {255,0,255}};

    // this block is a red cube (just a different color)
    // tri[0] = {0, 1, 2, {255,0,0}};
    // tri[1] = {0, 2, 3, {255,0,0}};
    // tri[2] = {4, 0, 3, {255,0,0}};
    // tri[3] = {4, 3, 7, {255,0,0}};
    // tri[4] = {5, 4, 7, {255,0,0}};
    // tri[5] = {5, 7, 6, {255,0,0}};
    // tri[6] = {1, 5, 6, {255,0,0}};
    // tri[7] = {1, 6, 2, {255,0,0}};
    // tri[8] = {4, 5, 1, {255,0,0}};
    // tri[9] = {4, 1, 0, {255,0,0}};
    // tri[10]= {2, 6, 7, {255,0,0}};
    // tri[11]= {2, 7, 3, {255,0,0}};

    originalTri = tri;

    rotate(rotation);
    scale({x_scale, y_scale, z_scale});
    transform({x,y,z});
}

cube::cube(const cube& other)
    : verticies(other.verticies),
      tri(other.tri),
      originalTri(other.originalTri),
      currT(other.currT),
      currS(other.currS),
      currR(other.currR)
{
    // nothing needs to be done in here (this is not wrong)
}


void cube::transform(const std::array<double, 3> t) {
    for (auto& poi: verticies) {
        poi.x += t[0];
        poi.y += t[1];
        poi.z += t[2];
    }
}
void cube::scale(const std::array<double, 3> t) {
   for (auto& poi: verticies) {
        poi.x *= t[0];
        poi.y *= t[1];
        poi.z *= t[2];
    }
}
void cube::rotate(const double radians) {
    for (auto& poi: verticies) {
        double old_x = poi.x;
        poi.x = poi.x*std::cos(radians) + poi.z*std::sin(radians);
        // y' = y for a roation around the y axis
        poi.z = -1*old_x*std::sin(radians) + poi.z*std::cos(radians);
    }
}

Plane::Plane(double A, double B, double C, double D) {
    double len = std::sqrt(A*A + B*B + C*C);
    n = {A/len, B/len, C/len};
    d = D/len; 
}

point point::cross(const point a, const point b) {
    return {a.y*b.z - a.z*b.y, a.z*b.x-a.x*b.z, a.x*b.y-a.y*b.x};
}