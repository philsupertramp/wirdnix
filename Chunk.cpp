#include "Chunk.h"
#include "engine/olcPixelGameEngine.h"
#include "engine/olcPGEX_Graphics3D.h"

Chunk::Chunk(float posX, float posY, size_t _width, size_t _height)
    : _posX(posX)
    , _posY(posY)
    , _width(_width)
    , _height(_height)
    , _backgroundColor(olc::DARK_YELLOW)
    , _sprite(10, 10)
{
    Engine::FillRect(_sprite, 0, 0, 10, 10, olc::Pixel(rand()%255, rand()%255, rand()%255));

    olc::GFX3D::triangle tri;
    tri.col = _backgroundColor;

    tri.p[0] = olc::GFX3D::vec3d{posX,          posY,           0};
    tri.p[1] = olc::GFX3D::vec3d{posX + _width, posY,           0};
    tri.p[2] = olc::GFX3D::vec3d{posX,          posY + _height, 0};
    tri.t[0] = olc::GFX3D::vec2d{ 0,  0};
    tri.t[1] = olc::GFX3D::vec2d{10,  0};
    tri.t[2] = olc::GFX3D::vec2d{ 0, 10};
    _mesh.tris.push_back(tri);

    tri.p[0] = olc::GFX3D::vec3d{posX + _width, posY,           0};
    tri.p[1] = olc::GFX3D::vec3d{posX + _width, posY + _height, 0};
    tri.p[2] = olc::GFX3D::vec3d{posX,          posY + _height, 0};
    tri.t[0] = olc::GFX3D::vec2d{10, 10};
    tri.t[1] = olc::GFX3D::vec2d{10,  0};
    tri.t[2] = olc::GFX3D::vec2d{ 0, 10};
    _mesh.tris.push_back(tri);
}

Chunk::~Chunk()
{
}

void Chunk::draw()
{
    engine.DrawMesh(_mesh, olc::GFX3D::RENDERFLAGS::RENDER_FLAT | olc::GFX3D::RENDERFLAGS::RENDER_WIRE | olc::GFX3D::RENDERFLAGS::RENDER_DEPTH);
}

void Chunk::setBackgroundColor(olc::Pixel const& color)
{
    _backgroundColor = color;

    for (auto& t:_mesh.tris)
    {
        t.col = color;
    }
}
