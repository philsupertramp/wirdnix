#include "Camera.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Engine.h"

const float Camera::MOVEMENT_SPEED = 20;
const float Camera::ROTATIONAL_SPEED = .9f;
const float Camera::ZOOM_SPEED = .00001f;

void Camera::normalizeLookAt()
{
    _lookat = _pos + (_lookat - _pos).normalize();
}

Camera::Camera()
{
//    reset();
}

Camera::~Camera()
{ }

olc::GFX3D::vec3d const& Camera::getPos()
{
    return _pos;
}

olc::GFX3D::vec3d const& Camera::getUp()
{
    return _up;
}

olc::GFX3D::vec3d Camera::getHeading()
{
    return std::move((_lookat - _pos).normalize());
}

void Camera::moveForward(float fElapsedTime /* = 0 */)
{
    olc::GFX3D::vec3d heading = (_lookat - _pos).normalize();
    heading *= fElapsedTime * MOVEMENT_SPEED;
    SetCamera(_pos += heading,
              _lookat += heading,
              _up);
}

void Camera::moveBackward(float fElapsedTime /* = 0 */)
{
    olc::GFX3D::vec3d heading = (_lookat - _pos).normalize();
    heading *= fElapsedTime * MOVEMENT_SPEED;
    SetCamera(_pos -= heading,
              _lookat -= heading,
              _up);
}

void Camera::moveUp(float fElapsedTime /* = 0 */)
{
    olc::GFX3D::vec3d headingUp = _up;
    headingUp *= fElapsedTime * MOVEMENT_SPEED;
    SetCamera(_pos -= headingUp,
              _lookat -= headingUp,
              _up);
}

void Camera::moveDown(float fElapsedTime /* = 0 */)
{
    olc::GFX3D::vec3d headingUp = _up;
    headingUp *= fElapsedTime * MOVEMENT_SPEED;
    SetCamera(_pos += headingUp,
              _lookat += headingUp,
              _up);
}


void Camera::moveLeft(float fElapsedTime /* = 0 */)
{
    olc::GFX3D::vec3d cross = ((_lookat - _pos) & _up).normalize();
    cross *= fElapsedTime * MOVEMENT_SPEED;
    SetCamera(_pos += cross,
              _lookat += cross,
              _up);
}

void Camera::moveRight(float fElapsedTime /* = 0 */)
{
    olc::GFX3D::vec3d cross = ((_lookat - _pos) & _up).normalize();
    cross *= fElapsedTime * MOVEMENT_SPEED;
    SetCamera(_pos -= cross,
              _lookat -= cross,
              _up);
}

void Camera::rollLeft(float fElapsedTime /* = 0 */)
{
    olc::GFX3D::vec3d heading = (_lookat - _pos).normalize();
    olc::GFX3D::mat4x4 rot = olc::GFX3D::Math::Mat_MakeRotationU(heading, -fElapsedTime * ROTATIONAL_SPEED);
    SetCamera(_pos,
              _lookat,
              _up = (rot * _up).normalize() );
}

void Camera::rollRight(float fElapsedTime /* = 0 */)
{
    olc::GFX3D::vec3d heading = (_lookat - _pos).normalize();
    olc::GFX3D::mat4x4 rot = olc::GFX3D::Math::Mat_MakeRotationU(heading, fElapsedTime * ROTATIONAL_SPEED);
    SetCamera(_pos,
              _lookat,
              _up = (rot * _up).normalize() );
}

void Camera::pitchUp(float fElapsedTime)
{
    olc::GFX3D::vec3d heading = (_lookat - _pos).normalize();
    olc::GFX3D::vec3d cross = (heading & _up).normalize();
    olc::GFX3D::mat4x4 rot = olc::GFX3D::Math::Mat_MakeRotationU(cross, -fElapsedTime * ROTATIONAL_SPEED);
    SetCamera(_pos,
              _lookat = (rot * heading) + _pos,
              _up = (cross & heading).normalize() ); // dont rotate _up, recalculate
}

void Camera::pitchDown(float fElapsedTime)
{
    olc::GFX3D::vec3d heading = (_lookat - _pos).normalize();
    olc::GFX3D::vec3d cross = (heading & _up).normalize();
    olc::GFX3D::mat4x4 rot = olc::GFX3D::Math::Mat_MakeRotationU(cross, fElapsedTime * ROTATIONAL_SPEED);
    SetCamera(_pos,
              _lookat = (rot * heading) + _pos,
              _up = (cross & heading).normalize()); // dont rotate _up, recalculate
}

void Camera::yawLeft(float fElapsedTime)
{
    olc::GFX3D::mat4x4 rot = olc::GFX3D::Math::Mat_MakeRotationU(_up, -fElapsedTime * ROTATIONAL_SPEED);
    SetCamera(_pos,
              _lookat = ( rot * (_lookat - _pos) ) + _pos,
              _up);
}

void Camera::yawRight(float fElapsedTime)
{
    olc::GFX3D::mat4x4 rot = olc::GFX3D::Math::Mat_MakeRotationU(_up, fElapsedTime * ROTATIONAL_SPEED);
    SetCamera(_pos,
              _lookat = ( rot * (_lookat - _pos) ) + _pos,
              _up);
}

void Camera::reset()
{
    float lookHeight = 8;
    _pos = {12.5,12.5,lookHeight};
    _lookat = {12.5,13,lookHeight};
    _up = {0,0,-1}; //- since y is downward
    _up.normalize();
    SetCamera(_pos, _lookat, _up);

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
    SetCamera(_pos, _lookat, _up);
}
