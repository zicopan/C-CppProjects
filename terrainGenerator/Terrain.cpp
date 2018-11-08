#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

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

// 2 lights (one at other end of terrain)
float light0[] = {50, -1000, 100, 1};
float light1[] = {-50, -1000, -100, 1};
float camPos[] = {100, 130, 100};

//initial terrain colour is red
float red = 1.0, green = 0.0, blue = 0.0;

float heightVals[500][500];
float normals[500][500][3];

// order to draw quads (ccw starting from the bottom left)
float quadOrder[4][2] = {{0, 0}, {-1, 0}, {-1, -1}, {0, -1}};
// order to draw triangles (ccw starting from the bottom left)
float triangleOrder[3][2] = {{0, 0}, {-1, 0}, {0, -1}};

// starting with the quad circles algorithm terrain that's 100x100
bool circles = true;
bool fault = false;
bool quad = true;
int xDimension = 100;
int zDimension = 100;

// other custom configurations
bool wires = false;
bool shade = true;
bool lit = true;
bool hypso = false;

// iterations (6 is arbitary and can be changed)
int iterations = xDimension * 6;

// circle algorithm to generate terrain courtesy of
// http://www.lighthouse3d.com/opengl/terrain/index.php?circles
void circleAlgorithm(int x, int z, int its)
{
    for (int i = 0; i < its; i++)
    {
        // get random circle dimensions
        int randX = rand() % x;
        int randZ = rand() % z;
        int terrainCircleSize = (rand() % 25) + 1;
        float disp = (rand() % 5) + 1;

        for (int j = 0; j < x; j++)
        {
            for (int k = 0; k < z; k++)
            {
                int xDist = j - randX;
                int zDist = k - randZ;
                float Dist = sqrt(pow(xDist, 2) + pow(zDist, 2));
                float pd = (Dist * 2) / terrainCircleSize;
                if (fabs(pd) <= 1.0)
                {
                    heightVals[j][k] += disp / 2 + cos(pd * 3.14) * disp / 2;
                }
            }
        }
    }
}

// fault algorithm to generate terrain courtesy of
// http://www.lighthouse3d.com/opengl/terrain/index.php?impdetails
// adding this for an extra feature
void faultAlgorithm(int x, int z, int its)
{

    for (int i = 0; i < its; i++)
    {
        float v = (float)rand();
        float a = sin(v);
        float b = cos(v);
        float d = sqrt(pow(x, 2) + pow(z, 2));
        float c = ((float)rand() / (float)(RAND_MAX)) * d - d / 2;

        for (int tx = 0; tx < x; tx++)
        {
            for (int tz = 0; tz < z; tz++)
            {
                if (a * tx + b * tz - c > 0)
                {
                    heightVals[tx][tz] += 1;
                }
                else
                {
                    heightVals[tx][tz] -= 1;
                }
            }
        }
    }
}

// generating terrain with quads
void quadsTerrain(float r, float g, float b)
{
    int x1, z1;
    float h;
    for (int x = 1; x < xDimension - 1; x++)
    {
        for (int z = 1; z < zDimension - 1; z++)
        {
            glBegin(GL_QUADS);
            for (int i = 0; i < 4; i++)
            {
                x1 = x - quadOrder[i][0];
                z1 = z - quadOrder[i][1];
                h = heightVals[x1][z1];

                // adding in hypsometric tint as an extra feature
                if (!hypso)
                {
                    glColor3f(r, g, b);
                }

                else
                {
                    if (circles)
                    {

                        if (h >= 20.0)
                        {
                            glColor3f(199.0 / 255.0, 73.0 / 255.0, 53.0 / 255.0);
                        }

                        else if (h >= 18.0)
                        {
                            glColor3f(230.0 / 255.0, 125.0 / 255.0, 84.0 / 255.0);
                        }

                        else if (h >= 16.0)
                        {
                            glColor3f(244.0 / 255.0, 191.0 / 255.0, 122.0 / 255.0);
                        }

                        else if (h >= 14.0)
                        {
                            glColor3f(252.0 / 255.0, 237.0 / 255.0, 170.0 / 255.0);
                        }

                        else if (h >= 12.0)
                        {
                            glColor3f(243.0 / 255.0, 248.0 / 255.0, 178.0 / 255.0);
                        }

                        else if (h >= 10.0)
                        {
                            glColor3f(199.0 / 255.0, 227.0 / 255.0, 167.0 / 255.0);
                        }

                        else if (h >= 1.5)
                        {
                            glColor3f(136.0 / 255.0, 197.0 / 255.0, 167.0 / 255.0);
                        }

                        else
                        {
                            glColor3f(68.0 / 255.0, 130.0 / 255.0, 181.0 / 255.0);
                        }
                    }
                    else
                    {

                        if (h >= 29.0)
                        {
                            glColor3f(199.0 / 255.0, 73.0 / 255.0, 53.0 / 255.0);
                        }

                        else if (h >= 26.0)
                        {
                            glColor3f(230.0 / 255.0, 125.0 / 255.0, 84.0 / 255.0);
                        }

                        else if (h >= 23.0)
                        {
                            glColor3f(244.0 / 255.0, 191.0 / 255.0, 122.0 / 255.0);
                        }

                        else if (h >= 19.0)
                        {
                            glColor3f(252.0 / 255.0, 237.0 / 255.0, 170.0 / 255.0);
                        }

                        else if (h >= 13.0)
                        {
                            glColor3f(243.0 / 255.0, 248.0 / 255.0, 178.0 / 255.0);
                        }

                        else if (h >= 9.0)
                        {
                            glColor3f(199.0 / 255.0, 227.0 / 255.0, 167.0 / 255.0);
                        }

                        else if (h >= 5.0)
                        {
                            glColor3f(136.0 / 255.0, 197.0 / 255.0, 167.0 / 255.0);
                        }

                        else
                        {
                            glColor3f(68.0 / 255.0, 130.0 / 255.0, 181.0 / 255.0);
                        }
                    }
                }
                glNormal3fv(normals[x1][z1]);
                glVertex3d(x1, h, z1);
            }
            glEnd();
        }
    }
}

