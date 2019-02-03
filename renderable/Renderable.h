#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "../engine/Engine.h"
#include <string>
#include "../engine/TextureLibrary.h"

class Renderable
{
protected:
    // for easy access to the engine
    Engine& engine = Engine::instance();

    olc::GFX3D::mesh _mesh;
    olc::Sprite* _texture = nullptr;

public:
    Renderable() = default;
    ~Renderable() = default;

    virtual void draw();

    void setBackgroundColor(olc::Pixel const& newColor);

    // returns success, if found in TextureLibrary
    bool setTexture(std::string const& name);

    void addTriangle(olc::GFX3D::triangle const& tri);

};

#endif // RENDERABLE_H
