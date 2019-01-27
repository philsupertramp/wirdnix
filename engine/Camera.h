#ifndef CAMERA_H
#define CAMERA_H

#include "olcPixelGameEngine.h"
#include "olcPGEX_Graphics2D.h"

class Engine;
typedef int WorldPos;

class Camera
{
    olc::GFX2D::Transform2D transform;

public:
    ///*** constructors ***//
    Camera();
    ~Camera();

    ///*** constants ***//
    const static WorldPos MOVEMENT_SPEED = 5;
    const static float ROTATIONAL_SPEED;
    const static WorldPos ZOOM_SPEED = 1;

    float getAngle();

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void rotateLeft();
    void rotateRight();
    void zoomOut();
    void zoomIn();

    void reset();

    friend class Engine;
};

#endif // CAMERA_H
