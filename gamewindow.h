#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QSequentialAnimationGroup>
#include <iostream>
#include <game.h>
#include <whoseturnlabel.h>
#include <localboarditem.h>
#include <fieldgraphicsitem.h>

QT_BEGIN_NAMESPACE
namespace Ui { class GameWindow; }
QT_END_NAMESPACE

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

signals:
    void reportMove(const int &board, const int &field);

public slots:
    void itemClicked(const QGraphicsItem *item);
    void markMove(const int &board, const int &field, const QString symbol);
    void updateWhoseTurnLabel(const QString symbol);
    void highlightBoards(const QVector<int> permittedBoards);
    void swapBoardToSymbol(const int & board, const QString symbol);
    void showEndRound();
    void prepareNewBoard();

private:
    Ui::GameWindow *ui;
    //WhoseTurnLabel *whoseTurnLabel;
    QGraphicsScene *scene;
    QVector<LocalBoardItem *> localBoards;
    QVector<QVector<FieldGraphicsItem *>> boardFields;
    Game *game;
    QSequentialAnimationGroup *sequentialAnimation;
    QParallelAnimationGroup *parallelAnimation;
    QPropertyAnimation *animation;

    void setUpBoards();
    void clearBoards();
};
#endif // GAMEWINDOW_H
