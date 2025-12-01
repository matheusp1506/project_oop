#include "textbox.h"

TextBox::TextBox(QGraphicsTextItem *t, QGraphicsPixmapItem *b, int base, int desired) {
    text = t;
    box = b;
    b->setScale((float)desired/base);
    t->setTextWidth(desired-12*(float)desired/base);
    t->setPos(b->pos()+QPointF(6*(float)desired/base,3*(float)desired/base));
}
