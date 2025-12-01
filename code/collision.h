#ifndef COLLISION_H
#define COLLISION_H

#include "defines.h"

class Collision
{
public:
    Collision(dfn::E_Collision tp, dfn::Point2D pos, float dim1, float dim2 = 0);
    bool isColliding(Collision *other);
    bool willCollide(Collision *other);
    void completeMove() {
        position = future;
    }
    void move(dfn::Point2D newPos) {
        future = newPos;
    }

    friend std::ostream &operator<<(std::ostream &output, const Collision &c);

private:
    dfn::E_Collision type;
    dfn::Point2D position, future;
    float dim[2];
};

#endif // COLLISION_H
