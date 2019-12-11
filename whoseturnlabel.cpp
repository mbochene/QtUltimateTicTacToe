#include "whoseturnlabel.h"

WhoseTurnLabel::WhoseTurnLabel(QWidget *parent, QString symbol) : QLabel(parent)
{
    this->symbol = symbol;
}

void WhoseTurnLabel::paintEvent(QPaintEvent *)
{
    if(symbol == QString("X"))
        paintX();
    else
        paintO();
}

void WhoseTurnLabel::setSymbol(QString symbol)
{
    if(symbol==QString("X") || symbol==QString("O"))
    {
        this->symbol = symbol;
        update();
    }
}

void WhoseTurnLabel::paintX()
{
    QPainter painter(this);
    painter.setPen(QPen(Qt::black, 4));
    painter.drawLine(2, 2, this->width()-2, this->height()-2);
    painter.drawLine(2, this->height()-2, this->width()-2, 2);
}

void WhoseTurnLabel::paintO()
{
    QPainter painter(this);
    painter.setPen(QPen(Qt::black, 6));
    painter.drawEllipse(6, 6, (this->width())-12, (this->height())-12);
}
