#include "raster.h"
#include "objects.h"
#include <SDL2/SDL_render.h>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <vector>


template<typename T>
std::vector<T> concat_vectors(const std::vector<T>& a, const std::vector<T>& b) {
    std::vector<T> result; 
    result.reserve(a.size() + b.size());  
    result.insert(result.end(), a.begin(), a.end());
    result.insert(result.end(), b.begin(), b.end());
    return result;
}

point Raster::toScreenCords(const point& p) {
    return {
        p.x + WIDTH_SCREEN/2.0,
        -p.y + HEIGHT_SCREEN/2.0,
        p.z,
        p.h
    };
}




// a = y1 - y0) / (x1-x0) (also known as slope)
// b = y0 - ax0
// y = ax + b



void Raster::drawLine(point start, point end, std::vector<int> color, SDL_Renderer* ren){
    start = toScreenCords(start);
    end = toScreenCords(end);
    // make sure that start.x is less than end.x
    SDL_SetRenderDrawColor(ren, color[0], color[1], color[2], 255);
    if (abs(end.x - start.x) > abs(end.y - start.y)) { // for more horizontal line
        if (start.x > end.x) {
            swap(start, end);
        }
        std::vector<double> y_values = interpolate(start.x, start.y, end.x, end.y);
        for (int i = start.x; i <= end.x; i++) {
            SDL_RenderDrawPoint(ren, i, y_values[i-start.x]);
        }
    } else {
        if (start.y > end.y) {
            swap(start, end);
        }
        std::vector<double> x_values = interpolate(start.y, start.x, end.y, end.x);
        for (int i = start.y; i <= end.y; i++) {
            SDL_RenderDrawPoint(ren, x_values[i-start.y], i);
        }
    }
}

template <typename T>
std::vector<double> Raster::interpolate(T i0, T d0, T i1, T d1) {
    if (i0 == i1) {
        return {static_cast<double>(d0)};
    }
    std::vector<double> ps;
    double a = static_cast<double>(d1-d0)/ static_cast<double>(i1-i0);
    double d = static_cast<double>(d0);
    for (int i = i0; i <= i1; i++) {
        ps.push_back(d);
        d += a;
    }
    return ps;
}

void Raster::drawWireTriangle(point p1, point p2, point p3, std::vector<int> color, SDL_Renderer *ren) {
    drawLine(p1, p2, color, ren);    
    drawLine(p2, p3, color, ren);    
    drawLine(p3, p1, color, ren);    
}

void Raster::swap(point &x, point &y) {
    point temp = x;
    x = y;
    y = temp;
}

void Raster::fillInTriangle(point p0, point p1, point p2, std::vector<int> color, SDL_Renderer *ren) {
    p0 = toScreenCords(p0);
    p1 = toScreenCords(p1);
    p2 = toScreenCords(p2);

    if (p1.y < p0.y) swap(p1, p0);
    if (p2.y < p0.y) swap(p2, p0);
    if (p2.y < p1.y) swap(p2,p1);

    std::vector<double> x01 = interpolate(p0.y, p0.x, p1.y, p1.x);
    std::vector<double> h01 = interpolate(static_cast<float>(p0.y), p0.h, static_cast<float>(p1.y), p1.h);

    std::vector<double> x12 = interpolate(p1.y, p1.x, p2.y, p2.x);
    std::vector<double> h12 = interpolate(static_cast<float>(p1.y), p1.h, static_cast<float>(p2.y), p2.h);
    
    std::vector<double> x02 = interpolate(p0.y, p0.x, p2.y, p2.x);
    std::vector<double> h02 = interpolate(static_cast<float>(p0.y), p0.h, static_cast<float>(p2.y), p2.h);
    

    x01.pop_back();
    h01.pop_back();
    std::vector<double> x012 = concat_vectors(x01, x12);
    std::vector<double> h012 = concat_vectors(h01, h12);


    std::vector<double> x_left;
    std::vector<double> h_left;
    std::vector<double> x_right; 
    std::vector<double> h_right;
    int m = floor(x012.size()/ 2);
    if (x02[m] < x012[m]) {
        x_left = x02;
        h_left = h02;
        x_right = x012;
        h_right = h012;
    } else {
        x_left = x012;
        h_left = h012;
        x_right = x02;
        h_right = h02;
    }
    for (int y = p0.y; y <= p2.y; y++) {
        int x_l = x_left[y-p0.y];
        int x_r = x_right[y-p0.y];
        std::vector<double> h_segment = interpolate(static_cast<double>(x_l), h_left[y-p0.y],static_cast<double>(x_r), h_right[y-p0.y]);
        for (int x = x_left[y-p0.y]; x <= x_right[y-p0.y]; x++) {
            SDL_SetRenderDrawColor(ren, color[0]*h_segment[x - x_l], color[1]*h_segment[x - x_l], color[2]*h_segment[x - x_l], 0xFF);
            SDL_RenderDrawPoint(ren, x, y);
        }
    }
}

