#ifndef OBJECTS
#define OBJECTS
#include <array>
#include <vector>
#include <cmath>

struct point {
    double x,y;
    double z = 1;
    float h = 1;
    point operator+(const point& other) const {return {x + other.x, y + other.y, z + other.z, h + other.h};}
    point operator+=(const point& other) const {return {x + other.x, y + other.y, z + other.z, h + other.h};}
    point operator+(const double scale) const {return {x+scale, y+scale, z+scale,h };}
    point operator+=(const double scale) const {return {x+scale, y+scale, z+scale,h };}
    point operator*=(const double scale) const {return {x*scale, y*scale, z*scale, h};}
    point cross(const point a,const point b);
    double dot(const point a,const point b) {return a.x*b.x+a.y*b.y+a.z*b.z;}
};


struct triangle {
    std::array<int, 3> verts;
    std::vector<int> color = {255,0,0};
};

struct cube {
    cube(double x, double y, double z, double x_scale, double y_scale, double z_scale, double rotation);
    std::vector<point> verticies;
    std::vector<triangle> tri;
    std::array<double, 3> currT;
    std::array<double, 3> currS;
    double currR; 
    void transform(const std::array<double, 3> tVector);
    void rotate(const double radians);
    void scale(const std::array<double, 3> amount);
};

struct Plane {
    point n;
    double d;
    Plane() : n{0,0,0}, d(0) {} 
    Plane(double A, double B, double C, double D);
    double signedDistance (const point p) const {return (n.x*p.x + n.y*p.y + n.z*p.z + d);}
};  

struct objects {
  std::vector<cube*> scene;
  std::vector<cube*> clippedScene;
  std::vector<cube*> tempCubes;
  std::array<Plane, 4> planes;
};



#endif