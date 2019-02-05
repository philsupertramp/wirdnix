#include "Engine.h"
#include "olcPixelGameEngine.h"
#include "../renderable/Room.h"
#include <algorithm>
#include "TextureLibrary.h"
#include "../renderable/Chunk.h"
#include "olcPGEX_Graphics3D.h"
#include <vector>
#include "Shell.h"

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
    //float zFight = .5;

    //for (size_t i = 0; i < 1; i++)
    //{
    //    // big origin
    //    Chunk c(olc::GFX3D::vec3d(-100, -100, zFight +i), 200, 200);
    //    c.setTexture("rasen");
    //    c.draw();

    //    // big origin
    //    Chunk d(olc::GFX3D::vec3d(-100, -100, -zFight +i), 200, 200);
    //    d.setTexture("dirt");
    //    d.draw();

    //}

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

    static std::vector<Room> r;
    /*(-10, -10, 20, 20)*/

    static bool initted = false;
    if (!initted)
    {
        int length = 10;
        float gap = 5;
        float size = 25;
        for (int i = -length; i < length; ++i)
        {
            for (int j = -length; j < length; ++j)
            {
                r.push_back(Room(i*(size + gap), j*(size + gap), size, size));
            }
        }
        initted = true;
    }


    for (auto& room:r)
    {
        room.draw();
    }

    obj.draw();


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

    TextureLibrary::add("../images/rasen.png");
    TextureLibrary::add("../images/dirt.png");
    TextureLibrary::add("../images/floor.png");
    TextureLibrary::add("../images/wall.png");

    obj.loadFromOBJfile("../objects/teapot.obj");
    obj.randomizeColors();

    return true;
}

// called once per frame, draws random coloured pixels
bool Engine::OnUserUpdate(float fElapsedTime)
{
    SetDrawTarget(_drawTarget);

    // to know where nothing has been drawn
    Clear(olc::Pixel( 75,   0, 130, 255));

    handleUserInput(fElapsedTime);

    SetDrawTarget(_drawTarget);
    drawTestImage();
    Shell::instance().draw(fElapsedTime);

//    camera.iterate(fElapsedTime);
    camera.refresh();

    return true;
}

void Engine::handleUserInput(float fElapsedTime /* = 0 */)
{
    bool ignoreCamera = Shell::instance().isWaiting();
    if(ignoreCamera){
        Shell::instance().setInput(mapInput(Shell::instance().getInput()));
        if (GetKey(olc::ESCAPE).bReleased)
        {
            Shell::instance().toggleWaiting();
        }
        if (GetKey(olc::ENTER).bReleased)
        {
            Shell::instance().sendUserMessage();
        }
    }
    else {
        if ((GetKey(olc::W).bHeld || GetKey(olc::UP).bHeld)) {
            camera.moveUp(fElapsedTime);
        }

        if ((GetKey(olc::A).bHeld || GetKey(olc::LEFT).bHeld)) {
            camera.moveLeft(fElapsedTime);
        }

        if ((GetKey(olc::S).bHeld || GetKey(olc::DOWN).bHeld)) {
            camera.moveDown(fElapsedTime);
        }

        if ((GetKey(olc::D).bHeld || GetKey(olc::RIGHT).bHeld)) {
            camera.moveRight(fElapsedTime);
        }

        if ((GetKey(olc::Q).bHeld || GetKey(olc::CTRL).bHeld)) {
            camera.rotateLeft(fElapsedTime);
        }

        if ((GetKey(olc::E).bHeld || GetKey(olc::NP0).bHeld)) {
            camera.rotateRight(fElapsedTime);
        }

        if ((GetKey(olc::R).bHeld || GetKey(olc::NP_ADD).bHeld)) {
            camera.moveForward(fElapsedTime);
        }

        if ((GetKey(olc::F).bHeld || GetKey(olc::NP_SUB).bHeld)) {
            camera.moveBackward(fElapsedTime);
        }

        if ((GetKey(olc::SPACE).bHeld)) {
            camera.reset();
        }
        if ((GetKey(olc::TAB).bReleased)) {
            Shell::instance().toggleWaiting();
        }
    }


}

olc::rcode Engine::Construct(uint32_t screen_w, uint32_t screen_h, uint32_t pixel_w, uint32_t pixel_h)
{
    return olc::PixelGameEngine::Construct(_nScreenWidth =  screen_w, _nScreenHeight = screen_h, pixel_w, pixel_h);
}

void Engine::drawSpriteOnTop(olc::Sprite* sprite, uint32_t x /* = 0 */, uint32_t y /* = 0 */, uint32_t scale /* = 1 */)
{
    SetPixelMode(olc::Pixel::Mode::ALPHA);
    olc::PixelGameEngine::DrawSprite(x, y, sprite, scale);
}
void Engine::fillRectOnTop(olc::Pixel pixel, uint32_t x /* = 0 */, uint32_t y /* = 0 */, uint32_t w/* = 10 */, uint32_t h/* = 10 */, uint32_t scale /* = 1 */)
{
    SetPixelMode(olc::Pixel::Mode::ALPHA);
    olc::PixelGameEngine::FillRect(x, y, w*scale, h*scale, pixel);
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
        camera.Render(m.tris, flags | olc::GFX3D::RENDERFLAGS::RENDER_TEXTURED & ~olc::GFX3D::RENDERFLAGS::RENDER_FLAT /*| olc::GFX3D::RENDERFLAGS::RENDER_WIRE*/ );
    }
    else
    {
        // certainly dont render it textured
        camera.Render(m.tris, flags & ~olc::GFX3D::RENDERFLAGS::RENDER_TEXTURED | olc::GFX3D::RENDERFLAGS::RENDER_CULL_CW);
    }
}

