#ifndef WHOSETURNLABEL_H
#define WHOSETURNLABEL_H

#include <QLabel>
#include <QPainter>

class WhoseTurnLabel : public QLabel
{
    Q_OBJECT
public:
    explicit WhoseTurnLabel(QString symbol = QString("X"), QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);

signals:

public slots:
    bool setSymbol(QString symbol);

private:
    QString symbol;

    void paintX();
    void paintO();
};

#endif // WHOSETURNLABEL_H