// generating terrain with triangle strips
void trainglesTerrain(float r, float g, float b)
{
    int x1, z1;
    float h;
    for (int x = 1; x < xDimension - 1; x++)
    {
        for (int z = 1; z < zDimension - 1; z++)
        {
            glBegin(GL_TRIANGLE_STRIP);
            for (int i = 0; i < 3; i++)
            {
                x1 = x - triangleOrder[i][0];
                z1 = z - triangleOrder[i][1];
                h = heightVals[x1][z1];

                if (!hypso)
                {
                    glColor3f(r, g, b);
                }

                else
                {
                    if (circles)
                    {

                        if (h >= 20.0)
                        {
                            glColor3f(199.0 / 255.0, 73.0 / 255.0, 53.0 / 255.0);
                        }

                        else if (h >= 18.0)
                        {
                            glColor3f(230.0 / 255.0, 125.0 / 255.0, 84.0 / 255.0);
                        }

                        else if (h >= 16.0)
                        {
                            glColor3f(244.0 / 255.0, 191.0 / 255.0, 122.0 / 255.0);
                        }

                        else if (h >= 14.0)
                        {
                            glColor3f(252.0 / 255.0, 237.0 / 255.0, 170.0 / 255.0);
                        }

                        else if (h >= 12.0)
                        {
                            glColor3f(243.0 / 255.0, 248.0 / 255.0, 178.0 / 255.0);
                        }

                        else if (h >= 10.0)
                        {
                            glColor3f(199.0 / 255.0, 227.0 / 255.0, 167.0 / 255.0);
                        }

                        else if (h >= 1.5)
                        {
                            glColor3f(136.0 / 255.0, 197.0 / 255.0, 167.0 / 255.0);
                        }

                        else
                        {
                            glColor3f(68.0 / 255.0, 130.0 / 255.0, 181.0 / 255.0);
                        }
                    }
                    else
                    {

                        if (h >= 29.0)
                        {
                            glColor3f(199.0 / 255.0, 73.0 / 255.0, 53.0 / 255.0);
                        }

                        else if (h >= 26.0)
                        {
                            glColor3f(230.0 / 255.0, 125.0 / 255.0, 84.0 / 255.0);
                        }

                        else if (h >= 23.0)
                        {
                            glColor3f(244.0 / 255.0, 191.0 / 255.0, 122.0 / 255.0);
                        }

                        else if (h >= 19.0)
                        {
                            glColor3f(252.0 / 255.0, 237.0 / 255.0, 170.0 / 255.0);
                        }

                        else if (h >= 13.0)
                        {
                            glColor3f(243.0 / 255.0, 248.0 / 255.0, 178.0 / 255.0);
                        }

                        else if (h >= 9.0)
                        {
                            glColor3f(199.0 / 255.0, 227.0 / 255.0, 167.0 / 255.0);
                        }

                        else if (h >= 5.0)
                        {
                            glColor3f(136.0 / 255.0, 197.0 / 255.0, 167.0 / 255.0);
                        }

                        else
                        {
                            glColor3f(68.0 / 255.0, 130.0 / 255.0, 181.0 / 255.0);
                        }
                    }
                }
                glNormal3fv(normals[x1][z1]);
                glVertex3d(x1, h, z1);
            }
            glEnd();
        }
    }
}