std::string Engine::mapInput(std::string const& _input){
    std::string input = "";

    /**
     * Alphabetic characters
     */
    if (GetKey(olc::A).bReleased)
    {
        input += "a";
    }
    if (GetKey(olc::B).bReleased)
    {
        input += "b";
    }
    if (GetKey(olc::C).bReleased)
    {
        input += "c";
    }
    if (GetKey(olc::D).bReleased)
    {
        input += "d";
    }
    if (GetKey(olc::E).bReleased)
    {
        input += "e";
    }
    if (GetKey(olc::F).bReleased)
    {
        input += "f";
    }
    if (GetKey(olc::G).bReleased)
    {
        input += "g";
    }
    if (GetKey(olc::H).bReleased)
    {
        input += "h";
    }
    if (GetKey(olc::I).bReleased)
    {
        input += "i";
    }
    if (GetKey(olc::J).bReleased)
    {
        input += "j";
    }
    if (GetKey(olc::K).bReleased)
    {
        input += "k";
    }
    if (GetKey(olc::L).bReleased)
    {
        input += "l";
    }
    if (GetKey(olc::M).bReleased)
    {
        input += "m";
    }
    if (GetKey(olc::N).bReleased)
    {
        input += "n";
    }
    if (GetKey(olc::O).bReleased)
    {
        input += "o";
    }
    if (GetKey(olc::P).bReleased)
    {
        input += "p";
    }
    if (GetKey(olc::Q).bReleased)
    {
        input += "q";
    }
    if (GetKey(olc::R).bReleased)
    {
        input += "r";
    }
    if (GetKey(olc::S).bReleased)
    {
        input += "s";
    }
    if (GetKey(olc::T).bReleased)
    {
        input += "t";
    }
    if (GetKey(olc::U).bReleased)
    {
        input += "u";
    }
    if (GetKey(olc::V).bReleased)
    {
        input += "v";
    }
    if (GetKey(olc::W).bReleased)
    {
        input += "w";
    }
    if (GetKey(olc::X).bReleased)
    {
        input += "x";
    }
    if (GetKey(olc::Y).bReleased)
    {
        input += "y";
    }
    if (GetKey(olc::Z).bReleased)
    {
        input += "z";
    }
    /**
     * Numbers
     */

    if (GetKey(olc::K0).bReleased || GetKey(olc::NP0).bReleased)
    {
        input += "0";
    }
    if (GetKey(olc::K1).bReleased || GetKey(olc::NP1).bReleased)
    {
        input += "1";
    }
    if (GetKey(olc::K2).bReleased || GetKey(olc::NP2).bReleased)
    {
        input += "2";
    }
    if (GetKey(olc::K3).bReleased || GetKey(olc::NP3).bReleased)
    {
        input += "3";
    }
    if (GetKey(olc::K4).bReleased || GetKey(olc::NP4).bReleased)
    {
        input += "4";
    }
    if (GetKey(olc::K5).bReleased || GetKey(olc::NP5).bReleased)
    {
        input += "5";
    }
    if (GetKey(olc::K6).bReleased || GetKey(olc::NP6).bReleased)
    {
        input += "6";
    }
    if (GetKey(olc::K7).bReleased || GetKey(olc::NP7).bReleased)
    {
        input += "7";
    }
    if (GetKey(olc::K8).bReleased || GetKey(olc::NP8).bReleased)
    {
        input += "8";
    }
    if (GetKey(olc::K9).bReleased || GetKey(olc::NP9).bReleased)
    {
        input += "9";
    }
    /**
     * Special characters
     */


    else if (GetKey(olc::SPACE).bReleased)
    {
        input += " ";
    }
    else if (GetKey(olc::NP_SUB).bReleased)
    {
        input += "-";
    }
    else if (GetKey(olc::NP_ADD).bReleased)
    {
        input += "+";
    }
    else if (GetKey(olc::NP_DIV).bReleased)
    {
        input += "/";
    }
    else if (GetKey(olc::NP_MUL).bReleased)
    {
        input += "*";
    }
    else if (GetKey(olc::NP_DECIMAL).bReleased)
    {
        input += ",";
    }

    /*
     * Special treatment for shift
     */
    bool uppercaseToggle = Shell::instance().getActiveMessage()._messageUppercase;
    if (GetKey(olc::SHIFT).bPressed && !uppercaseToggle || GetKey(olc::SHIFT).bReleased && uppercaseToggle)
    {
        Shell::instance().getActiveMessage().toggleUppercase();
    }

    if(Shell::instance().getActiveMessage()._messageUppercase){
        // TODO: keyboard layout == de!
        for (auto & c: input)
        {
            int current_char = (int) c;
            if((int) 'Z' >= current_char && current_char >= (int) 'A' || (int) 'z' >= current_char && current_char >= (int) 'a') {
                c = toupper(c);
            }
            else if(current_char == (int) '1')
            {
                c = '!';
            }
            else if(current_char == (int) '2')
            {
                c = '"';
            }
            /*
             * § is not a regular ascii character.
             * */
            else if(current_char == (int) '4')
            {
                c = '$';
            }
            else if(current_char == (int) '5')
            {
                c = '%';
            }
            else if(current_char == (int) '6')
            {
                c = '&';
            }
            else if(current_char == (int) '7')
            {
                c = '/';
            }
            else if(current_char == (int) '8')
            {
                c = '(';
            }
            else if(current_char == (int) '9')
            {
                c = ')';
            }
            else if(current_char == (int) '0')
            {
                c = '=';
            }
        }
    }
    /**
     * Text modifications
     */
    input = _input + input;
    if (GetKey(olc::BACK).bReleased)
    {
        input = input.substr(0, input.size() - 1);
        if(input.size() == 1){
            input = "";
        }
    }
    
    return input;
}