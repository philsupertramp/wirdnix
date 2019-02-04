#include "Room.h"
#include "../engine/Engine.h"
#include "../engine/TextureLibrary.h"
#include "olcPGEX_Graphics3D.h"

const float Room::ROOM_WIDTH = 50;
const float Room::ROOM_LENGTH = ROOM_WIDTH;
const float Room::ROOM_HEIGHT = 10;

Room::Room(float posX, float posY, float width, float length, float height)
{
    olc::GFX3D::vec3d posFloor(posX, posY, 0);
    olc::GFX3D::vec3d sizeX(width,      0,      0);
    olc::GFX3D::vec3d sizeY(    0, length,      0);
    olc::GFX3D::vec3d sizeZ(    0,      0, height);

    float angle = 1.25*2;
    olc::GFX3D::vec3d unitX(angle, 0, 0);
    olc::GFX3D::vec3d unitY(0, angle, 0);
    olc::GFX3D::vec3d unitZ(0, 0, angle);

    _floor.initPlane(posFloor, sizeX, sizeY);
    _floor.setTexture("floor");

    _wallNorth.initPlane(posFloor + sizeZ -unitY -unitX , sizeX + unitX*2, sizeZ*-1.f +unitY);
    _wallNorth.setTexture("wall");

    _wallSouth.initPlane(posFloor + sizeZ + sizeY +unitY-unitX, sizeX +unitX*2, sizeZ*-1.f -unitY);
    _wallSouth.setTexture("wall");

    _wallEast.initPlane(posFloor + sizeZ + sizeY -unitX+unitY, sizeY*-1 -unitY*2, sizeZ*-1.f+unitX);
    _wallEast.setTexture("wall");

    _wallWest.initPlane(posFloor + sizeZ + sizeY + sizeX+unitX+unitY, sizeY*-1 -unitY*2, sizeZ*-1.f-unitX);
    _wallWest.setTexture("wall");
}

Room::~Room()
{ }

void Room::draw()
{
    _wallNorth.draw();
    _wallSouth.draw();
    _wallEast.draw();
    _wallWest.draw();
    _floor.draw();
}
