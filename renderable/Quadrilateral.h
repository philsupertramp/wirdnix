#ifndef QUADRILATERAL_H
#define QUADRILATERAL_H

#include "../engine/olcPixelGameEngine.h"
#include "../engine/olcPGEX_Graphics3D.h"
#include "Renderable.h"
#include <string>

class Quadrilateral
    : protected Renderable
{

public:
    // if you use the default constructor you need to initialize the plane via initPlane and set the texture and/or backgroundcolor separately
    // width and height are relative to the pos
    Quadrilateral() = default;
    void initPlane(olc::GFX3D::vec3d const& pos, olc::GFX3D::vec3d const& width, olc::GFX3D::vec3d const& height);

    Quadrilateral(olc::GFX3D::vec3d const& pos, olc::GFX3D::vec3d const& width, olc::GFX3D::vec3d const& height, std::string const& textureName = "");
    Quadrilateral(olc::GFX3D::vec3d const& pos, olc::GFX3D::vec3d const& width, olc::GFX3D::vec3d const& height, olc::Pixel const& backgroundColor);

    ~Quadrilateral();

    using Renderable::setBackgroundColor;
    using Renderable::setTexture;
    using Renderable::draw;

    static const olc::Pixel DEFAULT_BACKGROUND_COLOR; // = olc::Pixel(128, 0, 128, 250);

    //void draw();
};

#endif // QUADRILATERAL_H
