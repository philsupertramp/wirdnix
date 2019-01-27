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
    olc::Sprite rect((int32_t)_width, (int32_t)_height);

    Engine::FillRect(rect, 0, 0, (int32_t)_width, (int32_t)_height, _backgroundColor);
    engine.DrawSprite(_posX, _posY, &rect);
}

void Chunk::setBackgroundColor(olc::Pixel const& color)
{
    _backgroundColor = color;
}
