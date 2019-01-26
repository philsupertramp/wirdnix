#ifndef ENGINE_H
#define ENGINE_H

#include "olcPixelGameEngine.h"

// Override base class with your custom functionality
class Engine :
    public olc::PixelGameEngine
{
private:
    Engine();

public:
    static Engine& instance()
    {
        static Engine e = Engine();
        return e;
    }

    bool OnUserCreate() override;
    bool OnUserUpdate(float fElapsedTime) override;
};

#endif // ENGINE_H
