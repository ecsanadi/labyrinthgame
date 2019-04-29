#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    myMaze = new MazeWidget;
    mazeChanged(0);

    m_button_next = new QPushButton("Next maze", this);
    m_button_next->setGeometry(QRect(QPoint(100, 100),
        QSize(200, 50)));
    connect(m_button_next, SIGNAL (clicked()), this, SLOT (buttonNext()));

    m_button_prev = new QPushButton("Prev maze", this);
    m_button_prev->setGeometry(QRect(QPoint(300, 100),
        QSize(200, 50)));
    connect(m_button_prev, SIGNAL (clicked()), this, SLOT (buttonPrev()));

}

MainWindow::~MainWindow()
{
    delete ui;
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
