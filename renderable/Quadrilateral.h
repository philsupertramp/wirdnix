#ifndef QUADRILATERAL_H
#define QUADRILATERAL_H

#include "../engine/olcPixelGameEngine.h"
#include "Renderable.h"
#include <string>

class Quadrilateral
    : protected Renderable
{
    void initPlane(float posX, float posY, float posZ, float width, float height);

public:
    Quadrilateral(float posX, float posY, float posZ, float width, float height, std::string const& textureName = "");
    Quadrilateral(float posX, float posY, float posZ, float width, float height, olc::Pixel const& backgroundColor);

    ~Quadrilateral();

    using Renderable::setBackgroundColor;
    using Renderable::setTexture;
    using Renderable::draw;

    static const olc::Pixel DEFAULT_BACKGROUND_COLOR; // = olc::Pixel(128, 0, 128, 250);

    //void draw();
};

#endif // QUADRILATERAL_H
