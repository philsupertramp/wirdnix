#ifndef CHUNK_H
#define CHUNK_H

#include "engine/Renderable.h"
#include "engine/olcPixelGameEngine.h"

typedef int WorldPos;

class Chunk
    : public Renderable
{
    WorldPos _posX;
    WorldPos _posY;
    size_t _width;
    size_t _height;

    olc::Pixel _backgroundColor;

public:
    Chunk(WorldPos posX, WorldPos posY, size_t _width = CHUNK_WIDTH, size_t _height = CHUNK_HEIGHT);

    ~Chunk();

    //jnl in pixels for now
    const static size_t CHUNK_WIDTH = 200;
    const static size_t CHUNK_HEIGHT = CHUNK_WIDTH;

    void draw();

    void setBackgroundColor(olc::Pixel const& color);
};

#endif // CHUNK_H
