#include "boardgraphicsview.h"

BoardGraphicsView::BoardGraphicsView(QWidget *parent) : QGraphicsView(parent) {}

void BoardGraphicsView::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);
    fitInView(scene()->sceneRect(), Qt::KeepAspectRatio);
}

void BoardGraphicsView::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);
    if (QGraphicsItem *item = itemAt(event->pos()))
        emit itemClicked(item);
}
