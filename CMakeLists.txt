project(QtOpenGL32Core)

cmake_minimum_required(VERSION 2.8.11)

# Qt5
#find_package(Qt5Core REQUIRED)
#find_package(Qt5Gui REQUIRED)
#find_package(Qt5OpenGL REQUIRED)
#find_package(Qt5Widgets REQUIRED)
#add_definitions(${Qt5Core_DEFINITIONS})
#add_definitions(${Qt5Gui_DEFINITIONS})
#add_definitions(${Qt5OpenGL_DEFINITIONS})
#add_definitions(${Qt5Widgets_DEFINITIONS})
#set(CMAKE_CXX_FLAGS "-Wall -std=c++0x ${Qt5Core_EXECUTABLE_COMPILE_FLAGS} ${Qt5Gui_EXECUTABLE_COMPILE_FLAGS} ${Qt5OpenGL_EXECUTABLE_COMPILE_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}" CACHE STRING "Flags used by the compiler during all build types.")
#include_directories(
#    ${Qt5Core_INCLUDE_DIRS}
#    ${Qt5GUI_INCLUDE_DIRS}
#    ${Qt5OpenGL_INCLUDE_DIRS}
#    ${Qt5Widgets_INCLUDE_DIRS}
#    ${OPENGL_INCLUDE_DIR}
#)
#${Qt5Core_LIBRARIES} ${Qt5Gui_LIBRARIES} ${Qt5OpenGL_LIBRARIES}
#${Qt5Widgets_LIBRARIES}

find_package(Qt4 4.7 COMPONENTS QtCore QtGui QtOpenGL REQUIRED)


find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW)


include_directories(${PROJECT_BINARY_DIR})

include_directories(
    ${QT_INCLUDES}
    ${OPENGL_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIR}
)

qt4_add_resources(RCC_GENERATED core-profile.qrc)

qt4_wrap_cpp(moc_srcs
    GLWidget.h
)

set(srcs
    ${moc_srcs}
    GLWidget.cpp
    glheader.cpp
    main.cpp
)

set(obj_srcs
    core_profile_attributes.mm
)

if(APPLE)
FIND_LIBRARY(COCOA_LIBRARY Cocoa)
FIND_LIBRARY(FOUNDATION_LIBRARY Foundation)

add_executable(QtOpenGL32Core ${srcs} ${obj_srcs} ${RCC_GENERATED})

target_link_libraries(QtOpenGL32Core
    ${FOUNDATION_LIBRARY} ${COCOA_LIBRARY}
    ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${QT_QTOPENGL_LIBRARY}
    ${QT_QTNETWORK_LIBRARY} ${OPENGL_gl_LIBRARY} ${GLEW_LIBRARIES}
)

else()

add_executable(QtOpenGL32Core ${srcs} ${RCC_GENERATED})

target_link_libraries(QtOpenGL32Core
    ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${QT_QTOPENGL_LIBRARY}
    ${QT_QTNETWORK_LIBRARY} ${OPENGL_gl_LIBRARY} ${GLEW_LIBRARIES}
)

endif()

# ${OPENGL_glu_LIBRARY} ${GLUT_glut_LIBRARY}
