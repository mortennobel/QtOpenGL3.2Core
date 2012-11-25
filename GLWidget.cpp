#include "GLWidget.h"
#include "Core3_2_context.h"

#include <QDebug>
#include <QKeyEvent>
#include <QFile>
#include <QString>

#include <iostream>

using namespace std;

GLWidget::GLWidget( const QGLFormat& format, QWidget* parent )
    : QGLWidget( new Core3_2_context(format), parent ),
      m_vertexBuffer( 0 )
{
}

GLuint GLWidget::prepareShaderProgram( const QString& vertexShaderPath,
                                     const QString& fragmentShaderPath )
{
    struct Shader {
        const QString&  filename;
        GLenum       type;
        GLchar*      source;
    }  shaders[2] = {
        { vertexShaderPath, GL_VERTEX_SHADER, NULL },
        { fragmentShaderPath, GL_FRAGMENT_SHADER, NULL }
    };

    GLuint program = glCreateProgram();

    for ( int i = 0; i < 2; ++i ) {
        Shader& s = shaders[i];
        QFile file( s.filename );
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
            qWarning() << "Cannot open file " << s.filename;
            exit( EXIT_FAILURE );
        }
        QByteArray data = file.readAll();
        file.close();
        s.source = data.data();

        if ( shaders[i].source == NULL ) {
            qWarning() << "Failed to read " << s.filename;
            exit( EXIT_FAILURE );
        }
        GLuint shader = glCreateShader( s.type );
        glShaderSource( shader, 1, (const GLchar**) &s.source, NULL );
        glCompileShader( shader );

        GLint  compiled;
        glGetShaderiv( shader, GL_COMPILE_STATUS, &compiled );
        if ( !compiled ) {
            qWarning() << s.filename << " failed to compile:" ;
            GLint  logSize;
            glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &logSize );
            char* logMsg = new char[logSize];
            glGetShaderInfoLog( shader, logSize, NULL, logMsg );
            qWarning() << logMsg;
            delete [] logMsg;

            exit( EXIT_FAILURE );
        }

        glAttachShader( program, shader );
    }

    /* Link output */
    glBindFragDataLocation(program, 0, "fragColor");

    /* link  and error check */
    glLinkProgram(program);

    GLint  linked;
    glGetProgramiv( program, GL_LINK_STATUS, &linked );
    if ( !linked ) {
        qWarning() << "Shader program failed to link";
        GLint  logSize;
        glGetProgramiv( program, GL_INFO_LOG_LENGTH, &logSize);
        char* logMsg = new char[logSize];
        glGetProgramInfoLog( program, logSize, NULL, logMsg );
        qWarning() << logMsg ;
        delete [] logMsg;

        exit( EXIT_FAILURE );
    }

    /* use program object */
    glUseProgram(program);

    return program;
}

void GLWidget::initializeGL()
{
#if defined(Q_OS_WIN32)
    glewExperimental = true;
    GLint GlewInitResult = glewInit();
    if (GlewInitResult != GLEW_OK) {
        const GLubyte* errorStr = glewGetErrorString(GlewInitResult);
        int size = strlen(reinterpret_cast<const char*>(errorStr));
        qDebug() <<"Glew error "<<QString::fromUtf8(reinterpret_cast<const char*>(errorStr), size);

    }
#endif

    QGLFormat glFormat = QGLWidget::format();
    // Set the clear color to black
    glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
    qDebug() << "OpenGL version "<<QString::fromStdString(string((const char*)glGetString(GL_VERSION)))
             << "GLSL "<<QString::fromStdString(string((const char*)glGetString(GL_SHADING_LANGUAGE_VERSION)));

    // Prepare a complete shader program...
    m_shader = prepareShaderProgram( ":/simple.vert", ":/simple.frag" );

    // Create a interleaved triangle (vec3 position, vec3 color)
    float points[] = { -0.5f, -0.5f, 0.0f, 1.0f, 0.0, 0.0,
                        0.5f, -0.5f, 0.0f, 0.0f, 1.0, 0.0,
                        0.0f,  0.5f, 0.0f, 0.0f, 0.0, 1.0,  };
    glGenVertexArrays(1, &m_vertexBuffer);
    glBindVertexArray(m_vertexBuffer);
    GLuint  vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, 3 * 6 * sizeof(float), points, GL_STATIC_DRAW);
    GLuint positionAttribute = glGetAttribLocation(m_shader, "vertex");
    GLuint colorAttribute = glGetAttribLocation(m_shader, "color");
    glEnableVertexAttribArray(positionAttribute);
    glVertexAttribPointer(positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(float)*6, (const GLvoid *)0);
    glEnableVertexAttribArray(colorAttribute);
    glVertexAttribPointer(colorAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(float)*6, (const GLvoid *)(sizeof(float)*3));
}

void GLWidget::resizeGL( int w, int h )
{
    // Set the viewport to window dimensions
    glViewport( 0, 0, w, qMax( h, 1 ) );
}

void GLWidget::paintGL()
{
    // Clear the buffer with the current clearing color
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    // Draw stuff
    glDrawArrays( GL_TRIANGLES, 0, 3 );
}

