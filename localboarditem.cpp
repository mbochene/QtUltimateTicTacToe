#include "localboarditem.h"

LocalBoardItem::LocalBoardItem(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent) : QGraphicsItem(parent)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->color = Qt::white;
    this->symbol = QString("NONE");
}

QRectF LocalBoardItem::boundingRect() const
{
    return QRectF(0,0, x+width, y+height);
}

void LocalBoardItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if(symbol == QString("NONE"))
        paintBoard(painter);
    else if(symbol == QString("X"))
        paintX(painter);
    else
        paintO(painter);
}

void LocalBoardItem::setColor(const QColor color)
{
    this->color = color;
    update();
}

void LocalBoardItem::setSymbol(const QString symbol)
{
    if(symbol==QString("X") || symbol==QString("O") || symbol==QString("NONE"))
    {
        this->symbol = symbol;
        update();
    }
}

void LocalBoardItem::paintFrame(QPainter *painter)
{
    painter->setPen(QPen(Qt::black, 2));
    painter->fillRect(QRectF(x, y, width, height), color);

    const qreal width = this->boundingRect().width();
    const qreal height = this->boundingRect().height();

    painter->drawLine(QLineF(0, 0, width, 0));
    painter->drawLine(QLineF(0, height, width, height));
    painter->drawLine(QLineF(0, 0, 0, height));
    painter->drawLine(QLineF(width, 0, width, height));
}

void LocalBoardItem::paintBoard(QPainter *painter)
{
    paintFrame(painter);

    for(int i=1; i<3; ++i)
    {
        painter->drawLine(QLineF(i*width/3, 0, i*width/3, height));
        painter->drawLine(QLineF(0, i*height/3, width, i*height/3));
    }
}

void LocalBoardItem::paintX(QPainter *painter)
{
    paintFrame(painter);

    const int width = static_cast<int>(boundingRect().width()) - 2;
    const int height = static_cast<int>(boundingRect().height()) - 2;
    painter->setPen(QPen(Qt::black, 3));

    painter->drawLine(2, 2, width, height);
    painter->drawLine(2, height, width, 2);
}

void LocalBoardItem::paintO(QPainter *painter)
{
    paintFrame(painter);

    const int width = static_cast<int>(boundingRect().width()) - 2;
    const int height = static_cast<int>(boundingRect().height()) - 2;
    painter->setPen(QPen(Qt::black, 3));

    painter->setPen(QPen(Qt::black, 3));
    painter->drawEllipse(2, 2, width, height);
}

