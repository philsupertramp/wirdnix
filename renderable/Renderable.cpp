#include "Renderable.h"


// returns success, if found in TextureLibrary

void Renderable::draw()
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

void Renderable::setBackgroundColor(olc::Pixel const & newColor)
{
    for (auto& t : _mesh.tris)
    {
        t.col = newColor;
    }
}

bool Renderable::setTexture(std::string const & name)
{
    if (!TextureLibrary::exists(name))
    {
        return false;
    }

    _texture = TextureLibrary::get(name);
    return true;
}

void Renderable::addTriangle(olc::GFX3D::triangle const & tri)
{
    _mesh.tris.push_back(tri);
}
