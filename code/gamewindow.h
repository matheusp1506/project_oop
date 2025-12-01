#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QGraphicsView>
#include <QVBoxLayout>
#include "gamescene.h"

class GameWindow : public QWidget
{
    Q_OBJECT
public:
    explicit GameWindow(QWidget *parent = nullptr);
    void loadScene();
    void updateSize(int width, int height);
    void setInteraction(bool interactable);
    void interact();
    void updateInteraction();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private:
    QGraphicsView *_viewport;
    GameScene *_scene = nullptr;
    QVBoxLayout *_layout;
};

#endif // GAMEWINDOW_H
