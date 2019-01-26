#ifndef CAMERA_H
#define CAMERA_H

typedef size_t WorldPos;

class Camera
{
    //jnl middlePoint currently
    //  the camera has no rotation so far and no zoom
    WorldPos _posX;
    WorldPos _posY;

    // maybe make the camera move, accelerate etc and get slowed down by drag
    double _velocityX;
    double _velocityY;

public:
    Camera(WorldPos posX = 0, WorldPos posY = 0);
    ~Camera();

    void changePosBy(WorldPos x = 0, WorldPos y = 0);
};

#endif // CAMERA_H
