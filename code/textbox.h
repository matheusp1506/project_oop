#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <QGraphicsItem>

class TextBox
{
public:
    TextBox(QGraphicsTextItem *t, QGraphicsPixmapItem *b, int base, int desired);
    QGraphicsPixmapItem *getBox() {
        return box;
    }
    QGraphicsTextItem *getText() {
        return text;
    }
    void setOpacity(qreal opacity) {
        box->setOpacity(opacity);
        text->setOpacity(opacity);
    }
    void setPos(int x, int y) {
        QPointF temp = text->pos() - box->pos();
        box->setPos(x, y);
        text->setPos(QPointF(x, y)+temp);
    }
    void setZIndex(int val) {
        box->setZValue(val);
        text->setZValue(val+1);
    }


private:
    QGraphicsTextItem *text = nullptr;
    QGraphicsPixmapItem *box = nullptr;
};

#endif // TEXTBOX_H
