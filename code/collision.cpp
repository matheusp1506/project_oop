#include "collision.h"
#include <QDebug>

bool checkBounds(float c1, float c2, float size1, float size2) {
    float min1 = c1 - size1 / 2;
    float max1 = c1 + size1 / 2;
    float min2 = c2 - size2 / 2;
    float max2 = c2 + size2 / 2;

    return (min1 <= max2 && max1 >= min2);
}

Collision::Collision(dfn::E_Collision tp, dfn::Point2D pos, float dim1, float dim2)
{
    type = tp;
    dim[0] = dim1;
    dim[1] = dim2;
    position = pos;
    future = pos;
}

// I haven't yet implemented Circle collision, so for now it's possibility is completely ignorated
bool Collision::isColliding(Collision *other)
{
    return checkBounds(position.x, other->position.x, dim[0], other->dim[0]) &&
           checkBounds(position.y, other->position.y, dim[1], other->dim[1]);
}

bool Collision::willCollide(Collision *other)
{
    //qDebug() << future.x << " " << future.y << " " << other->position.x << " " << other->position.y;
    return checkBounds(future.x, other->position.x, dim[0], other->dim[0]) &&
           checkBounds(future.y, other->position.y, dim[1], other->dim[1]);
}
