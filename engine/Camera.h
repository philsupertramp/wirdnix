#ifndef CAMERA_H
#define CAMERA_H

#include "olcPGEX_Graphics3D.h"
#include "olcPixelGameEngine.h"

class Engine;

class Camera
    : private olc::GFX3D::PipeLine
{
    olc::GFX3D::vec3d _pos;
    olc::GFX3D::vec3d _lookat;
    olc::GFX3D::vec3d _up;

public:
    ///*** constructors ***//
    Camera();
    ~Camera();

    // allow render to be called
    using olc::GFX3D::PipeLine::Render;

    ///*** constants ***//
    const static float MOVEMENT_SPEED;
    const static float ROTATIONAL_SPEED;
    const static float ZOOM_SPEED;

    ///*** modifiers ***//
    void moveForward(float fElapsedTime = 0);
    void moveBackward(float fElapsedTime = 0);
    void moveLeft(float fElapsedTime = 0);
    void moveRight(float fElapsedTime = 0);
    void rotateLeft(float fElapsedTime = 0);
    void rotateRight(float fElapsedTime = 0);
    void moveUp(float fElapsedTime = 0);
    void moveDown(float fElapsedTime = 0);

    void reset();
    void iterate();

    friend class Engine;
};

#endif // CAMERA_H
