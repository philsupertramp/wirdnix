//
// Created by phil on 26.01.19.
//

#ifndef WIRDNIX_OBJECT_H
#define WIRDNIX_OBJECT_H

#include "Vec2D.h"
#include "engine/olcPixelGameEngine.h"


class RenderObject {
public:
    Vec2D position;
    olc::Sprite sprite;
    bool moves = false;

    RenderObject(): position(Vec2D(0, 0)), sprite(){};
    RenderObject(Vec2D& _position, olc::Sprite _sprite): position(_position), sprite(_sprite){}

    RenderObject(Vec2D& _position, olc::Sprite _sprite, bool& _moves)
            : position(_position), sprite(_sprite), moves(_moves){}

    virtual void draw() = 0;
};

class MovingRenderObject: public RenderObject {
public:
    double movement_speed;
    bool is_moving;
    size_t ticks_to_move;

    MovingRenderObject(){
        this->moves = true;
        this->movement_speed = 1;
        this->is_moving = false;
    }

    void draw() = 0;

    void move(Vec2D& p){
        this->is_moving = true;

    }
};



#endif //WIRDNIX_OBJECT_H
