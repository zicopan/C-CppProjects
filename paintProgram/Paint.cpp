#include <stdio.h>
#include <stdlib.h>
#include "mathlib.h"
#include "mathlib.cpp"
#include <vector>

using namespace std;

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#endif

#define RED 2
#define GREEN 3
#define BLUE 4
#define PURPLE 5
#define CYAN 6
#define YELLOW 7
#define WHITE 8
#define ERASER 9
#define CLEAR 10
#define POINTS 11
#define LINES 12
#define RECTANGLES 13
#define CIRCLES 14
#define QUIT 15

int ScreenHeight = 600;
int brushSize = 3;

//initial drawing colour is green
float red = 0.0, green = 1.0, blue = 0.0;
vector<int> v;

bool draw = false;

// change which based on menu selection to draw different shapes
int which = 1;

void init(void)
{
    // background color
    glClearColor(0, 0, 0, 0);
    glColor3f(red, green, blue);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 600);
    //glutSwapBuffers();
}

void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0,0,0,0);
    //glFlush();
    glutSwapBuffers();
}

void lineDraw(vector<int> vec)
{
    int x, y;   // initial point
    int x1, y1; // end point

    x = vec[0];
    y = vec[1];
    x1 = vec[2];
    y1 = vec[3];

    int dx, dy, w, h;

    w = x1 - x;
    h = y1 - y;

    // generalization of bresenham's algorithm
    // courtesy of
    // http://tech-algorithm.com/articles/drawing-line-using-bresenham-algorithm/
    int dx1 = 0, dy1 = 0, dx2 = 0, dy2 = 0;
    if (w < 0)
        dx1 = -1;
    else if (w > 0)
        dx1 = 1;
    if (h < 0)
        dy1 = -1;
    else if (h > 0)
        dy1 = 1;
    if (w < 0)
        dx2 = -1;
    else if (w > 0)
        dx2 = 1;

    int l = abs(w);
    int s = abs(h);

    if (!(l > s))
    {
        l = abs(h);
        s = abs(w);
        if (h < 0)
            dy2 = -1;
        else if (h > 0)
            dy2 = 1;
        dx2 = 0;
    }
    int n = l >> 1;
    glColor3f(red, green, blue);
    glPointSize(brushSize);
    glBegin(GL_POINTS);
    for (int i = 0; i <= l; i++)
    {
        glVertex2i(x, y);
        n += s;
        if (!(n < l))
        {
            n -= l;
            x += dx1;
            y += dy1;
        }
        else
        {
            x += dx2;
            y += dy2;
        }
    }
    glEnd();
}

void rectangleDraw(vector<int> vec)
{
    int topLeftx = vec[0];
    int topLefty = vec[1];

    int botRightx = vec[2];
    int botRighty = vec[3];

    int botLeftx, botLefty;
    int topRightx, topRighty;
    botLeftx = topLeftx;
    botLefty = botRighty;
    topRightx = botRightx;
    topRighty = topLefty;

    vector<int> rect;

    rect.push_back(topLeftx);
    rect.push_back(topLefty);
    rect.push_back(topRightx);
    rect.push_back(topRighty);
    lineDraw(rect);

    rect.clear();

    rect.push_back(topRightx);
    rect.push_back(topRighty);
    rect.push_back(botRightx);
    rect.push_back(botRighty);
    lineDraw(rect);

    rect.clear();

    rect.push_back(botRightx);
    rect.push_back(botRighty);
    rect.push_back(botLeftx);
    rect.push_back(botLefty);
    lineDraw(rect);

    rect.clear();

    rect.push_back(botLeftx);
    rect.push_back(botLefty);
    rect.push_back(topLeftx);
    rect.push_back(topLefty);
    lineDraw(rect);

    rect.clear();
}

void circleDraw(vector<int> vec)
{
    // center coords of circle
    int xc = vec[0];
    int yc = vec[1];
    point2D cen = point2D(vec[0], vec[1]);
    point2D rad = point2D(vec[2], vec[3]);
    
    // radius of circle
    float f;
    f = mathlib::distance(cen, rad);
    int r = static_cast<int>(f);

    int x = r; int y = 0; int e = 0;
    while (x >= y)
    {
        glColor3f(red, green, blue);
        glPointSize(brushSize);
        glBegin(GL_POINTS);

        glVertex2i(xc + x, yc + y);
        glVertex2i(xc - x, yc + y);
        glVertex2i(xc + x, yc - y);
        glVertex2i(xc - x, yc - y);
        glVertex2i(xc + y, yc + x);
        glVertex2i(xc - y, yc + x);
        glVertex2i(xc + y, yc - x);
        glVertex2i(xc - y, yc - x);

        glEnd();

// midpoint circle drawing algorithm courtesy of
// https://www.thecrazyprogrammer.com/2016/12/bresenhams-midpoint-circle-algorithm-c-c.html
        if (e <= 0)
        {
            y += 1;
            e += 2 * y + 1;
        }

        if (e > 0)
        {
            x -= 1;
            e -= 2 * x + 1;
        }
    }
}

