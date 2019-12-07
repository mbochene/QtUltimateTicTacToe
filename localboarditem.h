#ifndef LOCALBOARDITEM_H
#define LOCALBOARDITEM_H

#include <QGraphicsItem>
#include <QPainter>

class LocalBoardItem : public QGraphicsItem
{
public:
    explicit LocalBoardItem(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent = nullptr);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void setColor(const QColor);

private:
    qreal x, y, width, height;
    QColor color;
};

#endif // LOCALBOARDITEM_H
