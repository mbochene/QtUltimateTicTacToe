#ifndef FIELDGRAPHICSITEM_H
#define FIELDGRAPHICSITEM_H

#include <QGraphicsRectItem>
#include <QPainter>
#include <QObject>

class FieldGraphicsItem : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity)
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
