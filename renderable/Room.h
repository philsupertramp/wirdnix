#ifndef ROOM_H
#define ROOM_H

#include "../engine/olcPixelGameEngine.h"
#include "Quadrilateral.h"

class Room
{
    Quadrilateral _floor;
    Quadrilateral _wallNorth;
    Quadrilateral _wallEast;
    Quadrilateral _wallSouth;
    Quadrilateral _wallWest;

public:
    Room(float posX, float posY, float width = Room::ROOM_WIDTH, float length = Room::ROOM_LENGTH, float height = Room::ROOM_HEIGHT);
    ~Room();

    //jnl in pixels for now
    const static float ROOM_WIDTH;
    const static float ROOM_LENGTH;
    const static float ROOM_HEIGHT;

    void draw();
};

#endif // ROOM_H
