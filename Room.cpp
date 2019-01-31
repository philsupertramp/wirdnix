#include "Room.h"

Room::Room(float posX, float posY, uint32_t width, uint32_t height)
    : Chunk(posX, posY, width, height)
    , _rand(width, height)
{
    Engine::FillRect(_rand, 0, 0, (int32_t)_width, (int32_t)_height, _backgroundColor);
    for (uint32_t i = 0; i < _width; i++)
    {
        for (uint32_t j = 0; j < _height; j++)
        {
            _rand.SetPixel(i, j, olc::Pixel(rand() % 255, rand() % 255, rand() % 255));
        }
    }

    olc::GFX3D::triangle tri;
    tri.col = _backgroundColor;

    // bottom
    tri.p[0] = olc::GFX3D::vec3d{-1, -1, -1};
    tri.p[1] = olc::GFX3D::vec3d{-1,  1, -1};
    tri.p[2] = olc::GFX3D::vec3d{ 1, -1, -1};
    _mesh.tris.push_back(tri);

    // top
    tri.p[0] = olc::GFX3D::vec3d{-1, -1,  1};
    tri.p[1] = olc::GFX3D::vec3d{-1,  1,  1};
    tri.p[2] = olc::GFX3D::vec3d{ 1, -1,  1};
    _mesh.tris.push_back(tri);

    // left
    tri.p[0] = olc::GFX3D::vec3d{-1, -1, -1};
    tri.p[1] = olc::GFX3D::vec3d{-1,  1, -1};
    tri.p[2] = olc::GFX3D::vec3d{-1, -1,  1};
    _mesh.tris.push_back(tri);

    // right
    tri.p[0] = olc::GFX3D::vec3d{ 1, -1, -1};
    tri.p[1] = olc::GFX3D::vec3d{ 1,  1, -1};
    tri.p[2] = olc::GFX3D::vec3d{ 1, -1,  1};
    _mesh.tris.push_back(tri);

    // front
    tri.p[0] = olc::GFX3D::vec3d{-1, -1, -1};
    tri.p[1] = olc::GFX3D::vec3d{ 1, -1, -1};
    tri.p[2] = olc::GFX3D::vec3d{-1, -1,  1};
    _mesh.tris.push_back(tri);

    // back
    tri.p[0] = olc::GFX3D::vec3d{-1,  1, -1};
    tri.p[1] = olc::GFX3D::vec3d{ 1,  1, -1};
    tri.p[2] = olc::GFX3D::vec3d{-1,  1,  1};
    _mesh.tris.push_back(tri);
}

Room::~Room()
{ }

void Room::draw()
{
//  engine.DrawMesh(_posX, _posY, &_rand, 1);
    engine.DrawMesh(_mesh, olc::GFX3D::RENDERFLAGS::RENDER_WIRE);
}
