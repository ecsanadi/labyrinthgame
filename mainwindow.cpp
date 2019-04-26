#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    myMaze = new MazeWidget;
    mazeChanged();
    m_button_next = new QPushButton("Next maze", this);
    m_button_next->setGeometry(QRect(QPoint(100, 100),
        QSize(200, 50)));
    connect(m_button_next, SIGNAL (clicked()), this, SLOT (handleButtonNext()));
    m_button_prev = new QPushButton("Prev maze", this);
    m_button_prev->setGeometry(QRect(QPoint(300, 100),
        QSize(200, 50)));
    connect(m_button_prev, SIGNAL (clicked()), this, SLOT (handleButtonPrev()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mazeChanged()
{
    myMaze->setMaze(1);
}

void MainWindow::handleButtonNext()
 {
    myMaze->setMaze(1);
 }

void MainWindow::handleButtonPrev()
 {
    myMaze->setMaze(-1);
    // change the text
    //m_button->setText("Example");
    // resize button
    //m_button->resize(100,100);
 }
