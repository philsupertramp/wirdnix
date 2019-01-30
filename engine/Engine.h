#ifndef ENGINE_H
#define ENGINE_H

#include "olcPixelGameEngine.h"
#include "Camera.h"
//#include "olcPGEX_Graphics3D.h"

// Override base class with your custom functionality

class Engine
    : private olc::PixelGameEngine
{
private:
    // engine is a singleton
    Engine();
    Camera camera;

    void drawTestImage();

    olc::Sprite* _drawTarget;
    bool OnUserCreate() override;
    bool OnUserUpdate(float fElapsedTime) override;

    static int32_t _nScreenWidth;
    static int32_t _nScreenHeight;

public:
    // engine is a singleton
    static Engine& instance()
    {
        static Engine e = Engine();
        return e;
    }

    olc::rcode Construct(uint32_t screen_w, uint32_t screen_h, uint32_t pixel_w = 1, uint32_t pixel_h = 1);
    using olc::PixelGameEngine::Start;
    using olc::PixelGameEngine::SetDrawTarget;
    using olc::PixelGameEngine::GetDrawTarget;
    using olc::PixelGameEngine::GetDrawTargetWidth;
    using olc::PixelGameEngine::GetDrawTargetHeight;

    static void FillRect(olc::Sprite& sprite, int32_t x, int32_t y, int32_t w, int32_t h, olc::Pixel const& p = olc::WHITE);
    static void DrawString(olc::Sprite& sprite, int32_t x, int32_t y, std::string const& sText, olc::Pixel const& col, uint32_t scale = 1);
    static int32_t ScreenWidth();
    static int32_t ScreenHeight();


    void DrawMesh(olc::GFX3D::mesh& m, uint32_t flags = olc::GFX3D::RENDERFLAGS::RENDER_CULL_CW | olc::GFX3D::RENDERFLAGS::RENDER_TEXTURED | olc::GFX3D::RENDERFLAGS::RENDER_DEPTH);
};

#endif // ENGINE_H
