#ifndef ENGINE_H
#define ENGINE_H

#include "olcPixelGameEngine.h"
#include "Camera.h"

// Override base class with your custom functionality

class Engine :
    private olc::PixelGameEngine
{
private:
    // engine is a singleton
    Engine();
    Camera camera;

    void drawTestImage();

    olc::Sprite* _drawTarget;
    bool OnUserCreate() override;
    bool OnUserUpdate(float fElapsedTime) override;

public:
    // engine is a singleton
    static Engine& instance()
    {
        static Engine e = Engine();
        return e;
    }

    using olc::PixelGameEngine::Construct;
    using olc::PixelGameEngine::Start;
    using olc::PixelGameEngine::SetDrawTarget;
    using olc::PixelGameEngine::GetDrawTarget;
    using olc::PixelGameEngine::GetDrawTargetWidth;
    using olc::PixelGameEngine::GetDrawTargetHeight;

    static void FillRect(olc::Sprite& sprite, int32_t x, int32_t y, int32_t w, int32_t h, olc::Pixel const& p = olc::WHITE);


    void DrawSprite(int32_t x, int32_t y, olc::Sprite* sprite, uint32_t scale = 1);
};

#endif // ENGINE_H
