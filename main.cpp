#include "engine/Engine.h"

int main()
{
    Engine& thomas = Engine::instance();
    if (thomas.Construct(1280, 720, 1, 1))
        thomas.Start();
    return 0;
}