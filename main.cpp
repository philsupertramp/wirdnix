#include "engine/olcPixelGameEngine.h"
#include "Vec2D.h"
#include "RenderObject.h"
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
    Vec2D a = Vec2D(2., 1.);
    int32_t w = 10, h = 10;
    RenderObject q = RenderObject(a, olc::Sprite(w, h));
    std::cout << q.position.getX() << " " << q.position.getY() << std::endl;
    Example demo;
    if (demo.Construct(256, 240, 4, 4))
        demo.Start();
    return 0;
}