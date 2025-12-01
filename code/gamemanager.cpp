#include "gamemanager.h"

GameManager& GameManager::instance() {
    static GameManager inst;
    return inst;
}

void GameManager::newGame() {
    _gw->updateSize(_width, _height);
    _gw->loadScene();
}

void GameManager::loadGame() {

}

void GameManager::dealWithInput(QKeyEvent *event, bool press)
{
    if(event->key() == Qt::Key_W) {
        _keys.data.forward = press;
    }
    if(event->key() == Qt::Key_A) {
        _keys.data.left = press;
    }
    if(event->key() == Qt::Key_S) {
        _keys.data.back = press;
    }
    if(event->key() == Qt::Key_D) {
        _keys.data.right = press;
    }
    if(event->key() == Qt::Key_E && canInteract) {
        _keys.data.interact = press;
        _gw->interact();
    }
    if(event->key() == Qt::Key_Space && isInteracting) {
        if(!_keys.data.update && press) {
            _gw->updateInteraction();
        }
        _keys.data.update = press;
    }
}

void GameManager::updatePlayer()
{
    if(_p == nullptr || isInteracting) {
        return;
    }
    float x=0, y=0;
    if(_keys.data.forward) {
        y += sqrt(2);
        x += sqrt(2);
    }
    if(_keys.data.left) {
        x += sqrt(2);
        y -= sqrt(2);
    }
    if(_keys.data.back) {
        y -= sqrt(2);
        x -= sqrt(2);
    }
    if(_keys.data.right) {
        x -= sqrt(2);
        y += sqrt(2);
    }

    _p->move(x*dfn::SPEED, y*dfn::SPEED);
}
