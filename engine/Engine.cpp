#include "Engine.h"
#include "olcPixelGameEngine.h"
#include "../Chunk.h"

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
    Chunk c(10,10);
    c.draw();
    return true;
}
