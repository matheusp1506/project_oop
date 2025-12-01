#include "gamescene.h"
#include <QGraphicsPixmapItem>
#include <QDebug>
#include <algorithm>

GameScene::GameScene(int scene, int w, int h, QObject *parent)
    : QGraphicsScene{parent}
{
    setSceneRect(0,0,w,h);

    int targetHeight = w * 3 / 4;
    if (targetHeight > h) {
        _windowSquareX = (w-h*4/3)/2;
        w = h * 4 / 3;
    } else {
        _windowSquareY = (h-targetHeight)/2;
    }

    _mult = w/320.0;

    setBackgroundBrush(QBrush(QColor(QColorConstants::Svg::black)));

    loadFromJson(scene);

    dialogBox = new TextBox(new QGraphicsTextItem(), new QGraphicsPixmapItem(QPixmap(":/assets/ui/input_outline_rectangle.png")), 192, w);
    dialogBox->setOpacity(0);
    dialogBox->getText()->setDefaultTextColor(QColor("black"));
    dialogBox->setPos(_windowSquareX, _windowSquareY+h-54*_mult);
    dialogBox->setZIndex(100);
    addItem(dialogBox->getText());
    addItem(dialogBox->getBox());

    speakerBox = new TextBox(new QGraphicsTextItem(), new QGraphicsPixmapItem(QPixmap(":/assets/ui/input_outline_rectangle.png")), 192, 192*std::min(_mult, 1.5f));
    speakerBox->setOpacity(0);
    speakerBox->getText()->setDefaultTextColor(QColor("black"));
    speakerBox->setPos(_windowSquareX, _windowSquareY+h-32*std::min(_mult, 1.5f)-54*_mult);
    speakerBox->setZIndex(100);
    addItem(speakerBox->getText());
    addItem(speakerBox->getBox());

    interactBox = new TextBox(new QGraphicsTextItem(), new QGraphicsPixmapItem(QPixmap(":/assets/ui/input_outline_rectangle.png")), 192, 220);
    interactBox->setOpacity(0);
    interactBox->setZIndex(100);
    interactBox->getText()->setDefaultTextColor(QColor("black"));
    QString text = "<p>Press <img src=\":/assets/ui/key_e.png\" height=\"%1\"style=\"vertical-align: middle; \"/> to interact </p>";
    text = text.arg(/*_mult**/16);
    interactBox->getText()->setHtml(text);
    interactBox->setPos(_windowSquareX+w-220, _windowSquareY);
    addItem(interactBox->getText());
    addItem(interactBox->getBox());

    _timer = new QTimer;
    QObject::connect(_timer, &QTimer::timeout, this, &GameScene::updateCycle);
    QObject::connect(_timer, &QTimer::timeout, this, [=]() {
        interactObj = nullptr;
        interaction = false;
        for(auto i : _objects) {
            if(m_player->getCollision()->willCollide(i->getCollision())) {
                m_player->cancelUpdate();
            }
            i->update();
            i->updateGraphicPos(convertToScreenSpace(i->getPosition()));
            if(i->isInteractable()) {
                if(m_player->getCollision()->willCollide(i->getInteractionZone())) {
                    interactObj = i;
                    interaction = true;
                }
            }
        }
        if(interaction) {
            emit interactionCall(true);
            showInteraction();
        } else {
            emit interactionCall(false);
            hideInteraction();
            started = false;
        }
        m_player->update();
        m_player->updateGraphicPos(convertToScreenSpace(m_player->getPosition()));
        emit advance();});
    _timer->start(1000 / 60);
}

bool GameScene::loadFromJson(int sceneIndex)
{
    QString filename = QString(":scenes/scene_%1.json").arg(sceneIndex);
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Failed to open scene file:" << filename;
        return false;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(data, &error);
    if (error.error != QJsonParseError::NoError) {
        qWarning() << "JSON parse error in" << filename << ":" << error.errorString();
        return false;
    }

    QJsonObject root = doc.object();

    clear(); // clear previous scene

    // Background
    if (root.contains("background"))
        loadBackground(root["background"].toString());
    if (root.contains("backgroundX"))
        _sceneCoordX = root["backgroundX"].toInt();
    if (root.contains("backgroundY"))
        _sceneCoordY = root["backgroundY"].toInt();
    if (root.contains("width"))
        _sceneSizeX = root["width"].toInt();
    if (root.contains("height"))
        _sceneSizeY = root["height"].toInt();

    // Player
    if (root.contains("player")) {
        loadPlayer(root["player"].toObject());
    }

    // Objects
    if (root.contains("objects"))
        loadObjects(root["objects"].toArray());
    return true;
}

void GameScene::interact()
{
    if(interactObj->getIntType() == dfn::E_Interaction::Dialog) {
        dialogBox->setOpacity(1);
        dialogBox->getText()->setPlainText(interactObj->getDialog(interactIndex).text);
        speakerBox->setOpacity(1);
        speakerBox->getText()->setPlainText(interactObj->getDialog(interactIndex).speaker);
        if(!started) {
            started = true;
            emit interactionBegin(true);
        }
    } else if(interactObj->getIntType() == dfn::E_Interaction::Item) {

    }
}

