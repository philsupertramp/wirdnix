#include "Engine.h"

Engine::Engine()
{
    sAppName = "widnix"; // hehe
}

// Called once at the start, so create things here
bool Engine::OnUserCreate()
{
    //jnl for now, can be changed.
    //jnl probably a good idea to set it in every function that does/doesnt need it
    SetPixelMode(olc::Pixel::Mode::ALPHA);

    return true;
}

// called once per frame, draws random coloured pixels
bool Engine::OnUserUpdate(float fElapsedTime)
{
    for (size_t i = 0; i < 10; i++)
    {
        FillCircle(olc::PixelGameEngine::ScreenHeight()/2, olc::PixelGameEngine::ScreenHeight()/2, 300, olc::Pixel(0,200,0));
    }
    return true;
}
