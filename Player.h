//
// Created by phil on 26.01.19.
//

#ifndef WIRDNIX_PLAYER_H
#define WIRDNIX_PLAYER_H

#include "RenderObject.h"
#include "engine/olcPixelGameEngine.h"

const int32_t PLAYER_HEIGHT = 10;
const int32_t PLAYER_WIDTH = 5;

using namespace olc;
Sprite generate_player_model(){
    Sprite sprite = Sprite(PLAYER_WIDTH, PLAYER_HEIGHT);
    for(int i=0; i<PLAYER_WIDTH; i++)
        for(int j=0; j<PLAYER_HEIGHT; j++)
            sprite.SetPixel(i,j,Pixel(255, 255, 255));

    return sprite;
}


class Player: public MovingRenderObject {
public:
    Player(){
        this->moves = true;
        this->movement_speed = 1;
        this->sprite = generate_player_model();
    };
    Player(double& _x, double& _y){
        this->position.setX(_x);
        this->position.setY(_y);
    }
    void draw() override {
        olc::PixelGameEngine::DrawSprite(this->position.getX(), this->position.getY(), this->sprite);
    }
};

#endif //WIRDNIX_PLAYER_H
