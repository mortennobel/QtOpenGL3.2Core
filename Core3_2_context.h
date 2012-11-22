#ifndef CORE3_2_CONTEXT_H
#define CORE3_2_CONTEXT_H
#include <QtGlobal>

#if defined(Q_OS_MAC)
#if QT_VERSION <= 0x040803 // if less or equal to 4.8.3
void* select_3_2_mac_visual(GDHandle handle);
#endif
#endif

struct Core3_2_context : public QGLContext {
    Core3_2_context(const QGLFormat& format, QPaintDevice* device) : QGLContext(format,device) {}
    Core3_2_context(const QGLFormat& format) : QGLContext(format) {}

#if defined(Q_OS_MAC)
#if QT_VERSION <= 0x040803 // if less or equal to 4.8.3
    virtual void* chooseMacVisual(GDHandle handle) {
        return select_3_2_mac_visual(handle);
    }
#endif
#endif
};

#endif // CORE3_2_CONTEXT_H
