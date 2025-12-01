#include "gamewindow.h"
#include "gamemanager.h"
#include <QDebug>

GameWindow::GameWindow(QWidget *parent) {
    _viewport = new QGraphicsView(this);
    _viewport->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _viewport->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _viewport->setFrameStyle(QFrame::NoFrame);            // removes gray frame
    _viewport->setAlignment(Qt::AlignLeft | Qt::AlignTop); // prevents centering
    _viewport->setBackgroundBrush(Qt::black);              // or any color you like
    //_layout = new QVBoxLayout(this);
    //_layout->addWidget(_viewport);
    //setLayout(_layout);
    _scene = nullptr;
}

void GameWindow::loadScene()
{
    if(_scene != nullptr) {
        delete _scene;
    }
    GameManager &game = GameManager::instance();
    _scene = new GameScene(game.getIndex(), game.getWidth(), game.getHeight(), this);
    connect(_scene, &GameScene::updateCycle, this, [=] {
        GameManager::instance().updatePlayer();
    });

    connect(_scene, &GameScene::interactionCall, this, [=](bool a) {
        setInteraction(a);
    });

    connect(_scene, &GameScene::interactionBegin, this, [=](bool a) {
        GameManager::instance().interacting(a);
    });

    game.setPlayer(_scene->getPlayer());
    _viewport->setScene(_scene);
}

void GameWindow::updateSize(int width, int height)
{
    _viewport->resize(width, height);
}

void GameWindow::setInteraction(bool interactable)
{
    GameManager::instance().setInteraction(interactable);
}

void GameWindow::interact()
{
    _scene->interact();
}

void GameWindow::updateInteraction()
{
    _scene->updateInteraction();
}

void GameWindow::keyPressEvent(QKeyEvent *event)
{
    GameManager &game = GameManager::instance();
    game.dealWithInput(event, true);
}

void GameWindow::keyReleaseEvent(QKeyEvent *event)
{
    GameManager &game = GameManager::instance();
    game.dealWithInput(event, false);
}

void GameWindow::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);
}
