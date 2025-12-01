#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include <QRectF>
#include <QString>
#include <QTimer>
#include "player.h"
#include "textbox.h"

class GameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GameScene(int scene = 0, int w=320, int h=240, QObject *parent = nullptr);
    bool loadFromJson(int sceneIndex);
    Player* getPlayer() {
        return m_player;
    }
    void interact();

    void updateInteraction();
signals:
    void updateCycle();
    void interactionCall(bool inter);
    void interactionBegin(bool inter);

private:
    void loadBackground(const QString& path);
    void loadPlayer(const QJsonObject& obj);
    void loadObjects(const QJsonArray& arr);
    dfn::Point2D convertToScreenSpace(const dfn::Point2D pos);
    void showInteraction();
    void hideInteraction();
    void endInteraction();


    QString m_backgroundPath;
    QPixmap* m_playerSheet = nullptr;
    QGraphicsPixmapItem* m_backgroundItem = nullptr;
    Player* m_player = nullptr;
    std::vector<GameObject*> _objects;
    QTimer *_timer;
    //QGraphicsRectItem* dialogBox = nullptr;
    //QGraphicsTextItem* speaker = nullptr, *text = nullptr, *interactText = nullptr;

    TextBox *interactBox = nullptr, *dialogBox = nullptr, *speakerBox = nullptr;

    float _mult = 1;
    int _windowSquareX = 0, _windowSquareY = 0, _sceneCoordX = 0, _sceneCoordY = 0;
    int _sceneSizeX = 0, _sceneSizeY = 0;
    int interactIndex = 0;

    GameObject *interactObj = nullptr;
    bool interaction = false, started = false;
};

#endif // GAMESCENE_H
