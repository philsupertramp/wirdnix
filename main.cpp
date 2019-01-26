#include "engine/olcPixelGameEngine.h"
// Override base class with your custom functionality
class Example : public olc::PixelGameEngine
{
public:
    Example()
    {
        sAppName = "Example";
    }
public:
    bool OnUserCreate() override
    {
        // Called once at the start, so create things here
        SetPixelMode(olc::Pixel::Mode::ALPHA);
        return true;
    }
    bool OnUserUpdate(float fElapsedTime) override
    {
        // called once per frame, draws random coloured pixels

        FillRect(rand() % 256, rand() % 240, 100, 100, olc::Pixel(rand() % 256, rand() % 256, rand() % 256, 10));
        return true;
    }
};
int main()
{
    Example demo;
    if (demo.Construct(256, 240, 4, 4))
        demo.Start();
    return 0;
}