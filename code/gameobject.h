#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "defines.h"
#include "collision.h"
#include <QGraphicsItem>
#include <QDebug>

class GameObject
{
public:
    GameObject(QGraphicsPixmapItem *item, int id);
    void setPosition(dfn::Point2D pos) {
        position = pos;
        future = pos;
    }
    void setAnchor(dfn::Point2D pos) {
        distanceToAnchor = pos;
    }
    dfn::Point2D getPosition() {
        return position;
    }
    void updateGraphicPos(dfn::Point2D n) {
        if(_graphic == nullptr)
            return;
        int x = n.x-(distanceToAnchor.x*_scale);
        int y = n.y-(distanceToAnchor.y*_scale);
        _graphic->setZValue(-(position.x+position.y));
        _graphic->setPos(x, y);
    }
    void updateGraphicScale(float scale) {
        if(_graphic == nullptr)
            return;
        _graphic->setScale(scale);
        _scale = scale;
    }
    void cancelUpdate();
    void createCollision(float x, float y);
    void createInteraction(float x, float y);
    void update();
    void move(float x, float y);
    bool isInteractable() {
        return interactable;
    }
    int getId() {
        return _id;
    }
    Collision *getCollision() {
        return _col;
    }
    Collision *getInteractionZone() {
        return _interaction;
    }
    dfn::DialogStruct getDialog(int index) {
        return dialogs[index];
    }
    void addDialog(dfn::DialogStruct d) {
        dialogs.push_back(d);
    }
    int getDialogSize() {
        return dialogs.size();
    }
    void setIntType(dfn::E_Interaction t) {
        intType = t;
    }
    dfn::E_Interaction getIntType() {
        return intType;
    }

    QString getItem() const;
    void setItem(const QString &newItem);

private:
    dfn::Point2D position, distanceToAnchor, future;
    QGraphicsPixmapItem* _graphic = nullptr;
    float _scale = 1;
    Collision* _col = nullptr, *_interaction = nullptr;
    bool interactable = false;
    int _id;

    dfn::E_Interaction intType;
    QString item;
    std::vector<dfn::DialogStruct> dialogs;
};

#endif // GAMEOBJECT_H
