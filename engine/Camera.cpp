#include "Camera.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Engine.h"

const float Camera::MOVEMENT_SPEED = 20;
const float Camera::ROTATIONAL_SPEED = .9f;
const float Camera::ZOOM_SPEED = .00001f;

olc::GFX3D::vec3d const& Camera::rotateLookAt()
{
    olc::GFX3D::vec3d cross = (_lookat - _pos) & _up;
    cross.normalize();

    olc::GFX3D::vec3d upNormalized = _up;
    upNormalized.normalize();

    olc::GFX3D::mat4x4 rot = olc::GFX3D::Math::Mat_MakeRotationU(upNormalized, _angleX);// *olc::GFX3D::Math::Mat_MakeRotationU(cross, _angleY);

    _lookCache = ( rot * (_lookat - _pos) ) + _pos;
    //SetCamera(_pos, _lookCache, _up);
    return _lookCache;
}

void Camera::defineCamera()
{
    // TODO dirty flag for rotateLookAt
    SetCamera(_pos, rotateLookAt(), _up);
}

Camera::Camera()
{
//    reset();
}

Camera::~Camera()
{ }

void Camera::moveForward(float fElapsedTime /* = 0 */)
{
    olc::GFX3D::vec3d dir = (_lookCache - _pos);
    dir.normalize();
    dir *= fElapsedTime * MOVEMENT_SPEED;

    _pos += dir;
    _lookat += dir;
    defineCamera();
}

void Camera::moveBackward(float fElapsedTime /* = 0 */)
{
    olc::GFX3D::vec3d dir = (_lookCache - _pos);
    dir.normalize();
    dir *= fElapsedTime * MOVEMENT_SPEED;

    _pos -= dir;
    _lookat -= dir;
    defineCamera();
}

void Camera::moveLeft(float fElapsedTime /* = 0 */)
{
    olc::GFX3D::vec3d cross = (_lookCache - _pos) & _up;
    cross.normalize();
    cross *= fElapsedTime * MOVEMENT_SPEED;

    _pos += cross;
    _lookat += cross;
    defineCamera();
}

void Camera::moveRight(float fElapsedTime /* = 0 */)
{
    olc::GFX3D::vec3d cross = (_lookCache - _pos) & _up;
    cross.normalize();
    cross *= fElapsedTime * MOVEMENT_SPEED;

    _pos -= cross;
    _lookat -= cross;
    defineCamera();
}

void Camera::rollLeft(float fElapsedTime /* = 0 */)
{
    olc::GFX3D::vec3d heading = _lookCache - _pos;
    heading.normalize();
    olc::GFX3D::mat4x4 rot = olc::GFX3D::Math::Mat_MakeRotationU(heading, -fElapsedTime * ROTATIONAL_SPEED);

    _up = rot * _up;
    defineCamera();
}

void Camera::rollRight(float fElapsedTime /* = 0 */)
{
    olc::GFX3D::vec3d heading = _lookCache - _pos;
    heading.normalize();
    olc::GFX3D::mat4x4 rot = olc::GFX3D::Math::Mat_MakeRotationU(heading, fElapsedTime * ROTATIONAL_SPEED);

    _up = rot * _up;
    _up.normalize();
    defineCamera();
}

void Camera::pitchUp(float fElapsedTime)
{
    _angleY += fElapsedTime * ROTATIONAL_SPEED;
    defineCamera();
}

void Camera::pitchDown(float fElapsedTime)
{
    _angleY -= fElapsedTime * ROTATIONAL_SPEED;
    defineCamera();
}

void Camera::yawLeft(float fElapsedTime)
{
    _angleX -= fElapsedTime * ROTATIONAL_SPEED;
    defineCamera();
}

void Camera::yawRight(float fElapsedTime)
{
    _angleX += fElapsedTime * ROTATIONAL_SPEED;
    defineCamera();
}

void Camera::resetRotation()
{
    _angleX = 0;
    _angleY = 0;
    defineCamera();
}

void Camera::moveUp(float fElapsedTime /* = 0 */)
{
    olc::GFX3D::vec3d dir = _up;
    dir.normalize();
    dir *= fElapsedTime * MOVEMENT_SPEED;

    _pos -= dir;
    _lookat -= dir;
    defineCamera();
}

void Camera::moveDown(float fElapsedTime /* = 0 */)
{
    olc::GFX3D::vec3d dir = _up;
    dir.normalize();
    dir *= fElapsedTime * MOVEMENT_SPEED;

    _pos += dir;
    _lookat += dir;
    defineCamera();
}

void Camera::reset()
{
    _angleX = 0;
    _angleY = 0;

    _pos = {12.5,12.5,10};
    _lookat = {12.5,12.5,0};
    _up = {0,10,0}; //- since y is downward
    defineCamera();
    SetProjection(110, (float)Engine::ScreenHeight()/(float)Engine::ScreenWidth(), .1f, 100, 0, 0, (float)Engine::ScreenWidth(), (float)Engine::ScreenHeight()); //jnl no idea yet about these numbers
    olc::GFX3D::mat4x4 I = olc::GFX3D::Math::Mat_MakeIdentity();
    SetTransform(I);

    olc::GFX3D::ConfigureDisplay();
}

void Camera::refresh()
{
    olc::GFX3D::ConfigureDisplay();
}

void Camera::iterate(float fElapsedTime /* = 0 */)
{
    olc::GFX3D::mat4x4 rotX = olc::GFX3D::Math::Mat_MakeRotationX(.5f * fElapsedTime);
    olc::GFX3D::mat4x4 rotY = olc::GFX3D::Math::Mat_MakeRotationY(.3f * fElapsedTime);
    olc::GFX3D::mat4x4 rotZ = olc::GFX3D::Math::Mat_MakeRotationZ(.2f * fElapsedTime);
    _pos = rotX * (rotY * (rotZ * _pos));
//    _pos.normalize();
//    _pos *= 10;
    defineCamera();
}
