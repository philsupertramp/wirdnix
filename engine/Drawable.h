#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "Engine.h"

class Drawable
{
protected:
    // for easy access to the engine
    Engine& engine = Engine::instance();

public:
//    Drawable();

    virtual void draw() = 0;

};

#endif // DRAWABLE_H
