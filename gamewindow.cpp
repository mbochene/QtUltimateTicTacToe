#include "gamewindow.h"
#include "ui_gamewindow.h"

GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GameWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    scene->setBackgroundBrush(QBrush(Qt::gray));

    setUpBoards();
    ui->boardView->setScene(scene);
    ui->boardView->show();
    ui->boardView->installEventFilter(this);

    whoseTurnLabel = new WhoseTurnLabel(QString("X"));
    whoseTurnLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    whoseTurnLabel->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    ui->verticalLayout->addWidget(whoseTurnLabel, 0);

    game = new Game();

    connect(ui->boardView, &BoardGraphicsView::itemClicked, this, &GameWindow::itemClicked);
    connect(ui->resetButton, &QPushButton::clicked, this, &GameWindow::prepareNewBoard);
    connect(this, &GameWindow::reportMove, game, &Game::processMove);
    connect(game, &Game::markMove, this, &GameWindow::markMove);
    connect(game, &Game::highlightPermittedBoards, this, &GameWindow::highlightBoards);
    connect(game, &Game::markLocalWin, this, &GameWindow::swapBoardToSymbol);
    connect(game, &Game::updateWhoseTurn, this, &GameWindow::updateWhoseTurnLabel);
    connect(game, &Game::globalWin, this, &GameWindow::showEndRound);
}

GameWindow::~GameWindow()
{
    delete ui;
    delete game;
}

void GameWindow::itemClicked(const QGraphicsItem *item)
{
    const QGraphicsItem *localBoard = item->parentItem();

    if(localBoard)
    {
        for(int i=0; i<9; i++)
        {
            if(localBoards[i] == localBoard)
            {
                for(int j=0; j<9; j++)
                {
                    if(boardFields[i][j] == item)
                    {
                        emit reportMove(i, j);
                        break;
                    }
                }
                break;
            }
        }
    }
}

void GameWindow::markMove(const int &board, const int &field, const QString symbol)
{
    boardFields[board][field]->setOpacity(0);
    boardFields[board][field]->setSymbol(symbol);

    animation = new QPropertyAnimation(boardFields[board][field], "opacity");
    {
        animation->setDuration(600);
        animation->setStartValue(0);
        animation->setEndValue(1);
        animation->setEasingCurve(QEasingCurve::InQuad);
    }

    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void GameWindow::updateWhoseTurnLabel(const QString symbol)
{
    whoseTurnLabel->setSymbol(symbol);
}

void GameWindow::highlightBoards(const QVector<int> permittedBoards)
{
    int j=0;
    const int permittedBoardsSize = permittedBoards.size();

    for(int i=0; i<9; i++)
    {
        if(j < permittedBoardsSize && i == permittedBoards[j])
        {
            localBoards[i]->setColor(Qt::red);
            ++j;
        }
        else
        {
            localBoards[i]->setColor(Qt::white);
        }
    }
}

void GameWindow::swapBoardToSymbol(const int &board, const QString symbol)
{
    sequentialAnimation = new QSequentialAnimationGroup();
    parallelAnimation = new QParallelAnimationGroup();
    QPropertyAnimation *animation;

    for(FieldGraphicsItem *x : boardFields[board])
    {
        animation = new QPropertyAnimation(x, "opacity");
        {
            animation->setDuration(600);
            animation->setStartValue(1);
            animation->setEndValue(0);
        }

        connect(animation, &QPropertyAnimation::finished, [x](){
            x->setVisible(false);
            x->setOpacity(1);
        });

        parallelAnimation->addAnimation(animation);
    }

    animation = new QPropertyAnimation(localBoards[board], "opacity");
    {
        animation->setDuration(600);
        animation->setStartValue(1);
        animation->setEndValue(0);
    }

    parallelAnimation->addAnimation(animation);
    connect(parallelAnimation, &QPropertyAnimation::finished, [=](){localBoards[board]->setSymbol(symbol); });

    sequentialAnimation->addAnimation(parallelAnimation);

    animation = new QPropertyAnimation(localBoards[board], "opacity");
    {
        animation->setDuration(600);
        animation->setStartValue(0);
        animation->setEndValue(1);
    }

    sequentialAnimation->addAnimation(animation);
    sequentialAnimation->start(QAbstractAnimation::DeleteWhenStopped);
}

void GameWindow::showEndRound()
{
    for(int i=0; i<9; i++)
    {
       localBoards[i]->setColor(Qt::white);
    }
}

void GameWindow::prepareNewBoard()
{
    clearBoards();
    game->prepareNewGame();
    updateWhoseTurnLabel(QString("X"));
}

void GameWindow::setUpBoards()
{
    for(int i=0; i<9; i++)
    {
        const QPointF point = ui->boardView->mapToScene(150 * (i%3), 150 * (i/3) );
        LocalBoardItem *localBoard = new LocalBoardItem(0, 0, 144, 144);
        localBoards.append(std::move(localBoard));
        localBoards[i]->setPos(point);
        scene->addItem(localBoards[i]);

        QVector<FieldGraphicsItem *> fields;
        for(int j=0; j<9; j++)
        {
            const QPointF point2 = ui->boardView->mapToScene(48 * (j%3), 48 * (j/3));
            FieldGraphicsItem *field = new FieldGraphicsItem(0, 0, 48, 48);
            fields.append(std::move(field));
            fields[j]->setPos(point2);
            fields[j]->setParentItem(localBoards[i]);
        }
        boardFields.append(std::move(fields));
    }
}

void GameWindow::clearBoards()
{
    for(int i=0; i<9; i++)
    {
        localBoards[i]->setSymbol("NONE");
        localBoards[i]->setColor(Qt::white);

        for(int j=0; j<9; j++)
        {
            boardFields[i][j]->setSymbol("NONE");
            boardFields[i][j]->setVisible(true);
        }
    }
}
