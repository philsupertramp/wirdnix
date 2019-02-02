#include "Chunk.h"
#include "engine/olcPixelGameEngine.h"
#include "engine/olcPGEX_Graphics3D.h"

Chunk::Chunk(float posX, float posY, uint32_t _width, uint32_t _height, float posZ)
    : _posX(posX)
    , _posY(posY)
    , _width(_width)
    , _height(_height)
    , _backgroundColor(olc::DARK_YELLOW)
{
    olc::GFX3D::triangle tri;
    tri.col = _backgroundColor;

    tri.p[0] = olc::GFX3D::vec3d(posX,          posY,           posZ);
    tri.p[1] = olc::GFX3D::vec3d(posX + _width, posY,           posZ);
    tri.p[2] = olc::GFX3D::vec3d(posX,          posY + _height, posZ);
    tri.t[0] = olc::GFX3D::vec2d( 0, 0);
    tri.t[1] = olc::GFX3D::vec2d( 1, 0);
    tri.t[2] = olc::GFX3D::vec2d( 0, 1);
    r.addTriangle(tri);

    tri.p[0] = olc::GFX3D::vec3d(posX + _width, posY,           posZ);
    tri.p[1] = olc::GFX3D::vec3d(posX + _width, posY + _height, posZ);
    tri.p[2] = olc::GFX3D::vec3d(posX,          posY + _height, posZ);
    tri.t[0] = olc::GFX3D::vec2d( 1, 0);
    tri.t[1] = olc::GFX3D::vec2d( 1, 1);
    tri.t[2] = olc::GFX3D::vec2d( 0, 1);
    r.addTriangle(tri);
}

Chunk::~Chunk()
{ }

void Chunk::draw()
{
    r.draw();
}

void Chunk::setBackgroundColor(olc::Pixel const& color)
{
    _backgroundColor = color;

    r.setBackgroundColor(color);
}

bool Chunk::setTexture(std::string const& name)
{
    return r.setTexture(name);
}
