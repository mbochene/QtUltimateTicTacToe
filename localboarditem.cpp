#include "localboarditem.h"

LocalBoardItem::LocalBoardItem(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent) : QGraphicsItem(parent)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->color = Qt::white;
}

QRectF LocalBoardItem::boundingRect() const
{
    return QRectF(0,0, x+width, y+height);
}

void LocalBoardItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setPen(QPen(Qt::black, 2));
    painter->fillRect(QRectF(x, y, width, height), color);
    const qreal width = this->boundingRect().width();
    const qreal height = this->boundingRect().height();
    painter->drawLine(QLineF(0, 0, width, 0));
    painter->drawLine(QLineF(0, height, width, height));
    painter->drawLine(QLineF(0, 0, 0, height));
    painter->drawLine(QLineF(width, 0, width, height));

    for(int i=1; i<3; ++i)
    {
        painter->drawLine(QLineF(i*width/3, 0, i*width/3, height));
        painter->drawLine(QLineF(0, i*height/3, width, i*height/3));
    }
}

void LocalBoardItem::setColor(const QColor color)
{
    this->color = color;
    update();
}

