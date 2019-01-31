#ifndef ROOM_H
#define ROOM_H

#include "Chunk.h"
#include "engine/olcPixelGameEngine.h"

class Room
    : public Chunk
{
    olc::Sprite _rand;

public:
    Room(float posX, float posY, uint32_t _width = Room::ROOM_WIDTH, uint32_t _height = Room::ROOM_HEIGHT);
    ~Room();

    //jnl in pixels for now
    const static size_t ROOM_WIDTH = 50;
    const static size_t ROOM_HEIGHT = ROOM_WIDTH;

    void draw();
};

#endif // ROOM_H
