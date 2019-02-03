#include "Quadrilateral.h"
#include "../engine/Engine.h"
#include "../engine/TextureLibrary.h"
#include "../engine/olcPixelGameEngine.h"
#include "../engine/olcPGEX_Graphics3D.h"

const olc::Pixel Quadrilateral::DEFAULT_BACKGROUND_COLOR = olc::Pixel(128,   0, 128, 250);

void Quadrilateral::initPlane(float posX, float posY, float posZ, float width, float height)
{
    olc::GFX3D::triangle tri;
    tri.col = DEFAULT_BACKGROUND_COLOR;

    tri.p[0] = olc::GFX3D::vec3d(posX,         posY,          posZ);
    tri.p[1] = olc::GFX3D::vec3d(posX + width, posY,          posZ);
    tri.p[2] = olc::GFX3D::vec3d(posX,         posY + height, posZ);
    tri.t[0] = olc::GFX3D::vec2d( 0, 0);
    tri.t[1] = olc::GFX3D::vec2d( 1, 0);
    tri.t[2] = olc::GFX3D::vec2d( 0, 1);
    addTriangle(tri);

    tri.p[0] = olc::GFX3D::vec3d(posX + width, posY,          posZ);
    tri.p[1] = olc::GFX3D::vec3d(posX + width, posY + height, posZ);
    tri.p[2] = olc::GFX3D::vec3d(posX,         posY + height, posZ);
    tri.t[0] = olc::GFX3D::vec2d( 1, 0);
    tri.t[1] = olc::GFX3D::vec2d( 1, 1);
    tri.t[2] = olc::GFX3D::vec2d( 0, 1);
    addTriangle(tri);
}

Quadrilateral::Quadrilateral(float posX, float posY, float posZ, float width, float height, std::string const& textureName /* = "" */)
{
    initPlane(posX, posY, posZ, width, height);
    if (textureName.size() > 0)
    {
        setTexture(textureName);
    }
}

Quadrilateral::Quadrilateral(float posX, float posY, float posZ, float width, float height, olc::Pixel const& backgroundColor)
{
    initPlane(posX, posY, posZ, width, height);
    setBackgroundColor(backgroundColor);
}

Quadrilateral::~Quadrilateral()
{ }

//void Quadrilateral::draw()
//{
//    _plane.draw();
//}
