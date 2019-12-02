#include "gamewindow.h"
#include "ui_gamewindow.h"

GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    setUpBoards();
}

GameWindow::~GameWindow()
{
    delete ui;
}

int GameWindow::itemClicked()
{
    return 0;
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
             boardLayouts[i]->setColumnStretch( j/3, j%3);
             boardFields.append(std::move(button));
         }
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

