#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "Engine.h"

class Renderable
{
protected:
    // for easy access to the engine
    Engine& engine = Engine::instance();

    olc::GFX3D::mesh _mesh;

public:
//    Renderable();

    virtual void draw() = 0;

};

#endif // RENDERABLE_H
