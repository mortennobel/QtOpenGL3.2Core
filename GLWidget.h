#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QtGlobal>

#include "glheader.h"

#include <QGLContext>
#include <QGLWidget>

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    GLWidget( const QGLFormat& format, QWidget* parent = 0 );

protected:
    virtual void initializeGL();
    virtual void resizeGL( int w, int h );
    virtual void paintGL();


private:
    GLuint prepareShaderProgram( const QString& vertexShaderPath,
                               const QString& fragmentShaderPath );

    GLuint m_shader;
    GLuint m_vertexBuffer;
};

#endif // GLWIDGET_H
