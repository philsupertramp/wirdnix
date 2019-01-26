#include "Room.h"

Room::Room(WorldPos posX, WorldPos posY, size_t width, size_t height)
    : Chunk(posX, posY, width, height)
{ }

Room::~Room()
{ }
