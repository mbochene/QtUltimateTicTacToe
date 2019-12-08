#include "fieldgraphicsitem.h"

FieldGraphicsItem::FieldGraphicsItem(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent) : QObject(), QGraphicsRectItem(x, y, width, height, parent)
{
    symbol = QString("NONE");
}

void FieldGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QGraphicsRectItem::paint(painter, option, widget);

    if(symbol == QString("X"))
     {
        paintX(painter);
     }
     else if(symbol == QString("O"))
     {
        paintO(painter);
     }
}

void FieldGraphicsItem::setSymbol(const QString symbol)
{
    if(symbol==QString("X") || symbol==QString("O") || symbol==QString("NONE"))
    {
        this->symbol = symbol;
        update();
    }
}

void FieldGraphicsItem::paintX(QPainter *painter)
{
    const int width = static_cast<int>(rect().width()) - 2;
    const int height = static_cast<int>(rect().height()) - 2;
    painter->setPen(QPen(Qt::black, 3));

    painter->drawLine(2, 2, width, height);
    painter->drawLine(2, height, width, 2);
}

void FieldGraphicsItem::paintO(QPainter *painter)
{
    const int width = static_cast<int>(rect().width()) - 2;
    const int height = static_cast<int>(rect().height()) - 2;
    painter->setPen(QPen(Qt::black, 3));

    painter->setPen(QPen(Qt::black, 3));
    painter->drawEllipse(2, 2, width, height);
}

