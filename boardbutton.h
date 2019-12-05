#ifndef BOARDBUTTON_H
#define BOARDBUTTON_H

#include <QWidget>
#include <QGraphicsRectItem>

class BoardButton : public QGraphicsRectItem
{
public:
    explicit BoardButton(qreal x, qreal y, qreal width, qreal height, int board, int field, QGraphicsItem * parent = nullptr);
    ~BoardButton();

private:
    int board, field;
    QRectF *empty, *x, *y;
};

#endif // BOARDBUTTON_H
