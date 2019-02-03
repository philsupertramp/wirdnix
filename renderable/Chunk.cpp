#include "Chunk.h"
#include "../engine/olcPixelGameEngine.h"
#include "../engine/olcPGEX_Graphics3D.h"

Chunk::Chunk(float posX, float posY, uint32_t _width, uint32_t _height, float posZ)
    : _posX(posX)
    , _posY(posY)
    , _width(_width)
    , _height(_height)
    , _backgroundColor(olc::DARK_YELLOW)
    , q(posX, posY, posZ, _width, _height)
{
    q.setBackgroundColor(_backgroundColor);
}

Chunk::~Chunk()
{ }

void Chunk::draw()
{
    q.draw();
}

void Chunk::setBackgroundColor(olc::Pixel const& color)
{
    _backgroundColor = color;

    q.setBackgroundColor(color);
}

bool Chunk::setTexture(std::string const& name)
{
    return q.setTexture(name);
}