void MouseFuncs(int mousex, int mousey)
{
    glClearColor(0,0,0, 0);
    if (draw == false){
        glutSwapBuffers();
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0,0,0,0);
        draw = true;
    }
    glutSwapBuffers();
    // for drawing points
    if (which == 1)
    {

        point2D point = point2D(mousex, mousey);

        glColor3f(red, green, blue);
        GLint x = point.x;
        GLint y = ScreenHeight - point.y;
        glPointSize(brushSize);

        glBegin(GL_POINTS);
        //glPointSize(brushSize);
        //glVertex2f(point.x, point.y);
        glVertex2i(x, y);
        glEnd();
        glFlush();
    }

    // for drawing lines between two clicked points
    else if (which == 2)
    {
        point2D point2 = point2D(mousex, mousey);

        GLint x = point2.x;
        GLint y = ScreenHeight - point2.y;

        if (v.size() == 0)
        {
            v.push_back(x);
            v.push_back(y);
        }

        else if (v.size() == 2)
        {
            v.push_back(x);
            v.push_back(y);
            lineDraw(v);
            v.clear();
        }
    }

    // for drawing rectangles
    // top left corner specified by one click, top right by the other
    else if (which == 3)
    {
        point2D corner = point2D(mousex, mousey);
        GLint x = corner.x;
        GLint y = ScreenHeight - corner.y;

        if (v.size() == 0)
        {
            v.push_back(x);
            v.push_back(y);
        }

        else if (v.size() == 2)
        {
            v.push_back(x);
            v.push_back(y);
            rectangleDraw(v);
            v.clear();
        }
    }

    // for drawing circles
    // first click for center of circle, second for radius
    else if (which == 4)
    {
        point2D circle = point2D(mousex, mousey);
        GLint x = circle.x;
        GLint y = ScreenHeight - circle.y;

        if (v.size() == 0)
        {
            v.push_back(x);
            v.push_back(y);
        }

        else if (v.size() == 2)
        {
            v.push_back(x);
            v.push_back(y);
            circleDraw(v);
            v.clear();
        }
    }

    //glFlush();
    glutSwapBuffers();
    //glutPostRedisplay();
}

void Keyboard(unsigned char key, int a, int b)
{
    switch (key)
    {
    // (like the plus key but without having to hold shift)
    // increases size
    case '=':
        brushSize++;
        break;
    case '-':
        // ensures not less than 1
        if (brushSize > 1)
            brushSize--;
        break;
    case 'q':
        exit(-1);
    default:
        break;
    }
}

void menuProc(int value)
{
    switch (value)
    {
    case RED:
        red = 1.0;
        green = 0.0;
        blue = 0.0;
        break;
    case GREEN:
        red = 0.0;
        green = 1.0;
        blue = 0.0;
        break;
    case BLUE:
        red = 0.0;
        green = 0.0;
        blue = 1.0;
        break;
    case PURPLE:
        red = 128.0;
        green = 0.0;
        blue = 128.0;
        break;
    case CYAN:
        red = 0.0;
        green = 1.0;
        blue = 1.0;
        break;
    case YELLOW:
        red = 1.0;
        green = 1.0;
        blue = 0.0;
        break;
    case ERASER:
        red = 0.0;
        green = 0.0;
        blue = 0.0;
        break;
    case WHITE:
        red = 1.0;
        green = 1.0;
        blue = 1.0;
        break; // set eraser to white

    case POINTS:
        which = 1;
        break;
    case LINES:
        which = 2;
        break;
    case RECTANGLES:
        which = 3;
        break;
    case CIRCLES:
        which = 4;
        break;
    case CLEAR:
        glutSwapBuffers();
        glClear(GL_COLOR_BUFFER_BIT);
        glFlush();
        break;

    case QUIT:
        exit(-1);
        break;
    }
}

void createOurMenu()
{

    int subMenu_id_colours = glutCreateMenu(menuProc);
    glutAddMenuEntry("Red", RED);
    glutAddMenuEntry("Blue", BLUE);
    glutAddMenuEntry("Green", GREEN);
    glutAddMenuEntry("Purple", PURPLE);
    glutAddMenuEntry("Cyan", CYAN);
    glutAddMenuEntry("Yellow", YELLOW);
    glutAddMenuEntry("White", WHITE);
    glutAddMenuEntry("Eraser", ERASER);

    int subMenu_id_shapes = glutCreateMenu(menuProc);
    glutAddMenuEntry("Point", POINTS);
    glutAddMenuEntry("Line", LINES);
    glutAddMenuEntry("Rectangle", RECTANGLES);
    glutAddMenuEntry("Circle", CIRCLES);
    //...

    int menu_id = glutCreateMenu(menuProc);
    glutAddSubMenu("Colours", subMenu_id_colours);
    glutAddSubMenu("Shapes", subMenu_id_shapes);
    glutAddMenuEntry("Clear the screen", CLEAR);
    glutAddMenuEntry("Quit", QUIT);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char **argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(200, 50);
    glutCreateWindow("Paint Program");
    glutDisplayFunc(myDisplay);
    glutMotionFunc(MouseFuncs);
    glutKeyboardFunc(Keyboard);

    cout << "\nCommands\n~~~~~~~~~\n~~~~~~~~~\nKeyboard: '=' increases the brushsize\n'-' decreases the brushsize\n'q' quits the program\n\nMouse: Right click to open menu" << endl;
    cout << "Point - draws points by clicking and/or dragging" <<endl;
    cout << "Line - draws a line between 2 subsequently clicked points" << endl;
    cout << "Rectangle - draws a rectangle via 2 clicks representing the upper-left and bottom-right vertices" << endl;
    
    cout << "Circle - draws a circle centered at the position of the first click with radius set by a second click\n" << endl;
    createOurMenu();
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    //glutPostRedisplay();

    init();
    glutMainLoop();

    return 0;
}
