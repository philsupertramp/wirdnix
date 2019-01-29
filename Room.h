#ifndef ROOM_H
#define ROOM_H

#include "Chunk.h"
#include "engine/olcPixelGameEngine.h"

class Room
    : public Chunk
{
public:
    Room(WorldPos posX, WorldPos posY, size_t _width = Room::ROOM_WIDTH, size_t _height = Room::ROOM_HEIGHT);
    ~Room();

    //jnl in pixels for now
    const static size_t ROOM_WIDTH = 20;
    const static size_t ROOM_HEIGHT = ROOM_WIDTH;
};

#endif // ROOM_H
