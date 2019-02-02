#include "Engine.h"
#include "olcPixelGameEngine.h"
#include "../Room.h"
#include <algorithm>
#include "TextureLibrary.h"

int32_t Engine::_nScreenWidth = 100;
int32_t Engine::_nScreenHeight = 100;

Engine::Engine()
{
    sAppName = "widnix"; // hehe

    // dont put anything else here that has something to do with the pge,
    //       initialize in onUserCreate
    // for example loading files into sprites wont work here
}

Engine::~Engine()
{ }

void Engine::drawTestImage()
{
    float zFight = .5;

    for (size_t i = 0; i < 1; i++)
    {
        // big origin
        Chunk c(-100, -100, 200, 200, zFight +i);
        olc::Sprite* rasen = TextureLibrary::get("Rasen");
        c.draw(rasen);

        // big origin
        Chunk d(-100, -100, 200, 200, -zFight+i);
        d.draw(TextureLibrary::get("dirt"));

    }
    //// origin
    //Chunk d(-10, -10, 20, 20);
    //d.setBackgroundColor(olc::RED);
    //d.draw();

    //{
    //    // one
    //    Chunk d(-10 + 100, -10, 20, 20);
    //    d.setBackgroundColor(olc::GREEN);
    //    d.draw();
    //}
    //{
    //    // -one
    //    Chunk d(-10 - 100, -10, 20, 20);
    //    d.setBackgroundColor(olc::BLUE);
    //    d.draw();
    //}
    //{
    //    // -i
    //    Chunk d(-10, -10 + 100, 20, 20);
    //    d.setBackgroundColor(olc::CYAN);
    //    d.draw();
    //}
    //{
    //    // i
    //    Chunk d(-10, -10 - 100, 20, 20);
    //    d.setBackgroundColor(olc::YELLOW);
    //    d.draw();
    //}

    //static Room r(10, 10);
    //r.setBackgroundColor(olc::GREEN);
    //r.draw();



    return;

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
//    DrawMesh(0, 0, &coords);
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

    TextureLibrary::add("../Images/Rasen.png");
    TextureLibrary::add("../Images/dirt.png");

    return true;
}

// called once per frame, draws random coloured pixels
bool Engine::OnUserUpdate(float fElapsedTime)
{
    SetDrawTarget(_drawTarget);

    Clear(olc::Pixel( 75,   0, 130, 255)); // to know where nothing has been drawn

    if (GetKey(olc::W).bHeld || GetKey(olc::UP).bHeld)
    {
        camera.moveUp(fElapsedTime);
    }

    if (GetKey(olc::A).bHeld || GetKey(olc::LEFT).bHeld)
    {
        camera.moveLeft(fElapsedTime);
    }

    if (GetKey(olc::S).bHeld || GetKey(olc::DOWN).bHeld)
    {
        camera.moveDown(fElapsedTime);
    }

    if (GetKey(olc::D).bHeld || GetKey(olc::RIGHT).bHeld)
    {
        camera.moveRight(fElapsedTime);
    }

    if (GetKey(olc::Q).bHeld || GetKey(olc::CTRL).bHeld)
    {
        camera.rotateLeft(fElapsedTime);
    }

    if (GetKey(olc::E).bHeld || GetKey(olc::NP0).bHeld)
    {
        camera.rotateRight(fElapsedTime);
    }

    if (GetKey(olc::R).bHeld || GetKey(olc::NP_ADD).bHeld)
    {
        camera.moveForward(fElapsedTime);
    }

    if (GetKey(olc::F).bHeld || GetKey(olc::NP_SUB).bHeld)
    {
        camera.moveBackward(fElapsedTime);
    }

    if (GetKey(olc::SPACE).bHeld)
    {
        camera.reset();
    }

    SetDrawTarget(_drawTarget);
    drawTestImage();
    camera.iterate(fElapsedTime);
    camera.refresh();

    return true;
}

olc::rcode Engine::Construct(uint32_t screen_w, uint32_t screen_h, uint32_t pixel_w, uint32_t pixel_h)
{
    return olc::PixelGameEngine::Construct(_nScreenWidth =  screen_w, _nScreenHeight = screen_h, pixel_w, pixel_h);
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

int32_t Engine::ScreenWidth()
{
    return _nScreenWidth;
}

int32_t Engine::ScreenHeight()
{
    return _nScreenHeight;
}

void Engine::DrawMesh(olc::GFX3D::mesh& m, uint32_t flags /* = olc::GFX3D::RENDERFLAGS::RENDER_CULL_CW | olc::GFX3D::RENDERFLAGS::RENDER_TEXTURED | olc::GFX3D::RENDERFLAGS::RENDER_DEPTH */, olc::Sprite* tex /* = nullptr */)
{
    SetPixelMode(olc::Pixel::Mode::NORMAL);
    SetDrawTarget(_drawTarget);

    //// only wire, not flat, not textured
    //flags &= ~olc::GFX3D::RENDERFLAGS::RENDER_FLAT | olc::GFX3D::RENDERFLAGS::RENDER_WIRE;

    if (tex != nullptr)
    {
        camera.SetTexture(tex);
        camera.Render(m.tris, flags | olc::GFX3D::RENDERFLAGS::RENDER_TEXTURED & ~olc::GFX3D::RENDERFLAGS::RENDER_FLAT | olc::GFX3D::RENDERFLAGS::RENDER_WIRE);
    }
    else
    {
        // certainly dont render it textured
        camera.Render(m.tris, flags & ~olc::GFX3D::RENDERFLAGS::RENDER_TEXTURED | olc::GFX3D::RENDERFLAGS::RENDER_CULL_CW);
    }
}
