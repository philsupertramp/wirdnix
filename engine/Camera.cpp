#include "Camera.h"

Camera::Camera(WorldPos posX = 0, WorldPos posY = 0)
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
