#ifndef CHUNK_H
#define CHUNK_H

#include "../renderable/Quadrilateral.h"
#include "../engine/olcPixelGameEngine.h"
#include "../engine/olcPGEX_Graphics3D.h"
#include <string>

class Chunk
{
protected:
    Quadrilateral q;

public:
    Chunk(olc::GFX3D::vec3d const& pos, float width, float height);

    ~Chunk();

    //jnl in pixels for now
    const static uint32_t CHUNK_WIDTH = 200;
    const static uint32_t CHUNK_HEIGHT = CHUNK_WIDTH;

    void draw();

    void setBackgroundColor(olc::Pixel const& color);
    bool setTexture(std::string const& name);
};

#endif // CHUNK_H
