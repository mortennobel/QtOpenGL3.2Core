QtOpenGL3.2Core
===============

An example of creating an OpenGL 3.2 core profile context using Qt 4.8/5.x crossplatform.

The project compiles under Qt 4.8.1 or later.

On Windows it requires GLEW (http://glew.sourceforge.net/) to access the OpenGL functions. You might need to update the GLEW path in the .pro file. 

On Windows tested on Qt 4.8.1 using VS 2010.

On OS/X tested on Qt 4.8.1 - 5.0.0-beta2 using GCC. The OS/X workaround used is based on this thread ( https://qt-project.org/forums/viewthread/8047/ ). On Qt 5.0.0 or later the OpenGL workaround is disabled, since OpenGL 3.2 works out of the box.

Known issues:
OS/X: Both GL.h and GL3.h is included - this gives a compiler warning and also import the deprecated OpenGL functions. 