point Raster::viewportToCanvas(const point& p){
    return {
        p.x* WIDTH_SCREEN / VIEWPORT_WIDTH, 
        p.y*HEIGHT_SCREEN / VIEWPORT_HEIGHT,
        p.z,
        p.h
    };
}

point Raster::projectVertex(const point& p) {
    return {
        viewportToCanvas({p.x*VIEWPORT_DEPTH/p.z, p.y*VIEWPORT_DEPTH/ p.z })
    };
}


void Raster::renderObject(std::vector<point> verticies , std::vector<triangle> tri, SDL_Renderer* ren) {
    std::vector<point> projected;
    for (const auto& it: verticies) {
        projected.push_back(projectVertex(it));
    }
    for (const auto& it: tri) {
        renderTriangle(it, projected, ren);
    }
    
}

void Raster::renderTriangle(triangle t, std::vector<point> proj, SDL_Renderer* ren){
    const point& p0 = proj[t.verts[0]];
    const point& p1 = proj[t.verts[1]];
    const point& p2 = proj[t.verts[2]];
    // drawWireTriangle(p0, p1, p2, t.color, ren);
    fillInTriangle(p0, p1, p2, t.color, ren);
}

void Raster::renderScene(std::vector<cube*> scene, SDL_Renderer* ren, std::array<Plane, 4> planes) {
    std::vector<cube*> temp;
    clipAll(scene, temp, planes);
    std::vector<cube*> cutFaces = cutTriangles(temp);
    for (const auto& cube: cutFaces){
    // for (const auto& cube: temp) {
        renderObject(cube->verticies, cube->tri, ren);
    }

    for (auto& cube: cutFaces) {
        delete cube;
    }
}
void Raster::updateObj(cube& cub, std::array<double, 3> transform, double rotate, std::array<double, 3> scale){
    cub.transform(transform);
    cub.rotate(rotate);
    cub.scale(scale);
}

void Raster::updateScene(std::vector<cube*> scene, SDL_Renderer* ren ,  std::array<Plane, 4> planes, std::array<double, 3> transform, double rotate, std::array<double, 3> scale) {
    for (auto& it: scene) {
        updateObj(*it,transform, rotate, scale );
    }
    renderScene(scene, ren, planes);
}

// by sending the clipped volume, we can avoid rendering too much
void Raster::clipWhole(const std::vector<cube*> scene, std::vector<cube*>& clippedScene, const std::array<Plane, 4> planes){
    for (const auto& cub: scene) {
        for (const auto& vert: cub->verticies) {
            if (planes[0].signedDistance(vert) < 0 ||
              planes[1].signedDistance(vert) < 0 ||
              planes[2].signedDistance(vert) < 0 ||
              planes[3].signedDistance(vert) < 0) {
                clippedScene.push_back(cub);
                break;
            }
        }
    }
    
} 

void Raster::clipAll(const std::vector<cube*> scene, std::vector<cube*>& clippedScene, const std::array<Plane, 4> planes){
    clippedScene.clear();
    clipWhole(scene, clippedScene, planes); // this only calls this for now but will be expanded on later to actually clip everything
}

std::vector<cube*> Raster::cutTriangles(std::vector<cube*> clippedScene) {// i wanted this to be a copy so that it checks it every time but im not sure if that is working
    std::vector<cube*> result;
    for (const auto& sceneCube: clippedScene) {
        cube* tempCube = new cube(*sceneCube); 
        std::vector<triangle> visibleTriangles;
        for (const auto& tri: tempCube->tri) {
            point a = tempCube->verticies[tri.verts[0]];
            point b = tempCube->verticies[tri.verts[1]];
            point c = tempCube->verticies[tri.verts[2]];
            point ab = {b.x-a.x, b.y-a.y, b.z-a.z};
            point ac = {c.x-a.x,c.y-a.y,c.z-a.z};
            point n = ab.cross(ab, ac);
            double len = std::sqrt(n.x*n.x + n.y*n.y + n.z*n.z);
            if (len >= 0) {
                n.x /= len;
                n.y /= len;
                n.z /= len;
            
            // cam to triangle vector is just one of the points on the triangle
            // because cam is at {0,0,0} so the point is just a vector from the cam to the vertex
            double sign = n.dot(n, a);
                if (sign <= 0) { // ok so this isn't working the way that is is supposed to
                    visibleTriangles.push_back(tri);
                }
            }
        } 
        tempCube->tri = visibleTriangles;
        result.push_back(tempCube);
    }
    return result;  // TODO figure ouot how to return the correct thing
}




// this is a test comment
// so im losing the cubes, so something is working
// cannot go though htem anymore. Im losing them, like once faces delete, they don't come back