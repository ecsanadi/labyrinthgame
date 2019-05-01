#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>

class QPushButton;
class QLabel;
class QPalette;
MainWindow::MainWindow()
{

    myMaze = new MazeWidget;

    QPalette pal = palette();

    // set black background
    pal.setColor(QPalette::Background, Qt::white);
    myMaze->setAutoFillBackground(true);
    myMaze->setPalette(pal);


    m_button_next = new QPushButton("New maze", this);
    connect(m_button_next, SIGNAL (clicked()), this, SLOT (buttonNext()));

    slider = new QSlider(Qt::Horizontal, this);
    slider->setRange(1,5);
    slider->setTickInterval(1);
    slider->setSingleStep(1);
    slider->setPageStep(1);
    slider->setValue(3);
    slider->setTickPosition(QSlider::TicksBelow);
    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(mazeChanged(int)));

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setColumnStretch(0, 1);
    mainLayout->setColumnStretch(3, 1);
    mainLayout->addWidget(myMaze, 0, 0, 1, 4);
    mainLayout->addWidget(m_button_next,4,1);
    mainLayout->addWidget(slider,4,2);

    setLayout(mainLayout);



    mazeChanged(0);

    setWindowTitle(tr("Labyrinth"));
}

MainWindow::~MainWindow()
{
   // delete ui;
}

void MainWindow::mazeChanged(int size)
{
    this->mysize=size;
    myMaze->setMaze(mysize);
}

void MainWindow::buttonNext()
{
    mazeChanged(this->mysize);
}