// get normal for each shape using the cross product and normalization
void getNormals()
{
    float v[3], u[3], w[3];
    for (int x = 0; x < xDimension; x++)
    {
        for (int z = 0; z < zDimension; z++)
        {
            u[0] = x + 1;
            u[1] = heightVals[x + 1][z] - heightVals[x][z];
            u[2] = z;

            w[0] = x + 1;
            w[1] = heightVals[x + 1][z + 1] - heightVals[x][z];
            w[2] = z + 1;

            v[0] = u[1] * w[2] - u[2] * w[1];
            v[1] = u[2] * w[0] - u[0] * w[2];
            v[2] = u[0] * w[1] - u[1] * w[0];

            float cp = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
            normals[x][z][0] = v[0] / cp;
            normals[x][z][1] = v[1] / cp;
            normals[x][z][2] = v[2] / cp;
        }
    }
}

// determines the build of the current terrain
void newTerrain()
{
    if (circles)
    {
        circleAlgorithm(xDimension, zDimension, iterations);
        getNormals();
        if (quad)
        {
            quadsTerrain(red, green, blue);
        }
        else
        {
            trainglesTerrain(red, green, blue);
        }
    }
    else
    {
        faultAlgorithm(xDimension, zDimension, iterations);
        getNormals();
        if (quad)
        {
            quadsTerrain(red, green, blue);
        }
        else
        {
            trainglesTerrain(red, green, blue);
        }
    }
}

// camera functionality
void special(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_LEFT:
        camPos[2] += 12;
        break;
    case GLUT_KEY_RIGHT:
        camPos[2] -= 12;
        break;
    case GLUT_KEY_UP:
        camPos[1] += 12;
        break;
    case GLUT_KEY_DOWN:
        // stop moving if about to go under map
        if (camPos[1] < 0)
        {
            break;
        }
        else
        {
            camPos[1] -= 12;
        }
        break;
    }
    glutPostRedisplay();
}

// keyboard functionality
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    // terrain generated using quads or triangle strips (t or y)
    case 't':
        quad = false;
        break;
    case 'y':
        quad = true;
        break;

    // changing wireframe mode
    case 'w':
        if (wires)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            wires = false;
        }
        else
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            wires = true;
        }
        break;

    // shading stuff (flat vs Gouraud (or smooth, according to the internet))
    case 's':
        if (shade)
        {
            glShadeModel(GL_SMOOTH);
            shade = false;
        }
        else
        {
            glShadeModel(GL_FLAT);
            shade = true;
        }
        break;

    // lighting stuff (turning lights on or off)
    case 'L':
    case 'l':
        if (lit)
        {
            lit = false;
            glDisable(GL_LIGHT0);
            glDisable(GL_LIGHTING);
        }
        else
        {
            lit = true;
            glEnable(GL_LIGHT0);
            glEnable(GL_LIGHTING);
        }
        break;

    // resets back to the beginning
    case 'R':
        light0[0] = 50; light0[1] = -1000; light0[2] = 100;
        light1[0] = -50; light1[1] = -1000; light1[2] = -100;
        camPos[0] = 100; camPos[1] = 130; camPos[2] = 100;
        red = 1.0, green = 0.0, blue = 0.0;
        quad = true; fault = false; circles = true;
        shade = false; wires = false; lit = true; hypso = false;
        xDimension = 100; zDimension = 100;
        memset(heightVals, 0, 1000000 * (sizeof(float)));
        newTerrain();
        break;

    // random terrain
    // aka - random colour, random algorithm, random primitive
    case 'r':
        memset(heightVals, 0, 1000000 * (sizeof(float)));
        srand((unsigned int)time(NULL));
        red = ((float)rand() / (float)(RAND_MAX)) * 1.0;
        blue = ((float)rand() / (float)(RAND_MAX)) * 1.0;
        green = ((float)rand() / (float)(RAND_MAX)) * 1.0;
        int what;
        what = rand() % 2;
        if (what == 0)
        {
            circles = true;
            fault = false;
            quad = true;
            newTerrain();
            break;
        }
        else
        {
            circles = false;
            fault = true;
            quad = false;
            newTerrain();
            break;
        }

    // hypsometric tint
    case 'H':
    case 'h':
        if (!hypso)
        {
            hypso = true;
            if (quad)
            {
                quadsTerrain(red, green, blue);
            }
            else
            {
                trainglesTerrain(red, green, blue);
            }
        }
        else
        {
            hypso = false;
            if (quad)
            {
                quadsTerrain(red, green, blue);
            }
            else
            {
                trainglesTerrain(red, green, blue);
            }
        }
        break;

    // terrain generated in circles or fault algorithm (c or f)
    case 'c':
        memset(heightVals, 0, 1000000 * (sizeof(float)));
        circles = true;
        fault = false;
        newTerrain();
        break;
    case 'f':
        memset(heightVals, 0, 1000000 * (sizeof(float)));
        circles = false;
        fault = true;
        newTerrain();
        break;

    // increase/decrease lighting by changing the light's position
    case '1':
        light0[1] += 50;
        light1[1] += 50;
        break;
    case '2':
        light0[1] -= 50;
        light1[1] -= 50;
        break;
    case '9':
        light0[2] += 50;
        light1[2] += 50;
        break;
    case '0':
        light0[2] -= 50;
        light1[2] -= 50;
        break;

    // quit program
    case 'q':
        exit(0);
        break;
    }

    // update light position if changed
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLightfv(GL_LIGHT0, GL_POSITION, light0);
    glLightfv(GL_LIGHT1, GL_POSITION, light1);
    glPopMatrix();
    glutPostRedisplay();
}

