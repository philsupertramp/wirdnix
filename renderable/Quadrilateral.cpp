#include "Quadrilateral.h"
#include "../engine/Engine.h"
#include "../engine/TextureLibrary.h"
#include "../engine/olcPixelGameEngine.h"
#include "../engine/olcPGEX_Graphics3D.h"

const olc::Pixel Quadrilateral::DEFAULT_BACKGROUND_COLOR = olc::Pixel(128,   0, 128, 250);

void Quadrilateral::initPlane(olc::GFX3D::vec3d const& pos, olc::GFX3D::vec3d const& width, olc::GFX3D::vec3d const& height)
{
    olc::GFX3D::triangle tri;
    tri.col = DEFAULT_BACKGROUND_COLOR;

    tri.p[0] = pos;
    tri.p[1] = pos + width;
    tri.p[2] = pos         + height;
    tri.t[0] = olc::GFX3D::vec2d( 0, 0);
    tri.t[1] = olc::GFX3D::vec2d( 1, 0);
    tri.t[2] = olc::GFX3D::vec2d( 0, 1);

    addTriangle(tri);

    tri.p[0] = pos + width;
    tri.p[1] = pos + width + height;
    tri.p[2] = pos         + height;
    tri.t[0] = olc::GFX3D::vec2d( 1, 0);
    tri.t[1] = olc::GFX3D::vec2d( 1, 1);
    tri.t[2] = olc::GFX3D::vec2d( 0, 1);
    addTriangle(tri);
}

Quadrilateral::Quadrilateral(olc::GFX3D::vec3d const& pos, olc::GFX3D::vec3d const& width, olc::GFX3D::vec3d const& height, std::string const& textureName /* = "" */)
{
    initPlane(pos, width, height);
    if (textureName.size() > 0)
    {
        setTexture(textureName);
    }
}

Quadrilateral::Quadrilateral(olc::GFX3D::vec3d const& pos, olc::GFX3D::vec3d const& width, olc::GFX3D::vec3d const& height, olc::Pixel const& backgroundColor)
{
    initPlane(pos, width, height);
    setBackgroundColor(backgroundColor);
}

Quadrilateral::~Quadrilateral()
{ }

//void Quadrilateral::draw()
//{
//    _plane.draw();
//}
