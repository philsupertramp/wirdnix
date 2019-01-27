#include "Camera.h"

Camera::Camera(WorldPos posX, WorldPos posY)
    : _posX(posX)
    , _posY(posY)
{ }

Camera::~Camera()
{
}

void Camera::changePosBy(WorldPos x, WorldPos y)
{
    _posX += x;
    _posY += y;
}
