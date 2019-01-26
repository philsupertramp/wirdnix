#ifndef CHUNK_H
#define CHUNK_H

#include "engine/Drawable.h"

typedef int WorldPos;
class Chunk
    : public Drawable
{
    WorldPos _posX;
    WorldPos _posY;
    size_t _width;
    size_t _height;

public:
    Chunk(WorldPos posX, WorldPos posY, size_t _width = CHUNK_WIDTH, size_t _height = CHUNK_HEIGHT);

    ~Chunk();

    //jnl in pixels for now
    const static size_t CHUNK_WIDTH = 200;
    const static size_t CHUNK_HEIGHT = CHUNK_WIDTH;

    void draw();
};

#endif // CHUNK_H