void GameScene::updateInteraction()
{
    if(interactObj->getDialogSize() > interactIndex+1) {
        interactIndex++;
        interact();
    } else {
        endInteraction();
    }
}

void GameScene::loadBackground(const QString& path)
{
    m_backgroundPath = path;
    QPixmap bg(path);
    if (bg.isNull()) {
        qWarning() << "Failed to load background:" << path;
        return;
    }
    m_backgroundItem = addPixmap(bg);
    m_backgroundItem->setZValue(-100); // behind everything
    m_backgroundItem->setScale(_mult);
    m_backgroundItem->setPos(_windowSquareX, _windowSquareY);
}

void GameScene::loadPlayer(const QJsonObject &obj)
{
    m_playerSheet = new QPixmap(obj["sprite"].toString());
    if(m_playerSheet->isNull()) {
        qWarning() << "Failed to load sprite:" << obj["sprite"].toString();
        return;
    }

    QPixmap playChar = m_playerSheet->copy(QRect(16,48,16,24));
    m_player = new Player(addPixmap(playChar));
    dfn::Point2D pos;
    pos.x = obj["x"].toInt();
    pos.y = obj["y"].toInt();
    m_player->setPosition(pos);
    pos.x = obj["anchor"]["x"].toInt();
    pos.y = obj["anchor"]["y"].toInt();
    m_player->setAnchor(pos);
    m_player->updateGraphicScale(_mult);
    m_player->updateGraphicPos(convertToScreenSpace(m_player->getPosition()));
    m_player->createCollision(obj["collision"]["x"].toDouble(), obj["collision"]["y"].toDouble());

    //GameManager::instance().setPlayer(m_player);
}

void GameScene::loadObjects(const QJsonArray &arr) {
    for(int i = 0; i<arr.size(); i++) {
        if(arr[i].isObject()) {
            QJsonObject temp = arr[i].toObject();
            QPixmap *sprite = nullptr;
            QGraphicsPixmapItem *item = nullptr;

            if(temp.contains("sprite")) {
                sprite = new QPixmap(temp["sprite"].toString());
                item = addPixmap(*sprite);
                //item->setZValue(-50);
            }

            GameObject *obj = new GameObject(item, i);
            dfn::Point2D point;
            point.x = temp["x"].toDouble();
            point.y = temp["y"].toDouble();
            obj->setPosition(point);
            obj->createCollision(temp["sizeX"].toDouble(), temp["sizeY"].toDouble());
            obj->updateGraphicScale(_mult);
            obj->updateGraphicPos(convertToScreenSpace(obj->getPosition()));
            if(temp.contains("anchor")) {
                point.x = temp["anchor"].toObject()["x"].toInt();
                point.y = temp["anchor"].toObject()["y"].toInt();
                obj->setAnchor(point);
            }
            if(temp.contains("interaction")) {
                QJsonObject tst = temp["interaction"].toObject();
                point.x = tst["sizeX"].toDouble();
                point.y =tst["sizeY"].toDouble();
                obj->createInteraction(point.x,point.y);

                if(tst["condition"].toBool()) {

                } else {
                    if(tst.contains("dialog")) {
                        obj->setIntType(dfn::E_Interaction::Dialog);
                        QJsonArray arrD = tst["dialog"].toArray();
                        for(auto j : arrD) {
                            dfn::DialogStruct d;
                            d.text = j.toObject()["text"].toString();
                            d.speaker = j.toObject()["speaker"].toString();
                            obj->addDialog(d);
                        }
                    }
                    if(tst.contains("inventory")) {
                        obj->setItem(tst["inventory"].toString());
                    }
                    if(tst.contains("newRoom")) {

                    }
                }
            }
            _objects.push_back(obj);

        }
    }
}

dfn::Point2D GameScene::convertToScreenSpace(const dfn::Point2D pos)
{
    dfn::Point2D screen;
    screen.x = (-pos.x*_sceneSizeX/2+_sceneCoordX+pos.y*_sceneSizeY*0.8)*_mult+_windowSquareX;
    screen.y = (-pos.x*_sceneSizeY/2+_sceneCoordY-pos.y*_sceneSizeY/2)*_mult+_windowSquareY;
    return screen;
}

void GameScene::showInteraction()
{
    //interactText->setZValue(200);
    //interactText->setOpacity(1);
    interactBox->setOpacity(1);
}

void GameScene::hideInteraction()
{
    //interactText->setZValue(-101);
    //interactText->setOpacity(0);
    interactBox->setOpacity(0);
}

void GameScene::endInteraction()
{
    dialogBox->setOpacity(0);
    speakerBox->setOpacity(0);
    interactIndex = 0;
    started = false;
    emit interactionBegin(false);
}

