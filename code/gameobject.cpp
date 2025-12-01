#include "gameobject.h"

GameObject::GameObject(QGraphicsPixmapItem *item, int id)
{
    _graphic = item;
    future.x = 0;
    future.y = 0;
    _id = id;
}

void GameObject::cancelUpdate()
{
    future = position;
}

void GameObject::update()
{
    position.x = future.x;
    position.y = future.y;
}

void GameObject::move(float x, float y)
{
    future.x += x;
    future.y += y;
    float temp = sqrt(pow(future.x-position.x,2)+pow(future.y-position.y,2));
    if(temp>dfn::SPEED) {
        future.x = position.x + (future.x-position.x)*dfn::SPEED/temp;
        future.y = position.y + (future.y-position.y)*dfn::SPEED/temp;
    }
    if(_interaction != nullptr)
        _interaction->move(future);
    _col->move(future);
}

QString GameObject::getItem() const
{
    return item;
}

void GameObject::setItem(const QString &newItem)
{
    item = newItem;
}

void GameObject::createCollision(float x, float y) {
    _col = new Collision(dfn::E_Collision::Rectangle, position, x, y);
}

void GameObject::createInteraction(float x, float y)
{
    interactable = true;
    _interaction = new Collision(dfn::E_Collision::Rectangle, position, x, y);
}
