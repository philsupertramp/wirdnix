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
        for (int i = -length; i <= length; ++i)
        {
            for (int j = -length; j <= length; ++j)
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
    TextureLibrary::add("../images/ceiling.png");

    obj.loadFromOBJfile("../objects/axis.obj");
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

//    std::cout << camera._up << std::endl;

    return true;
}

void Engine::handleUserInput(float fElapsedTime /* = 0 */)
{
    bool ignoreCamera = Shell::instance().isWaiting();
    if(ignoreCamera)
    {
        Shell::instance().setInput(mapInput(Shell::instance().getInput()));
        if (GetKey(olc::ESCAPE).bReleased)
        {
            Shell::instance().setWaiting(false);
        }
        else if (GetKey(olc::ENTER).bReleased)
        {
            Shell::instance().sendUserMessage();
            Shell::instance().setWaiting(false);
        }
    }
    else
    {
        if ((GetKey(olc::W).bHeld || GetKey(olc::UP).bHeld))
        {
            camera.moveForward(fElapsedTime);
        }

        if ((GetKey(olc::A).bHeld || GetKey(olc::LEFT).bHeld))
        {
            camera.moveLeft(fElapsedTime);
        }

        if ((GetKey(olc::S).bHeld || GetKey(olc::DOWN).bHeld))
        {
            camera.moveBackward(fElapsedTime);
        }

        if ((GetKey(olc::D).bHeld || GetKey(olc::RIGHT).bHeld))
        {
            camera.moveRight(fElapsedTime);
        }

        if ((GetKey(olc::Q).bHeld || GetKey(olc::CTRL).bHeld))
        {
            camera.rollLeft(fElapsedTime);
        }

        if ((GetKey(olc::E).bHeld || GetKey(olc::NP0).bHeld))
        {
            camera.rollRight(fElapsedTime);
        }

        if ( GetKey(olc::NP4).bHeld )
        {
            camera.yawLeft(fElapsedTime);
        }

        if ( GetKey(olc::NP6).bHeld )
        {
            camera.yawRight(fElapsedTime);
        }

        if ( GetKey(olc::NP8).bHeld )
        {
            camera.pitchUp(fElapsedTime);
        }

        if ( GetKey(olc::NP2).bHeld )
        {
            camera.pitchDown(fElapsedTime);
        }

        //if ( GetKey(olc::NP5).bHeld )
        //{
        //    camera.resetRotation(); // removed
        //}

        if ((GetKey(olc::R).bHeld || GetKey(olc::NP_ADD).bHeld))
        {
            camera.moveUp(fElapsedTime);
        }

        if ((GetKey(olc::F).bHeld || GetKey(olc::NP_SUB).bHeld))
        {
            camera.moveDown(fElapsedTime);
        }

        if ((GetKey(olc::SPACE).bPressed))
        {
            camera.reset();
        }

        if ((GetKey(olc::TAB).bPressed))
        {
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
        camera.Render(m.tris, flags | olc::GFX3D::RENDERFLAGS::RENDER_TEXTURED & ~olc::GFX3D::RENDERFLAGS::RENDER_FLAT /*| olc::GFX3D::RENDERFLAGS::RENDER_WIRE*/ | olc::GFX3D::RENDERFLAGS::RENDER_CULL_CCW);
    }
    else
    {
        // certainly dont render it textured
        camera.Render(m.tris, flags & ~olc::GFX3D::RENDERFLAGS::RENDER_TEXTURED | olc::GFX3D::RENDERFLAGS::RENDER_CULL_CW);
    }
}

std::string Engine::mapInput(std::string const& _input)
{
    std::vector<char> keyMap;

    keyMap.resize(100, '@'); // @ == not printable

    keyMap.at(olc::Key::A) = 'A'; keyMap.at(olc::Key::B) = 'B'; keyMap.at(olc::Key::C) = 'C'; keyMap.at(olc::Key::D) = 'D'; keyMap.at(olc::Key::E) = 'E'; keyMap.at(olc::Key::F) = 'F'; keyMap.at(olc::Key::G) = 'G'; keyMap.at(olc::Key::H) = 'H';
    keyMap.at(olc::Key::I) = 'I'; keyMap.at(olc::Key::J) = 'J'; keyMap.at(olc::Key::K) = 'K'; keyMap.at(olc::Key::L) = 'L'; keyMap.at(olc::Key::M) = 'M'; keyMap.at(olc::Key::N) = 'N'; keyMap.at(olc::Key::O) = 'O'; keyMap.at(olc::Key::P) = 'P';
    keyMap.at(olc::Key::Q) = 'Q'; keyMap.at(olc::Key::R) = 'R'; keyMap.at(olc::Key::S) = 'S'; keyMap.at(olc::Key::T) = 'T'; keyMap.at(olc::Key::U) = 'U'; keyMap.at(olc::Key::V) = 'V'; keyMap.at(olc::Key::W) = 'W'; keyMap.at(olc::Key::X) = 'X';
    keyMap.at(olc::Key::Y) = 'Y'; keyMap.at(olc::Key::Z) = 'Z';
    keyMap.at(olc::Key::K0) = keyMap.at(olc::Key::NP0) = '0'; keyMap.at(olc::Key::K1) = keyMap.at(olc::Key::NP1) = '1'; keyMap.at(olc::Key::K2) = keyMap.at(olc::Key::NP2) = '2'; keyMap.at(olc::Key::K3) = keyMap.at(olc::Key::NP3) = '3';
    keyMap.at(olc::Key::K4) = keyMap.at(olc::Key::NP4) = '4'; keyMap.at(olc::Key::K5) = keyMap.at(olc::Key::NP5) = '5'; keyMap.at(olc::Key::K6) = keyMap.at(olc::Key::NP6) = '6'; keyMap.at(olc::Key::K7) = keyMap.at(olc::Key::NP7) = '7';
    keyMap.at(olc::Key::K8) = keyMap.at(olc::Key::NP8) = '8'; keyMap.at(olc::Key::K9) = keyMap.at(olc::Key::NP9) = '9';
    keyMap.at(olc::Key::SPACE ) = ' '; keyMap.at(olc::Key::TAB   ) = '\t';keyMap.at(olc::Key::DEL       ) = '\b';keyMap.at(olc::Key::BACK  ) = '\b'; keyMap.at(olc::Key::RETURN) = '\n';keyMap.at(olc::Key::ENTER ) = '\n';keyMap.at(olc::Key::NP_MUL    ) = '*';
    keyMap.at(olc::Key::NP_DIV) = '/'; keyMap.at(olc::Key::NP_ADD) = '+'; keyMap.at(olc::Key::NP_SUB) = '-'; keyMap.at(olc::Key::NP_DECIMAL) = ',';


    std::string input;

    for (size_t i = 0; i <= olc::Key::NP_DECIMAL; i++)
    {
        if (olc::PixelGameEngine::GetKey(olc::Key(i)).bPressed)
        {
            input += keyMap[i];
        }
    }

    /*
     * Special treatment for shift
     */
    bool uppercaseToggle = Shell::instance().getInputMessage()._messageUppercase;
    if (GetKey(olc::SHIFT).bPressed && !uppercaseToggle || GetKey(olc::SHIFT).bReleased && uppercaseToggle)
    {
        Shell::instance().getInputMessage().toggleUppercase();
    }

    if(Shell::instance().getInputMessage()._messageUppercase)
    {
        // TODO: keyboard layout == de!
        for (auto & c: input)
        {
            int current_char = (int) c;
            if((int) 'Z' >= current_char && current_char >= (int) 'A' || (int) 'z' >= current_char && current_char >= (int) 'a')
            {
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
    //if (GetKey(olc::BACK).bReleased)
    //{
    //    input = input.substr(0, input.size() - 1);
    //    if(input.size() == 1){
    //        input = "";
    //    }
    //}

    return input;
}