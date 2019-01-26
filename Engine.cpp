#include "Engine.h"
#include "olcPixelGameEngine.h"

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
    static double pos = 0;
    pos += fElapsedTime*100;
    size_t x = size_t(pos) % (olc::PixelGameEngine::ScreenWidth()+600) -300;
    olc::PixelGameEngine::Clear(olc::BLACK);
    FillCircle(x, olc::PixelGameEngine::ScreenHeight()/2, 300, olc::Pixel(0,200,0));
    return true;
}
