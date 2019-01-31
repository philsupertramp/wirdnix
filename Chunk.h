#ifndef CHUNK_H
#define CHUNK_H

#include "engine/Renderable.h"
#include "engine/olcPixelGameEngine.h"
#include "engine/olcPGEX_Graphics3D.h"


class Chunk
    : public Renderable
{
protected:
    float _posX;
    float _posY;
    uint32_t _width;
    uint32_t _height;

    olc::Pixel _backgroundColor;
    olc::Sprite _sprite;

public:
    Chunk(float posX, float posY, uint32_t _width = CHUNK_WIDTH, uint32_t _height = CHUNK_HEIGHT);

    ~Chunk();

    //jnl in pixels for now
    const static uint32_t CHUNK_WIDTH = 200;
    const static uint32_t CHUNK_HEIGHT = CHUNK_WIDTH;

    void draw();

    void setBackgroundColor(olc::Pixel const& color);
};

#endif // CHUNK_H
