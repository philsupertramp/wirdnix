#include "Camera.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Engine.h"


const float Camera::ROTATIONAL_SPEED = .05f;


Camera::Camera()
{ }

Camera::~Camera()
{
}

float Camera::getAngle()
{

    float x1, y1;
    transform.Forward(1, 0, x1, y1);

    float x0, y0;
    transform.Forward(0, 0, x0, y0);

    // average as maybe more precise
    return (acosf(x1 - x0) + asinf(y1 - y0))/2;
}

void Camera::moveUp()
{
    transform.Translate(0, MOVEMENT_SPEED);
}

void Camera::moveDown()
{
    transform.Translate(0, -MOVEMENT_SPEED);
}

void Camera::moveLeft()
{
    transform.Rotate((float)-M_PI_2);
    moveUp();
    transform.Rotate((float)M_PI_2);
}

void Camera::moveRight()
{
    transform.Rotate((float)M_PI_2);
    moveUp();
    transform.Rotate((float)-M_PI_2);
}

void Camera::rotateLeft()
{
    float x0, y0;
    transform.Forward(Engine::instance().GetDrawTargetWidth()/2, Engine::instance().GetDrawTargetHeight()/2, x0, y0);
    transform.Translate(-x0, -y0);
    std::cout << x0 << " " << y0 << std::endl;
    {
        float x0, y0;
        transform.Forward(0, 0, x0, y0);
        std::cout << " " << x0 << " " << y0 << std::endl;
    }
    transform.Rotate(ROTATIONAL_SPEED);
    transform.Translate(x0, y0);
}

void Camera::rotateRight()
{
    //float x0, y0;
    //transform.Forward(0, 0, x0, y0);
    //transform.Translate(-x0, -y0);
    //transform.Rotate(-ROTATIONAL_SPEED);
    //transform.Translate(x0, y0);

    float x0, y0;
    float x0, y0;
    transform.Forward(Engine::instance().GetDrawTargetWidth()/2, Engine::instance().GetDrawTargetHeight()/2, x0, y0);
    transform.Translate(-x0, -y0);
    transform.Rotate(-ROTATIONAL_SPEED);
    transform.Translate(x0, y0);
}

void Camera::zoomOut()
{
    transform.Scale(ZOOM_SPEED, ZOOM_SPEED);
}

void Camera::zoomIn()
{
    transform.Scale(-ZOOM_SPEED, -ZOOM_SPEED);
}

void Camera::reset()
{
    transform.Reset();
}