// terrain size options
void menuProc(int value)
{
    switch (value)
    {
    case 1:
        xDimension = 50;
        zDimension = 50;
        break;
    case 2:
        xDimension = 100;
        zDimension = 100;
        break;
    case 3:
        xDimension = 150;
        zDimension = 150;
        break;
    case 4:
        xDimension = 200;
        zDimension = 200;
        break;
    case 5:
        xDimension = 250;
        zDimension = 250;
        break;
    case 6:
        xDimension = 300;
        zDimension = 300;
        break;
    }
    // reset all array vals and generate new terrain
    memset(heightVals, 0, 1000000 * (sizeof(float)));
    newTerrain();
    glutPostRedisplay();
}

void myDisplay()
{   
    // materials courtesy of
    // http://devernay.free.fr/cours/opengl/materials.html 
    // chrome
    // float m_amb[] = {0.25, 0.25, 0.25, 1.0};
    // float m_dif[] = {0.4, 0.4, 0.4, 1.0};
    // float m_spec[] = {0.774597, 0.774597, 0.774597, 1.0};
    // float shiny = 0.6;

    // ruby
    // these can be changed to anything
    float m_amb[] = {0.1745, 0.01175, 0.01175, 1.0};
    float m_dif[] = {0.61424, 0.04136, 0.04136, 1.0};
    float m_spec[] = {0.727811, 0.626959, 0.626959, 1.0};
    float shiny = 20;

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_amb);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_dif);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_spec);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);
    glColorMaterial(GL_AMBIENT, GL_DIFFUSE);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(camPos[0], camPos[1], camPos[2], 0, 0, 0, 0, 1, 0);
    // maintain image while expanding window
    glTranslatef(-1 * (xDimension / 2), 0, -1 * (xDimension / 2));

    // generate terrain
    if (quad)
    {
        quadsTerrain(red, blue, green);
    }
    else
    {
        trainglesTerrain(red, blue, green);
    }

    glutSwapBuffers();
}

void init()
{
    glClearColor(0, 0, 0, 0);
    glColor3f(1, 1, 1);

    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT0, GL_POSITION, light0);
    glLightfv(GL_LIGHT1, GL_POSITION, light1);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50, 1, 1, 500);
}

void createOurMenu()
{
    int menu_id = glutCreateMenu(menuProc);
    glutAddMenuEntry("50 x 50", 1);
    glutAddMenuEntry("100 x 100", 2);
    glutAddMenuEntry("150 x 150", 3);
    glutAddMenuEntry("200 x 200", 4);
    glutAddMenuEntry("250 x 250", 5);
    glutAddMenuEntry("300 x 300", 6);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

// program start
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(900, 900);    
    glutInitWindowPosition(100, 100); 
    glutCreateWindow("3GC3 A2 - stepannj"); 

    glutDisplayFunc(myDisplay); 
    glutKeyboardFunc(keyboard); 
    glutSpecialFunc(special);

    glEnable(GL_DEPTH_TEST);
    init();
    circleAlgorithm(xDimension, zDimension, iterations);
    getNormals();
    createOurMenu();
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout << "                      Commands\n";
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout << "Left and right arrow keys rotate about the y axis\n";
    cout << "Up and down arrow keys to rotate about the x axis\n";
    cout << "'1' & '2' change position of first light\n";
    cout << "'9' & '0' change position of second light"
         << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout << "'w' --> toggles the wireframe mode\n";
    cout << "'L' --> toggles the lighting in the scene\n";
    cout << "'s' --> toggles between flat and Gouraud shading"
         << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout << "'c' --> generates terrain using circles algorithm\n";
    cout << "'f' --> generates terrain using fault algorithm\n";
    cout << "'r' --> generates new random terrain with random colour\n";
    cout << "'h' --> generates hypsometric tint (or topography map)"
         << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout << "'t' --> draws terrain using triangles\n";
    cout << "'y' --> draws terrain using quads\n"
         << endl;
    cout << "'R' --> resets terrain back to the beginning\n";
    cout << "Right clicking brings up terrain size menu\n";
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

    glutMainLoop();

    return 0;
}