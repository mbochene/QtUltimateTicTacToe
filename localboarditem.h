#ifndef LOCALBOARDITEM_H
#define LOCALBOARDITEM_H

#include <QGraphicsItem>
#include <QPainter>

class LocalBoardItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity)
public:
    explicit LocalBoardItem(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent = nullptr);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void setColor(const QColor);
    void setSymbol(const QString symbol);

private:
    qreal x, y, width, height;
    QColor color;
    QString symbol;

    void paintFrame(QPainter *painter);
    void paintBoard(QPainter *painter);
    void paintX(QPainter *painter);
    void paintO(QPainter *painter);
};

#endif // LOCALBOARDITEM_H
