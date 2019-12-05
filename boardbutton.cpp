#include "boardbutton.h"

BoardButton::BoardButton(qreal x, qreal y, qreal width, qreal height, int board, int field, QGraphicsItem * parent) : QGraphicsRectItem(x, y, width, height, parent)
{
    this->board=board;
    this->field=field;
    empty = new QRectF(x, y, width, height);
    this->x = new QRectF(x, y, width, height);
    this->y = new QRectF(x, y, width, height);
}

BoardButton::~BoardButton()
{
    delete empty;
    delete x;
    delete y;
}
