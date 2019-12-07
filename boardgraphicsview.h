#ifndef BOARDGRAPHICSVIEW_H
#define BOARDGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QGraphicsItem>
#include <iostream>
#include <QMouseEvent>

class BoardGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit BoardGraphicsView(QWidget *parent = nullptr);

signals:
    void itemClicked(const QGraphicsItem *item);

public slots:

private:
    void resizeEvent(QResizeEvent * event);
    void mousePressEvent(QMouseEvent * event);
};

#endif // BOARDGRAPHICSVIEW_H
