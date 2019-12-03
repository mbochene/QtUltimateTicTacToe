#include "gamewindow.h"
#include "ui_gamewindow.h"

GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    setUpBoards();
    game = new Game();
    connect(this, &GameWindow::reportMove, game, &Game::processMove);
    connect(game, &Game::markMove, this, &GameWindow::markMove);
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
    std::cout << board << " " << field << " " << symbol.toLocal8Bit().constData() << std::endl;
    QWidget *boardGrid = ui->centralwidget->findChild<QWidget *>(QString("gridLayoutWidget_") + QString::number(board));
    std::cout << boardGrid->objectName().toLocal8Bit().constData() << std::endl;
    QPushButton *button = boardGrid->findChild<QPushButton *>(QString::number(field));
    button->setText(symbol);
    button->setEnabled(false);
}

void GameWindow::setUpBoards()
{
     for(int i=0; i<9; i++)
     {
         boardFrames.append(ui->centralwidget->findChild<QFrame *>(QString("frame_") + QString::number(i)));
         boardLayouts.append(ui->centralwidget->findChild<QGridLayout *>(QString("board_") + QString::number(i)));
         boardFrames[i]->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
         boardFrames[i]->setFrameStyle(QFrame::Panel | QFrame::Plain);

         QVector<QPushButton *> boardFields;
         for(int j=0; j<9; j++)
         {
             QPushButton *button = createButton(j);
             boardLayouts[i]->addWidget(button, j/3, j%3);
             boardFields.append(std::move(button));
         }
         boardFields[0]->parentWidget()->setObjectName(QString("gridLayoutWidget_") + QString::number(i));
         itemButtons.append(std::move(boardFields));
     }
}

QPushButton *GameWindow::createButton(const int &buttonNumber)
{
    QPushButton *button = new QPushButton;
    button->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    button->setText("");
    button->setCheckable(true);
    button->setAutoExclusive(true);
    button->setObjectName(QString::number(buttonNumber));
    connect(button, SIGNAL(clicked()),this,SLOT(itemClicked()));
    return button;
}

