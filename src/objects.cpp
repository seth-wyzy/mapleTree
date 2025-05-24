#include "objects.h"

cube::cube() {
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
    tri[11]= {2, 6, 7, {255,0,255}};

    // this block is a red cube
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
    // tri[11]= {2, 6, 7, {255,0,0}};



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
void cube::rotate(const double degrees) {
    return;
}

//TODO: Implement rotate 