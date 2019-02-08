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

    _floor.initPlane(posFloor, sizeX, sizeY*-1);
    _floor.setTexture("floor");

    _ceiling.initPlane(posFloor+sizeZ-sizeY, sizeX, sizeY);
    _ceiling.setTexture("ceiling");

    _wallNorth.initPlane(posFloor + sizeZ , sizeX , sizeZ*-1.f );
    _wallNorth.setTexture("wall");

    _wallSouth.initPlane(posFloor + sizeZ -sizeY+sizeX, sizeX*-1 , sizeZ*-1 );
    _wallSouth.setTexture("wall");

    _wallEast.initPlane(posFloor + sizeZ + sizeX, sizeY*-1 , sizeZ*-1.f);
    _wallEast.setTexture("wall");

    _wallWest.initPlane(posFloor + sizeZ - sizeY, sizeY, sizeZ*-1.f);
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
    _ceiling.draw();
}
