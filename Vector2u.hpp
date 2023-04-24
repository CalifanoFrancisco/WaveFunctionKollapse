#ifndef VECTOR2U_HPP
#define VECTOR2U_HPP

struct Vector2u {
    unsigned int x, y;

    Vector2u(unsigned int _x, unsigned int _y): x(_x), y(_y) { }
    
    Vector2u():x(0), y(0) { }
    
    bool operator==(const Vector2u& b) {
        if (this->x == b.x && this->y == b.y) return true;
        return false;
    }

    bool operator!=(const Vector2u& b) {
        return !(operator==(b));
    }

    Vector2u& operator=(const Vector2u& b){
        if (this != &b) 
        {
            this->x = b.x;
            this->y = b.y;
        }
        return *this;
    }
};

#endif