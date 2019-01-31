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
    olc::GFX3D::vec3d dir = (_lookat - _pos);
    dir.normalize();
    dir *= fElapsedTime * MOVEMENT_SPEED;

    _pos += dir;
    _lookat += dir;
    SetCamera(_pos, _lookat, _up);
}

void Camera::moveBackward(float fElapsedTime /* = 0 */)
{
    olc::GFX3D::vec3d dir = (_lookat - _pos);
    dir.normalize();
    dir *= fElapsedTime * MOVEMENT_SPEED;

    _pos -= dir;
    _lookat -= dir;
    SetCamera(_pos, _lookat, _up);
}

void Camera::moveLeft(float fElapsedTime /* = 0 */)
{
    olc::GFX3D::vec3d cross = (_lookat - _pos) & _up;
    cross.normalize();
    cross *= fElapsedTime * MOVEMENT_SPEED;

    _pos += cross;
    _lookat += cross;
    SetCamera(_pos, _lookat, _up);
}

void Camera::moveRight(float fElapsedTime /* = 0 */)
{
    olc::GFX3D::vec3d cross = (_lookat - _pos) & _up;
    cross.normalize();
    cross *= fElapsedTime * MOVEMENT_SPEED;

    _pos -= cross;
    _lookat -= cross;
    SetCamera(_pos, _lookat, _up);
}

void Camera::rotateLeft(float fElapsedTime /* = 0 */)
{
    olc::GFX3D::vec3d heading = _lookat - _pos;
    heading.normalize();
    olc::GFX3D::mat4x4 rot = olc::GFX3D::Math::Mat_MakeRotationU(heading, fElapsedTime * ROTATIONAL_SPEED);

    _up = olc::GFX3D::Math::Mat_MultiplyVector(rot, _up);
    SetCamera(_pos, _lookat, _up);
}

void Camera::rotateRight(float fElapsedTime /* = 0 */)
{
    olc::GFX3D::vec3d heading = _lookat - _pos;
    heading.normalize();
    olc::GFX3D::mat4x4 rot = olc::GFX3D::Math::Mat_MakeRotationU(heading, -fElapsedTime * ROTATIONAL_SPEED);

    _up = olc::GFX3D::Math::Mat_MultiplyVector(rot, _up);
    SetCamera(_pos, _lookat, _up);
}

void Camera::moveUp(float fElapsedTime /* = 0 */)
{
    olc::GFX3D::vec3d dir = _up;
    dir.normalize();
    dir *= fElapsedTime * MOVEMENT_SPEED;

    _pos -= dir;
    _lookat -= dir;
    SetCamera(_pos, _lookat, _up);
}

void Camera::moveDown(float fElapsedTime /* = 0 */)
{
    olc::GFX3D::vec3d dir = _up;
    dir.normalize();
    dir *= fElapsedTime * MOVEMENT_SPEED;

    _pos += dir;
    _lookat += dir;
    SetCamera(_pos, _lookat, _up);
}

void Camera::reset()
{
    _pos = {0,0,100}; // above zero
    _lookat = {0,0,0}; // zero
    _up = {0,-10,0}; //- since y is downward
    SetCamera(_pos, _lookat, _up);
    SetProjection(110, (float)Engine::ScreenHeight()/(float)Engine::ScreenWidth(), -0.1f, 10, 0, 0, (float)Engine::ScreenWidth(), (float)Engine::ScreenHeight()); //jnl no idea yet about these numbers
    olc::GFX3D::mat4x4 I = olc::GFX3D::Math::Mat_MakeIdentity();
    SetTransform(I);
}

void Camera::iterate()
{
    return;
    _lookat.x += .1f;
    _lookat.y += .2f;
    _lookat.z += .07f;

    float d = 10;
    if (_lookat.x > d) _lookat.x = -d;
    if (_lookat.y > d) _lookat.y = -d;
    if (_lookat.z > d) _lookat.z = -d;
    SetCamera(_pos, _lookat, _up);
}
