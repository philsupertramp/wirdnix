#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "Engine.h"
#include <string>
#include "TextureLibrary.h"

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

    virtual void draw()
    {
        if (_texture != nullptr)
        {
            engine.DrawMesh(_mesh, olc::GFX3D::RENDERFLAGS::RENDER_DEPTH | olc::GFX3D::RENDERFLAGS::RENDER_TEXTURED, _texture);
        }
        else
        {
            engine.DrawMesh(_mesh, olc::GFX3D::RENDERFLAGS::RENDER_FLAT | olc::GFX3D::RENDERFLAGS::RENDER_DEPTH);
        }
    }

    void setBackgroundColor(olc::Pixel const& newColor)
    {
        for (auto& t : _mesh.tris )
        {
            t.col = newColor;
        }
    }

    bool setTexture(std::string const& name)
    {
        _texture = TextureLibrary::get(name);
    }

    void addTriangle(olc::GFX3D::triangle const& tri)
    {
        _mesh.tris.push_back(tri);
    }

};

#endif // RENDERABLE_H
