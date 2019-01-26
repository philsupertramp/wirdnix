cmake_minimum_required(VERSION 3.10)
project(wirdnix)

set(CMAKE_CXX_STANDARD 11)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread -fpermissive")

add_executable(wirdnix main.cpp engine/olcPixelGameEngine.h engine/pge.cpp)

find_package (PkgConfig REQUIRED)
find_package (OpenGL REQUIRED)
find_package (GLUT REQUIRED)


include_directories(${OPENGL_INCLUDE_DIR}  ${GLUT_INCLUDE_DIRS})

file(GLOB SOURCE_FILES
        *.cpp
        *.h
        )
target_link_libraries (wirdnix ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} GL m dl Xinerama Xrandr Xi Xcursor X11 Xxf86vm pthread png)
