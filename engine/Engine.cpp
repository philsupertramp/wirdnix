#include "Engine.h"
#include "olcPixelGameEngine.h"
#include "../Room.h"

Engine::Engine()
{
    sAppName = "widnix"; // hehe
}

void Engine::drawTestImage()
{
    // big origin
    Chunk c(-100, -100, 200, 200);
    c.draw();

    // origin
    Chunk d(-10, -10, 20, 20);
    d.setBackgroundColor(olc::RED);
    d.draw();

    {
        // one
        Chunk d(-10 + 100, -10, 20, 20);
        d.setBackgroundColor(olc::GREEN);
        d.draw();
    }
    {
        // -one
        Chunk d(-10 - 100, -10, 20, 20);
        d.setBackgroundColor(olc::BLUE);
        d.draw();
    }
    {
        // -i
        Chunk d(-10, -10 + 100, 20, 20);
        d.setBackgroundColor(olc::CYAN);
        d.draw();
    }
    {
        // i
        Chunk d(-10, -10 - 100, 20, 20);
        d.setBackgroundColor(olc::YELLOW);
        d.draw();
    }
    //Room r(10, 10);
    //r.setBackgroundColor(olc::GREEN);
    //r.draw();


    /// create coordinate sprite
    int32_t coordWidth = 500;
    static olc::Sprite coords(coordWidth+100, coordWidth+100);
    static bool coordsFilled = false;
    if (!coordsFilled)
    {
        SetPixelMode(olc::Pixel::Mode::NORMAL);
        FillRect(coords, 0, 0, coordWidth+100, coordWidth+100, olc::Pixel(0,255,255,0)); // transparent
        SetPixelMode(olc::Pixel::Mode::ALPHA);

        for (int i = 0; i <= coordWidth; i += 100)
        {
            for (int j = 0; j <= coordWidth; j += 100)
            {
                DrawString(coords, i, j, "(" + std::to_string(i) + "," + std::to_string(j) + ")", olc::Pixel(255,255,0,100));
            }
        }
        coordsFilled = true; // dont fill again every frame
    }
    DrawSprite(0, 0, &coords);
    olc::PixelGameEngine::DrawSprite(0,0, &coords);
}

// Called once at the start, so create things here
bool Engine::OnUserCreate()
{
    //jnl for now, can be changed.
    //jnl probably a good idea to set it in every function that does/doesnt need it
    SetPixelMode(olc::Pixel::Mode::ALPHA);

    _drawTarget = GetDrawTarget();

    camera.reset();

    return true;
}

// called once per frame, draws random coloured pixels
bool Engine::OnUserUpdate(float fElapsedTime)
{
    SetDrawTarget(_drawTarget);

    Clear(olc::Pixel( 75,   0, 130, 255)); // to know where nothing has been drawn

    if (GetKey(olc::W).bHeld || GetKey(olc::UP).bHeld)
    {
        camera.moveUp();
    }

    if (GetKey(olc::A).bHeld || GetKey(olc::LEFT).bHeld)
    {
        camera.moveLeft();
    }

    if (GetKey(olc::S).bHeld || GetKey(olc::DOWN).bHeld)
    {
        camera.moveDown();
    }

    if (GetKey(olc::D).bHeld || GetKey(olc::RIGHT).bHeld)
    {
        camera.moveRight();
    }

    if (GetKey(olc::Q).bHeld || GetKey(olc::CTRL).bHeld)
    {
        camera.rotateLeft();
    }

    if (GetKey(olc::E).bHeld || GetKey(olc::NP0).bHeld)
    {
        camera.rotateRight();
    }

    if (GetKey(olc::SPACE).bHeld)
    {
        camera.reset();
    }

    SetDrawTarget(_drawTarget);
    drawTestImage();

    return true;
}

void Engine::FillRect(olc::Sprite& sprite, int32_t x, int32_t y, int32_t w, int32_t h, olc::Pixel const& p /* = olc::WHITE */)
{
    auto& engine = instance();

    engine.SetDrawTarget(&sprite);
    engine.olc::PixelGameEngine::FillRect(x, y, w, h, p);
    engine.SetDrawTarget(engine._drawTarget);
}

void Engine::DrawString(olc::Sprite& sprite, int32_t x, int32_t y, std::string const& sText, olc::Pixel const& col, uint32_t scale /* = 1 */)
{
    auto& engine = instance();

    engine.SetDrawTarget(&sprite);
    engine.olc::PixelGameEngine::DrawString(x, y, sText, col, scale);
    engine.SetDrawTarget(engine._drawTarget);
}

void Engine::DrawSprite(int32_t x, int32_t y, olc::Sprite* sprite, uint32_t scale /* = 1 */)
{
    SetDrawTarget(_drawTarget);

    // transform the location where the sprite shall be drawn as well
    float xf, yf;
    camera.transform.Forward(x, y, xf, yf);
    x = xf; y = yf;

    camera.transform.Translate(x, y);
    olc::GFX2D::DrawSprite(sprite, camera.transform);
    camera.transform.Translate(-x, -y);
}
