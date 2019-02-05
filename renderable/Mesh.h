#ifndef MESH_H
#define MESH_H

#include "olcPixelGameEngine.h"
#include "olcPGEX_Graphics3D.h"
#include "Renderable.h"
#include <string>

class Mesh
    : protected Renderable
{

public:
    Mesh() = default;
    Mesh(std::string const& fileName);
    ~Mesh() {};

    using Renderable::setBackgroundColor;
    using Renderable::setTexture;
    void draw();

    void randomizeColors();

    bool loadFromOBJfile(std::string const& fileName);

};

#endif // MESH_H
