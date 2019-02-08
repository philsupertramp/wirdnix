#include "Camera.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Engine.h"

const float Camera::MOVEMENT_SPEED = 20;
const float Camera::ROTATIONAL_SPEED = .9f;
const float Camera::ZOOM_SPEED = .00001f;

Camera::Camera()
{
//    reset();
}

Camera::~Camera()
{ }

void Camera::moveForward(float fElapsedTime /* = 0 */)
{
    olc::GFX3D::vec3d heading = (_lookat - _pos);
    heading.normalize();
    heading *= fElapsedTime * MOVEMENT_SPEED;

    _pos += heading;
    _lookat += heading;
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

void Camera::moveUp(float fElapsedTime /* = 0 */)
{
    olc::GFX3D::vec3d headingUp = _up;
    headingUp.normalize();
    headingUp *= fElapsedTime * MOVEMENT_SPEED;

    _pos -= headingUp;
    _lookat -= headingUp;
    SetCamera(_pos, _lookat, _up);
}

void Camera::moveDown(float fElapsedTime /* = 0 */)
{
    olc::GFX3D::vec3d headingUp = _up;
    headingUp.normalize();
    headingUp *= fElapsedTime * MOVEMENT_SPEED;

    _pos += headingUp;
    _lookat += headingUp;
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

void Camera::rollLeft(float fElapsedTime /* = 0 */)
{
    olc::GFX3D::vec3d heading = _lookat - _pos;
    heading.normalize();
    olc::GFX3D::mat4x4 rot = olc::GFX3D::Math::Mat_MakeRotationU(heading, -fElapsedTime * ROTATIONAL_SPEED);

    _up = rot * _up;
    _up.normalize();
    SetCamera(_pos, _lookat, _up);
}

void Camera::rollRight(float fElapsedTime /* = 0 */)
{
    olc::GFX3D::vec3d heading = _lookat - _pos;
    heading.normalize();
    olc::GFX3D::mat4x4 rot = olc::GFX3D::Math::Mat_MakeRotationU(heading, fElapsedTime * ROTATIONAL_SPEED);

    _up = rot * _up;
    _up.normalize();
    SetCamera(_pos, _lookat, _up);
}


//TODO upon starting, constantly pitching up does not go all the way, the crossproduct goes to 0 vector,
// the dotProd of heading and _up goes to 1 from 0 at the start
void Camera::pitchUp(float fElapsedTime)
{
    std::cout << std::endl;
    float angleY = -fElapsedTime * ROTATIONAL_SPEED;

    olc::GFX3D::vec3d heading = (_lookat - _pos);
    heading.normalize();

    _up.normalize();
    olc::GFX3D::vec3d cross = heading & _up;
    std::cout <<  "cross pre normalize "<< cross << "  heading * up = " << heading * _up << std::endl;
    cross.normalize();

    std::cout << __FUNCTION__ << "  up" << _up << "  x" << cross << "  h" << heading << std::endl;

    olc::GFX3D::mat4x4 rot = olc::GFX3D::Math::Mat_MakeRotationU(cross, angleY);
//    std::cout << " rot " << std::endl << rot ;

    _up = rot * _up;
    _up.normalize();
    _lookat = ( rot * (_lookat - _pos) ) + _pos;
    std::cout << "  up" << _up << std::endl;
    SetCamera(_pos, _lookat, _up);
}

void Camera::pitchDown(float fElapsedTime)
{
    float angleY = fElapsedTime * ROTATIONAL_SPEED;

    olc::GFX3D::vec3d cross = (_lookat - _pos) & _up;
    cross.normalize();

    olc::GFX3D::mat4x4 rot = olc::GFX3D::Math::Mat_MakeRotationU(cross, angleY);

    _up = rot * _up;
    SetCamera(_pos, _lookat, _up);
}

void Camera::yawLeft(float fElapsedTime)
{
    float angleX = -fElapsedTime * ROTATIONAL_SPEED;

    _up.normalize();
    olc::GFX3D::mat4x4 rot = olc::GFX3D::Math::Mat_MakeRotationU(_up, angleX);

    olc::GFX3D::vec3d toRotate = (_lookat - _pos);

    std::cout << "toRotateLength " << toRotate.length();
    toRotate = rot * toRotate;

    std::cout << " rotatedLength  "<< toRotate.length() << " up " << _up << std::endl;

    _lookat = ( rot * (_lookat - _pos) ) + _pos;
    SetCamera(_pos, _lookat, _up);
}

void Camera::yawRight(float fElapsedTime)
{
    float angleX = fElapsedTime * ROTATIONAL_SPEED;

    olc::GFX3D::vec3d cross = (_lookat - _pos) & _up;
    cross.normalize();

    olc::GFX3D::vec3d upNormalized = _up;
    upNormalized.normalize();

    olc::GFX3D::mat4x4 rot = olc::GFX3D::Math::Mat_MakeRotationU(upNormalized, angleX);

    _lookat = ( rot * (_lookat - _pos) ) + _pos;
    SetCamera(_pos, _lookat, _up);
}

void Camera::resetRotation()
{

    //_angleX = 0;
    //_angleY = 0;
    //defineCamera();
}

void Camera::reset()
{
    float lookHeight = 11;
    _pos = {12.5,12.5,lookHeight};
    _lookat = {12.5,0,lookHeight};
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
