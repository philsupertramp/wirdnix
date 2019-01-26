#include "Chunk.h"
#include "engine/olcPixelGameEngine.h"

Chunk::Chunk(WorldPos posX, WorldPos posY, size_t _width, size_t _height)
    : _posX(posX)
    , _posY(posY)
    , _width(_width)
    , _height(_height)
    , _backgroundColor(olc::DARK_YELLOW)
{ }

Chunk::~Chunk()
{
}

void Chunk::draw()
{
    engine.FillRect(_posX, _posY, _width, _height, _backgroundColor);
}

void Chunk::setBackgroundColor(olc::Pixel const& color)
{
    _backgroundColor = color;
}
