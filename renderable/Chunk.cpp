#include "Chunk.h"
#include "../engine/olcPixelGameEngine.h"
#include "../engine/olcPGEX_Graphics3D.h"

Chunk::Chunk(olc::GFX3D::vec3d const& pos, float width, float height)
{
    olc::GFX3D::vec3d sizeX(width,      0, 0);
    olc::GFX3D::vec3d sizeY(0    , height, 0);
    q.initPlane(pos, sizeX, sizeY);
    q.setBackgroundColor(olc::DARK_YELLOW);
}

Chunk::~Chunk()
{ }

void Chunk::draw()
{
    q.draw();
}

void Chunk::setBackgroundColor(olc::Pixel const& color)
{
    q.setBackgroundColor(color);
}

bool Chunk::setTexture(std::string const& name)
{
    return q.setTexture(name);
}
