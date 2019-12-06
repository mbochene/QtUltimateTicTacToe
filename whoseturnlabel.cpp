#include "whoseturnlabel.h"

WhoseTurnLabel::WhoseTurnLabel(QString symbol, QWidget *parent) : QLabel(parent)
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

bool WhoseTurnLabel::setSymbol(QString symbol)
{
    if(symbol==QString("X") || symbol==QString("O"))
    {
        this->symbol = symbol;
        return true;
    }
    return false;
}

void WhoseTurnLabel::paintX()
{
    QPainter painter(this);
    painter.setPen(QPen(Qt::black, 4));
    painter.drawLine(0, 0, this->width(), this->height());
    painter.drawLine(0, this->height(), this->width(), 0);
}

void WhoseTurnLabel::paintO()
{
    QPainter painter(this);
    painter.setPen(QPen(Qt::black, 4));
    painter.drawEllipse(0, 0, this->width(), this->height());
}
