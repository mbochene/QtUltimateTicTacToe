#include "gamewindow.h"
#include "ui_gamewindow.h"

GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GameWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    scene->setBackgroundBrush(QBrush(Qt::gray));
    ui->boardView->setScene(scene);
    setUpBoards();
    std::cout << scene->sceneRect().x() << " " << scene->sceneRect().y() << " " << scene->sceneRect().width() << std::endl;

    whoseTurnLabel = new WhoseTurnLabel();
    whoseTurnLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    whoseTurnLabel->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    ui->verticalLayout->addWidget(whoseTurnLabel, 2);

    ui->boardView->show();

    game = new Game();

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

void GameWindow::itemClicked()
{
    QPushButton *clickedItem = qobject_cast<QPushButton*>(sender());
    clickedItem->setAutoExclusive(false);
    clickedItem->setChecked(false);
    clickedItem->setAutoExclusive(true);
    const int board = clickedItem->parentWidget()->objectName().back().digitValue();
    const int field = clickedItem->objectName().toInt();
    emit reportMove(board, field);
}

void GameWindow::markMove(const int &board, const int &field, const QString symbol)
{
    QFrame *boardGrid = ui->centralwidget->findChild<QFrame *>(QString("frame_") + QString::number(board));
    QPushButton *button = boardGrid->findChild<QPushButton *>(QString::number(field));
    button->setIcon(QIcon(":/" + symbol));
    button->setEnabled(false);
}

void GameWindow::updateWhoseTurnLabel(const QString symbol)
{
    QPixmap *pixmap = new QPixmap(":/" + symbol);
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
            boardFrames[i]->setStyleSheet("background-color:rgb(235, 123, 123)");
            ++j;
        }
        else
        {
            boardFrames[i]->setStyleSheet("background-color:white");
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
    QPen pen(Qt::black, 1);
    QBrush brush(Qt::white);
    for(int i=0; i<9; i++)
    {
        const QPointF point = ui->boardView->mapToScene(2 + (150 * (i/3)), 2 + (150 * (i%3)));
        boardRects.append(std::move(scene->addRect(point.x(), point.y(), 145, 145, pen, brush)));
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
    connect(button, &QPushButton::clicked, this, &GameWindow::itemClicked);
    return button;
}

void GameWindow::resizeEvent(QResizeEvent *event)
{
    if(event->oldSize().width() != -1)
    {
        ui->boardView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
    }
}
