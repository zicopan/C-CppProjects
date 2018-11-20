# Terrain Generator Program

Random terrains are generated with OpenGL/GLUT and C++ using a couple of algorithms. The default option is the circles algorithm, which can be learned about here http://www.lighthouse3d.com/opengl/terrain/index.php?circles

Another option is the fault algorithm, which can be learned about here http://www.lighthouse3d.com/opengl/terrain/index.php?fault

The following code snippet displays all of the options available in this program:

```
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                      Commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Left and right arrow keys rotate about the y axis
Up and down arrow keys to rotate about the x axis
'1' & '2' change position of first light
'9' & '0' change position of second light
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
'w' --> toggles the wireframe mode
'L' --> toggles the lighting in the scene
's' --> toggles between flat and Gouraud shading
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
'c' --> generates terrain using circles algorithm
'f' --> generates terrain using fault algorithm
'r' --> generates new random terrain with random colour
'h' --> generates hypsometric tint (or topography map)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
't' --> draws terrain using triangles
'y' --> draws terrain using quads

'R' --> resets terrain back to the beginning
Right clicking brings up terrain size menu
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
```

These are a few pictures of some terrains the program has generated:

![ScreenShot](https://github.com/zicopan/C-CppProjects/blob/master/terrainGenerator/terrainPic0.png)

![ScreenShot](https://github.com/zicopan/C-CppProjects/blob/master/terrainGenerator/terrainPic1.png)

![ScreenShot](https://github.com/zicopan/C-CppProjects/blob/master/terrainGenerator/terrainPic2.png)

![ScreenShot](https://github.com/zicopan/C-CppProjects/blob/master/terrainGenerator/terrainPic3.png)

![ScreenShot](https://github.com/zicopan/C-CppProjects/blob/master/terrainGenerator/terrainPic4.png)

Ideas to continue with this project include adding a character which can be moved on the terrain.
