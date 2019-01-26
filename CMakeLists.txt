cmake_minimum_required(VERSION 3.10)
project(wirdnix)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread -fpermissive")

add_executable(widnix 
	main.cpp 
	olcPixelGameEngine.h 
	pge.cpp
	Engine.h
	Engine.cpp
)

#find_package (PkgConfig REQUIRED)
find_package (OpenGL REQUIRED)
#find_package (GLUT REQUIRED)


if(UNIX)
	include_directories(${OPENGL_INCLUDE_DIR}  ${GLUT_INCLUDE_DIRS})
endif(UNIX)

file(GLOB SOURCE_FILES
        *.cpp
        *.h
        )
if(UNIX)

target_link_libraries (wirdnix 
	${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} GL m dl Xinerama Xrandr Xi Xcursor X11 Xxf86vm pthread png)
endif(UNIX)