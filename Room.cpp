#include "Room.h"
#include "engine/Engine.h"
#include "engine/TextureLibrary.h"

Room::Room(float posX, float posY, uint32_t width, uint32_t height)
{
    _floor.setTexture("floor");

    // testcube
    //// bottom
    //tri.p[0] = olc::GFX3D::vec3d{-1, -1, -1};
    //tri.p[1] = olc::GFX3D::vec3d{-1,  1, -1};
    //tri.p[2] = olc::GFX3D::vec3d{ 1, -1, -1};
    //_mesh.tris.push_back(tri);
    //
    //// top
    //tri.p[0] = olc::GFX3D::vec3d{-1, -1,  1};
    //tri.p[1] = olc::GFX3D::vec3d{-1,  1,  1};
    //tri.p[2] = olc::GFX3D::vec3d{ 1, -1,  1};
    //_mesh.tris.push_back(tri);
    //
    //// left
    //tri.p[0] = olc::GFX3D::vec3d{-1, -1, -1};
    //tri.p[1] = olc::GFX3D::vec3d{-1,  1, -1};
    //tri.p[2] = olc::GFX3D::vec3d{-1, -1,  1};
    //_mesh.tris.push_back(tri);
    //
    //// right
    //tri.p[0] = olc::GFX3D::vec3d{ 1, -1, -1};
    //tri.p[1] = olc::GFX3D::vec3d{ 1,  1, -1};
    //tri.p[2] = olc::GFX3D::vec3d{ 1, -1,  1};
    //_mesh.tris.push_back(tri);
    //
    //// front
    //tri.p[0] = olc::GFX3D::vec3d{-1, -1, -1};
    //tri.p[1] = olc::GFX3D::vec3d{ 1, -1, -1};
    //tri.p[2] = olc::GFX3D::vec3d{-1, -1,  1};
    //_mesh.tris.push_back(tri);
    //
    //// back
    //tri.p[0] = olc::GFX3D::vec3d{-1,  1, -1};
    //tri.p[1] = olc::GFX3D::vec3d{ 1,  1, -1};
    //tri.p[2] = olc::GFX3D::vec3d{-1,  1,  1};
    //_mesh.tris.push_back(tri);
}

Room::~Room()
{ }

void Room::draw()
{
    _floor.draw();
}
