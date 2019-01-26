#include "Engine.h"

int main()
{
    Engine& thomas = Engine::instance();
    if (thomas.Construct(1000, 1000, 1, 1))
        thomas.Start();
    return 0;
}