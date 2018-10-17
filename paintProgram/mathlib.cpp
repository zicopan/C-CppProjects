#include "mathlib.h"
#include <iostream>
#include <math.h>

// point2D is a class that calls method in said class point2D
// this class is included in header file "matlib.h"
using namespace std;
// class in mathlib.h
//       point2D     ::   point2D
point2D::point2D()
{
    x = 0;
    y = 0;
}

point2D::point2D(float inX, float inY)
{
    x = inX;
    y = inY;
}

vec2D::vec2D()
{
    x = 0;
    y = 0;
}

vec2D::vec2D(float inX, float inY)
{
    x = inX;
    y = inY;
}

float vec2D::magnitude(vec2D vec)
{
    return abs(sqrt(vec.x * vec.x + vec.y * vec.y));
}

// other normalize, returns a vector
vec2D mathlib::normalize(vec2D vec)
{
    vec2D normalizedVector;
    normalizedVector.x = vec.x / vec2D::magnitude(vec);
    normalizedVector.y = vec.y / vec2D::magnitude(vec);
    return normalizedVector;
}

// to call this function, use mathlib::distance(point, point2)
// where point and point2 are declared above
float mathlib::distance(point2D start, point2D end)
{
    return sqrt(pow(end.x - start.x, 2) +
                pow(end.y - start.y, 2));
}

float mathlib::fastdistance(point2D start, point2D end)
{
    return pow(end.x - start.x, 2) + pow(end.y - start.y, 2);
}

vec2D mathlib::vectorMultiply(vec2D vec, float scalar)
{
    vec.x = vec.x * scalar;
    vec.y = scalar * vec.y;
    return vec;
}

vec2D mathlib::createVector(vec2D vec1, vec2D vec2)
{
    vec2D createdVec;
    createdVec.x = vec2.x - vec1.x;
    createdVec.y = vec2.y - vec1.y;
    return createdVec;
}

point2D mathlib::movePoint(point2D p, vec2D v){

    point2D newPoint;
    newPoint.x = v.x + p.x;
    newPoint.y = v.y + p.y;
    return newPoint;
}

int main(){}
