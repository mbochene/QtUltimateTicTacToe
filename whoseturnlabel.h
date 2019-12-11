#ifndef WHOSETURNLABEL_H
#define WHOSETURNLABEL_H

#include <QLabel>
#include <QPainter>

class WhoseTurnLabel : public QLabel
{
    Q_OBJECT
public:
    explicit WhoseTurnLabel(QWidget *parent = nullptr, QString symbol = QString("X"));
    void paintEvent(QPaintEvent *) override;
    void setSymbol(QString symbol);

private:
    QString symbol;

    void paintX();
    void paintO();
};

#endif // WHOSETURNLABEL_H
