#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>

class QPushButton;
class QLabel;
MainWindow::MainWindow(/*QWidget *parent*/) //:
   /* QMainWindow(parent),
    ui(new Ui::MainWindow)*/
{
    //ui->setupUi(this);
    myMaze = new MazeWidget;


    m_button_next = new QPushButton("New maze", this);
   // m_button_next->setGeometry(QRect(QPoint(600, 750),
   //     QSize(70, 30)));

    connect(m_button_next, SIGNAL (clicked()), this, SLOT (buttonNext()));

    slider = new QSlider(Qt::Horizontal, this);
    //slider->setMinimum(1);
    //slider->setMaximum(5);
    //slider->setValue(3);
    //slider->setSingleStep(1);
    slider->setRange(1,5);
    slider->setTickInterval(1);
        slider->setSingleStep(1);
        slider->setPageStep(1);
            slider->setValue(3);
            slider->setTickPosition(QSlider::TicksBelow);
    //slider->setTickInterval(1);

    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(mazeChanged(int)));
  //  connect( slider, SIGNAL((slider->valueChanged())), this, SLOT(setValue(double)) );
    //sizeLabel = new QLabel()

   /* m_button_prev = new QPushButton("Prev maze", this);
  //  m_button_prev->setGeometry(QRect(QPoint(700, 750),
//        QSize(70, 30)));
    connect(m_button_prev, SIGNAL (clicked()), this, SLOT (buttonPrev()));*/

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

void MainWindow::setSize(int size)
{
    switch (size) {
    case 1:

        break;
    case 2:

        break;
    case 3:

        break;
    case 4:

        break;
    case 5:

        break;
    default:
        break;
    }

}

void MainWindow::buttonPrev()
{
    mazeChanged(-1);
}
