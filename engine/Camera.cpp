#include "Camera.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Engine.h"

const float Camera::MOVEMENT_SPEED = 100;
const float Camera::ROTATIONAL_SPEED = .9f;
const float Camera::ZOOM_SPEED = .00001f;

Camera::Camera()
{
    reset();
}

Camera::~Camera()
{ }

void Camera::moveForward(float fElapsedTime /* = 0 */)
{
    _pos.y += fElapsedTime * MOVEMENT_SPEED;
    SetCamera(_pos, _lookat, _up);
}

void Camera::moveBackward(float fElapsedTime /* = 0 */)
{
    _pos.y -= fElapsedTime * MOVEMENT_SPEED;
    SetCamera(_pos, _lookat, _up);
}

void Camera::moveLeft(float fElapsedTime /* = 0 */)
{
    _pos.x -= fElapsedTime * MOVEMENT_SPEED;
    SetCamera(_pos, _lookat, _up);
}

void Camera::moveRight(float fElapsedTime /* = 0 */)
{
    _pos.x += fElapsedTime * MOVEMENT_SPEED;
    SetCamera(_pos, _lookat, _up);
}

void Camera::rotateLeft(float fElapsedTime /* = 0 */)
{
    //TODO rotate up
}

void Camera::rotateRight(float fElapsedTime /* = 0 */)
{
    //TODO rotate up
}

void Camera::moveUp(float fElapsedTime /* = 0 */)
{
    _pos.z += fElapsedTime * MOVEMENT_SPEED;
    SetCamera(_pos, _lookat, _up);
}


void Camera::moveDown(float fElapsedTime /* = 0 */)
{
    _pos.z -= fElapsedTime * MOVEMENT_SPEED;
    SetCamera(_pos, _lookat, _up);
}

void Camera::reset()
{
    _pos = {0,0,0};
    _lookat  ={1,0,0};
    _up = {0,0,1};
    SetCamera(_pos, _lookat, _up);
    SetProjection(90, 1, 0.1, 10, 0, 0, (float)Engine::ScreenWidth(), (float)Engine::ScreenHeight()); //jnl no idea yet about these numbers
    olc::GFX3D::mat4x4 einheit;
    einheit.m[0][0] = 1;
    einheit.m[1][1] = 1;
    einheit.m[2][2] = 1;
    einheit.m[3][3] = 1;
    SetTransform(einheit);
}

void Camera::iterate()
{
    return;
    _lookat.x += .1;
    _lookat.y += .2;
    _lookat.z += .07;

    float d = 10;
    if (_lookat.x > d) _lookat.x = -d;
    if (_lookat.y > d) _lookat.y = -d;
    if (_lookat.z > d) _lookat.z = -d;
    SetCamera(_pos, _lookat, _up);
}
