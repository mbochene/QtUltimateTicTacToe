#include "gamewindow.h"
#include "ui_gamewindow.h"

GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GameWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    scene->setBackgroundBrush(QBrush(Qt::gray));
    //ui->boardView->setScene(scene);

    setUpBoards();
    ui->boardView->setScene(scene);
    ui->boardView->show();
    ui->boardView->installEventFilter(this);

    whoseTurnLabel = new WhoseTurnLabel();
    whoseTurnLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    whoseTurnLabel->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    ui->verticalLayout->addWidget(whoseTurnLabel, 0);

    game = new Game();

    connect(ui->boardView, &BoardGraphicsView::itemClicked, this, &GameWindow::itemClicked);
    connect(ui->resetButton, &QPushButton::clicked, this, &GameWindow::prepareNewBoard);
    connect(this, &GameWindow::reportMove, game, &Game::processMove);
    connect(game, &Game::markMove, this, &GameWindow::markMove);
    connect(game, &Game::highlightPermittedBoards, this, &GameWindow::highlightBoards);
    connect(game, &Game::markLocalWin, this, &GameWindow::swapBoardToImage);
    connect(game, &Game::updateWhoseTurn, this, &GameWindow::updateWhoseTurnLabel);
    connect(game, &Game::globalWin, this, &GameWindow::showEndRound);

    updateWhoseTurnLabel(QString("X"));
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
    boardFields[board][field]->setSymbol(symbol);
   //const qreal width = boardFields[board][field]->rect().width();
   //const qreal height = boardFields[board][field]->rect().height();
   //QPixmap pixmap = QPixmap(":/" + symbol).scaled(width, height, Qt::KeepAspectRatio);
   //QPainter pixmapPainter(&pixmap);
   //boardFields[board][field]->paint(&pixmapPainter, nullptr);
}

void GameWindow::updateWhoseTurnLabel(const QString symbol)
{
    std::cout << whoseTurnLabel->width() << " " << whoseTurnLabel->height() << std::endl;
    whoseTurnLabel->setSymbol(symbol);
    update();
    //ui->whoseTurnLabel->setPixmap(pixmap->scaled(ui->whoseTurnLabel->width(), ui->whoseTurnLabel->height(), Qt::KeepAspectRatio));
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

void GameWindow::swapBoardToImage(const int &board, const QString symbol)
{
    for(QPushButton *x : itemButtons[board])
        x->deleteLater();

    itemButtons[board].clear();

    QLabel *label = new QLabel();
    QPixmap *pixmap = new QPixmap(":/" + symbol);
    label->setPixmap(pixmap->scaled(boardFrames[board]->height(),  boardFrames[board]->width(), Qt::KeepAspectRatio));
    //label->setPixmap(QPixmap(":/" + symbol));
    label->setObjectName(QString("label_") + QString::number(board));
    boardLayouts[board]->addWidget(label);
}

void GameWindow::showEndRound()
{
    for(int i=0; i<9; i++)
    {
        boardFrames[i]->setStyleSheet("background-color:white");
    }
}

void GameWindow::prepareNewBoard()
{
    clearBoards();
    game->prepareNewGame();

    for(int i=0; i<9; i++)
    {
        boardFrames[i]->setStyleSheet("background-color:white");

        QVector<QPushButton *> boardFields;
        for(int j=0; j<9; j++)
        {
            QPushButton *button = createButton(j);
            boardLayouts[i]->addWidget(button, j/3, j%3);
            boardFields.append(std::move(button));
        }
        itemButtons.append(std::move(boardFields));
    }

    updateWhoseTurnLabel(QString("X"));
}


/*
void GameWindow::setUpBoards()
{
     for(int i=0; i<9; i++)
     {
         boardFrames.append(ui->centralwidget->findChild<QFrame *>(QString("frame_") + QString::number(i)));
         boardFrames[i]->setStyleSheet("background-color:white");
         QGridLayout *layout = new QGridLayout(boardFrames[i]);
         layout->setObjectName(QString("board_") + QString::number(i));
         boardLayouts.append(std::move(layout));
         boardFrames[i]->setFrameStyle(QFrame::Panel | QFrame::Plain);

         QVector<QPushButton *> boardFields;
         for(int j=0; j<9; j++)
         {
             QPushButton *button = createButton(j);
             boardLayouts[i]->addWidget(button, j/3, j%3);
             boardFields.append(std::move(button));
         }

         itemButtons.append(std::move(boardFields));
     }
}
*/

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
            //fields[j]->setBrush(Qt::red);
        }
        boardFields.append(std::move(fields));
    }
}

void GameWindow::clearBoards()
{
    for(int i=0; i<9; i++)
    {
        QLabel *label = boardFrames[i]->findChild<QLabel*>(QString("label_") + QString::number(i));

        if(label!=nullptr)
            label->deleteLater();

        for(QPushButton *button : itemButtons[i])
            button->deleteLater();
    }

    itemButtons.clear();
}

QPushButton *GameWindow::createButton(const int &buttonNumber)
{
    QPushButton *button = new QPushButton;
    button->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    button->setText("");
    button->setCheckable(true);
    button->setAutoExclusive(true);
    button->setObjectName(QString::number(buttonNumber));
    button->setIconSize(button->sizeHint());
    //connect(button, &QPushButton::clicked, this, &GameWindow::itemClicked);
    return button;
}


bool GameWindow::eventFilter(QObject *object, QEvent *event)
{
    if(object == ui->boardView && event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent* me = static_cast<QMouseEvent*>(event);
        if (QGraphicsItem *item = ui->boardView->itemAt(me->pos())) {
                std::cout << "itemmmmmmm " << item << std::endl;
            } else {
                std::cout << "You didn't click on an item." << item<< std::endl;
            }
    }
    return false;
}
