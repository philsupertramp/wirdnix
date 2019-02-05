#ifndef RENDERABLE_H
#define RENDERABLE_H

#include <string>
#include "TextureLibrary.h"
#include "olcPGEX_Graphics3D.h"
#include "olcPixelGameEngine.h"

class Renderable
{
protected:
    olc::GFX3D::mesh _mesh;
    olc::Sprite* _texture = nullptr;

public:
    Renderable() = default;
    virtual ~Renderable() = default;

    virtual void draw();

    void setBackgroundColor(olc::Pixel const& newColor);

    // returns success, if found in TextureLibrary
    bool setTexture(std::string const& name);

    void addTriangle(olc::GFX3D::triangle const& tri);
};

#endif // RENDERABLE_H
