#ifndef FIELDGRAPHICSITEM_H
#define FIELDGRAPHICSITEM_H

#include <QGraphicsItem>
#include <QPainter>

class FieldGraphicsItem : public QGraphicsRectItem
{
public:
    explicit FieldGraphicsItem(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void setSymbol(const QString symbol);

private:
    QString symbol;
    void paintX(QPainter *painter);
    void paintO(QPainter *painter);
};

#endif // FIELDGRAPHICSITEM_H
