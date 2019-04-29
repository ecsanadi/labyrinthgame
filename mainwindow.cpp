#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>

class QPushButton;
MainWindow::MainWindow(/*QWidget *parent*/) //:
   /* QMainWindow(parent),
    ui(new Ui::MainWindow)*/
{
    //ui->setupUi(this);
    myMaze = new MazeWidget;


    m_button_next = new QPushButton("Next maze", this);
   // m_button_next->setGeometry(QRect(QPoint(600, 750),
   //     QSize(70, 30)));

    connect(m_button_next, SIGNAL (clicked()), this, SLOT (buttonNext()));

    m_button_prev = new QPushButton("Prev maze", this);
  //  m_button_prev->setGeometry(QRect(QPoint(700, 750),
//        QSize(70, 30)));
    connect(m_button_prev, SIGNAL (clicked()), this, SLOT (buttonPrev()));

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setColumnStretch(0, 1);
    mainLayout->setColumnStretch(3, 1);
    mainLayout->addWidget(myMaze, 0, 0, 1, 4);
    mainLayout->addWidget(m_button_next,4,1);
    mainLayout->addWidget(m_button_prev,4,2);


    setLayout(mainLayout);

     mazeChanged(0);




    setWindowTitle(tr("Labyrinth"));


}

MainWindow::~MainWindow()
{
   // delete ui;
}

void MainWindow::mazeChanged(int step)
{
    myMaze->setMaze(/*step*/);
}

void MainWindow::buttonNext()
{
    mazeChanged(1);
}

void MainWindow::buttonPrev()
{
    mazeChanged(-1);
}
