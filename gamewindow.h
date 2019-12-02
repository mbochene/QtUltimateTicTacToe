#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <QFrame>
#include <QLabel>
#include <iostream>

QT_BEGIN_NAMESPACE
namespace Ui { class GameWindow; }
QT_END_NAMESPACE

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

public slots:
    int itemClicked();

private:
    Ui::GameWindow *ui;
    QVector<QVector<QPushButton *>>itemButtons;
    QVector<QGridLayout *> boardLayouts;
    QVector<QFrame *> boardFrames;
    QVector<QLabel *> labels;

    void setUpBoards();
    QPushButton *createButton(const int &buttonNumber);
};
#endif // GAMEWINDOW_H
