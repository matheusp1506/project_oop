#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "gamewindow.h"
#include "defines.h"
#include "player.h"
#include <QKeyEvent>

class GameManager
{
public:
    static GameManager& instance();
    void setGameWidget(GameWindow *gw) {
        _gw = gw;
    };
    void setPlayer(Player *p) {
        _p = p;
    }
    void newGame();
    void loadGame();
    int getIndex() {return sceneIndex;};
    void dealWithInput(QKeyEvent *event, bool press);
    void updatePlayer();
    void setSize(int w, int h) {_width = w;_height = h;};
    int getWidth() {return _width;};
    int getHeight() {return _height;};
    void setInteraction(bool interactable) {
        canInteract = interactable;
    }
    void interacting(bool i) {
        isInteracting = i;
    }

private:
    GameManager() = default;
    GameWindow *_gw;
    int sceneIndex = 0;
    int _width = 320;
    int _height = 240;
    Player *_p;
    dfn::COMMANDS _keys;
    bool canInteract = false;
    bool isInteracting = false;
};

#endif // GAMEMANAGER_H
