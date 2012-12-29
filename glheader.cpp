#include "glheader.h"

using namespace std;

void glError(const char *file, int line) {
        GLenum err (glGetError());

        while(err!=GL_NO_ERROR) {
                string error;

                switch(err) {
                        case GL_INVALID_OPERATION:      error="INVALID_OPERATION";      break;
                        case GL_INVALID_ENUM:           error="INVALID_ENUM";           break;
                        case GL_INVALID_VALUE:          error="INVALID_VALUE";          break;
                        case GL_OUT_OF_MEMORY:          error="OUT_OF_MEMORY";          break;
                        case GL_INVALID_FRAMEBUFFER_OPERATION:  error="INVALID_FRAMEBUFFER_OPERATION";  break;
                }

                cerr<<"GL_"<<error<<" - "<<file<<':'<<line<<endl;
                err=glGetError();
        }
}

void glSetup(){
#if defined(Q_OS_WIN32)
    glewExperimental = true;
    GLint GlewInitResult = glewInit();
    if (GlewInitResult != GLEW_OK) {
        const GLubyte* errorStr = glewGetErrorString(GlewInitResult);
        int size = strlen(reinterpret_cast<const char*>(errorStr));
        qDebug() <<"Glew error "<<QString::fromUtf8(reinterpret_cast<const char*>(errorStr), size);

    }
#endif

    cout << "OpenGL initialized: version "<<glGetString(GL_VERSION) << "GLSL "<<glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}
