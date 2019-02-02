#include "engine/Engine.h"
#include "util/Logger.h"

int main()
{
    float scale = 1;
    scale = std::max(floorf(scale), 1.f);
    float height = 720 / scale;
    float width = height / 9 * 16;

    Engine& thomas = Engine::instance();
    if (thomas.Construct((uint32_t)width, (uint32_t)height, (uint32_t)scale, (uint32_t)scale))
    {
        thomas.Start();
    }

    return 0;
}