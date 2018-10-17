// mathlib.h

#ifndef mathlib_h
#define mathlib_h

class point2D
{
  public:
    point2D();
    point2D(float inX, float inY);
    float x;
    float y;
};

// by definition, a vector is a point's distance to the origin.
class vec2D
{
  public:
    vec2D();
    vec2D(float inX, float inY);
    float x;
    float y;
    static float magnitude(vec2D vec);
};

class mathlib
{
  public:
    mathlib();
    static float distance(point2D start, point2D end);
    static float fastdistance(point2D start, point2D end);
    static float length(vec2D vec);
    static vec2D normalize(vec2D vec);
    static vec2D vectorMultiply(vec2D vec, float scalar);
    static vec2D createVector(vec2D vec1, vec2D vec2);
    static point2D movePoint(point2D p, vec2D v);
};

#endif