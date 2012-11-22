#include "GLWidget.h"
#include <QApplication>
#include <QtGui>
#include <QString>

int main(int argc, char *argv[])
{
    QApplication a( argc, argv );

    QGLFormat glFormat;
    glFormat.setVersion( 3, 2 );
    glFormat.setProfile( QGLFormat::CoreProfile ); // Requires >=Qt-4.8.0
    glFormat.setSampleBuffers( true );

    GLWidget w( glFormat );
    w.show();

    return a.exec();
}
