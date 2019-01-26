#ifndef WIRDNIX_VEC2D_H
#define WIRDNIX_VEC2D_H


class Vec2D{
public:
    double x = 0;
    double y = 0;

    Vec2D(double _x, double _y)
            : x(_x),y(_y){}

    double& getX(){
        return this->x;
    }

    double& getY(){
        return this->y;
    }

    void setX(double& new_x){
        this->x = new_x;
    }

    void setY(double& new_y){
        this->y = new_y;
    }

    void addX(double& append_x){
        this->x += append_x;
    }

    void addY(double& append_y){
        this->y += append_y;
    }

    Vec2D& Vec2D::operator - (const Vec2D& other){
        return Vec2D(this->getX() - other.getX(), this->getY() - other->getY());
    }
    Vec2D& Vec2D::operator + (const Vec2D& other){
        return Vec2D(this->getX() + other.getX(), this->getY() + other->getY());
    }
};


#endif //WIRDNIX_VEC2D_H
