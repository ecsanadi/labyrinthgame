#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mazewidget.h"
#include <QtWidgets>

class QPushButton;
class QLabel;
class QPalette;
MainWindow::MainWindow(SerialReader* pserial)
{

    myMaze = new MazeWidget;

    serial = pserial;
    myMaze->setSerialReader(serial);

    connect(serial, SIGNAL(serialIsReady()),
            this, SLOT(shapeChanged()));

    connect(myMaze, SIGNAL(winGame()),
            this, SLOT(winnerMsg()));

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

    sizeLabel = new QLabel("Size: ", this);

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setColumnStretch(0, 1);
    mainLayout->setColumnStretch(3, 1);
    mainLayout->addWidget(myMaze, 0, 0, 1, 4);
    mainLayout->addWidget(m_button_next,4,0);
    mainLayout->addWidget(sizeLabel,4,1);
    mainLayout->addWidget(slider,4,2);

    setLayout(mainLayout);

    mazeChanged(0);

    shapeChanged();

    setWindowTitle(tr("Labyrinth"));
}

MainWindow::~MainWindow()
{
   // delete ui;
}

void MainWindow::mazeChanged(int size)
{
    this->mysize=size;
    serial->setDoDelete(true);
    myMaze->setMaze(mysize);    
}

void MainWindow::buttonNext()
{
    mazeChanged(this->mysize);
}

void MainWindow::setSerialReader(SerialReader* pserial)
{
    serial = pserial;
    myMaze->setSerialReader(serial);
}

void MainWindow::shapeChanged()
{
    myMaze->setShape(MazeWidget::Line);
}

void MainWindow::winnerMsg()
{
    const QFont fixedFont = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    QMessageBox messageBox;
    messageBox.setFont(fixedFont);
    messageBox.setStyleSheet("QTextEdit { font-family: monospace; }");
    messageBox.setWindowTitle("Escaped");
    messageBox.setTextFormat(Qt::PlainText);
    messageBox.setText("                Congratulation! You won!\n\n"


"                                     .''.                \n"
"         .''.      .        *''*    :_\\/_:     .         \n"
"        :_\\/_:   _\\(/_  .:.*_\\/_*   : /\\ :  .'.:.'.      \n"
"    .''.: /\\ :   ./)\\   ':'* /\\ * :  '..'.  -=:o:=-      \n"
"   :_\\/_:'.:::.    ' *''*    * '.\\'/.' _\\(/_'.':'.'      \n"
"   : /\\ : :::::     *_\\/_*     -= o =-  /)\\    '  *      \n"
"    '..'  ':::'     * /\\ *     .'/.\\'.   '               \n"
"        *            *..*         :                      \n");
    messageBox.exec();
    myMaze->setShape(MazeWidget::Line);
}


