#include "mazewidget.h"
#include "mainwindow.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <QDebug>



QSize MazeWidget::minimumSizeHint() const
{
    return QSize(100, 100);
}

QSize MazeWidget::sizeHint() const
{

    return QSize(900, 700);
}

void MazeWidget::setShape(Shape shape)
{
    this->shape = shape;
    update();
}

void MazeWidget::setSerialReader(SerialReader* pserial)
{
    serial = pserial;
}

void MazeWidget::getEndPixels()
{
    //store the end points of the new labyrinth
    //int endLineBeginX;
    //int endLineBeginY;
    //int endLineEndY;
    endPointList.clear();
    //int loopStart = ((meretY - 2) * meretPen) - (meretPen / 2);
    //int loopEnd = ((meretY - 2) * meretPen) + (meretPen / 2);
    endLineBeginY = ((meretY - 2) * meretPen) - (meretPen / 2);
    endLineEndY = ((meretY - 2) * meretPen) + (meretPen / 2);
    //endpoints.x = ((meretX - 1) * meretPen) + (meretPen / 2);
    endLineBeginX = ((meretX - 1) * meretPen) + (meretPen / 2);
    //endpoints.colorCounter = serial->getPointColorCount();
    /*for (int y = loopStart; y < loopEnd;y++)
    {
        endpoints.y = y;
        endPointList.push_back(endpoints);

        std::cout<<"x: "<<endpoints.x<<", y: "<<endpoints.y<<std::endl;
    }*/
    qPix = QPixmap::grabWidget(this);
    image = (qPix.toImage());
}

void MazeWidget::setMaze(int size)
{
    srand(time(0));
    switch (size) {
    case 1:
        this->meretY=7;
        this->meretX=9;
        this->meretPen=100;
        this->iniPoint.x=10;
        this->iniPoint.y=110;

        break;
    case 2:
        this->meretY=15;
        this->meretX=19;
        this->meretPen=47;
        this->iniPoint.x=5;
        this->iniPoint.y=50;

        break;
    case 3:
        this->meretY=25;
        this->meretX=33;
        this->meretPen=27;
        this->iniPoint.x=2;
        this->iniPoint.y=30;
        //this->iniPoint.x=860;
        //this->iniPoint.y=625;

        break;
    case 4:
        this->meretY=59;
        this->meretX=75;
        this->meretPen=12;
        this->iniPoint.x=2;
        this->iniPoint.y=15;

        break;
    case 5:
        this->meretY=117;
        this->meretX=151;
        this->meretPen=6;
        this->iniPoint.x=1;
        this->iniPoint.y=7;

        break;
    default:
        this->meretY=25;
        this->meretX=33;
        this->meretPen=27;
        this->iniPoint.x=2;
        this->iniPoint.y=30;
        break;
    }

    ures(p);
    labirintus(p, 1, 1);

    /* bejarat es kijarat */
    p[1][0] = Jarat;
    p[this->meretY - 2][this->meretX - 1] = Jarat;

    getEndPixels();

    update();
}


void MazeWidget::ures(Palya p) {
    for (int y = 0; y < MERETY; ++y)
        for (int x = 0; x < MERETX; ++x)
            p[y][x] = Jarat;


    for (int y = 0; y < this->meretY; ++y)
        for (int x = 0; x < this->meretX; ++x)
            p[y][x] = Fal;
}

/* ez maga a generalo fuggveny */
void MazeWidget::labirintus(Palya p, int x, int y) {
    typedef enum { fel, le, jobbra, balra } Irany;
    Irany iranyok[4] = {fel, le, jobbra, balra};

    /* erre a pontra hivtak minket, ide lerakunk egy darabka jaratot. */
    p[y][x] = Jarat;

    /* a tomb keverese */
    for (int i = 3; i > 0; --i) {   /* mindegyiket... */
        int r = rand() % (i+1);     /* egy veletlenszeruen valasztottal... */
        Irany temp = iranyok[i];    /* megcsereljuk. */
        iranyok[i] = iranyok[r];
        iranyok[r] = temp;
    }

    /* a kevert iranyok szerint mindenfele probalunk menni, ha lehet. */
    for (int i = 0; i < 4; ++i)
        switch (iranyok[i]) {
        case fel:
            if (y >= 2 && p[y - 2][x] != Jarat) {
                p[y - 1][x] = Jarat;      /* elinditjuk arrafele a jaratot */
                labirintus(p, x, y - 2); /* es rekurzive megyunk tovabb */
            }
            break;
        case balra:
            if (x >= 2 && p[y][x - 2] != Jarat) {
                p[y][x - 1] = Jarat;
                labirintus(p, x - 2, y);
            }
            break;
        case le:
            if (y < ((this->meretY) - 2) && p[y + 2][x] != Jarat) {
                p[y + 1][x] = Jarat;
                labirintus(p, x, y + 2);
            }
            break;
        case jobbra:
            if (x < ((this->meretX) - 2) && p[y][x + 2] != Jarat) {
                p[y][x + 1] = Jarat;
                labirintus(p, x + 2, y);
            }
            break;
        }
}

void MazeWidget::checkWindowEdges()
{
    if (point.x < 0)
    {
        serial->setPointX(0);
    }
    if (point.x > width())
    {
        serial->setPointX(width());
    }

   if (point.y > height())
    {
        serial->setPointY(height());
    }
    if (point.y < 0)
    {
        serial->setPointY(0);
    }

    //restart color counter if the end is reached
    if (point.colorCounter>=17)
    {
        serial->setPointColorCount(0);
    }
}

void MazeWidget::restoreRotaryPosition()
{
    int lastColorCount = serial->getPointColorCount();
    pointList.clear();
    serial->setPointX(this->iniPoint.x);
    serial->setPointY(this->iniPoint.y);
    serial->setPointColorCount(lastColorCount);
    serial->setDoDelete(false);
}





void MazeWidget::paintEvent(QPaintEvent */*event*/)
{
    QPainter painter(this);
    painter.save();

    // draw the labyrinth
    for (int y = 0; y < this->meretY; ++y) {
        for (int x = 0; x < this->meretX; ++x){
            if (p[y][x] == Fal){
                painter.setPen(QPen(Qt::black, this->meretPen, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
                painter.drawPoint(x*this->meretPen,y*this->meretPen);
            }
            if (p[y][x] == Jarat){
                painter.setPen(QPen(Qt::white, this->meretPen, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
                painter.drawPoint(x*this->meretPen,y*this->meretPen);
            }
        }
    }




    // draw the rotary path
    if (serial->getDoDelete())
    {
        restoreRotaryPosition();
    }    

    prevpoint = point;

    point.x=serial->getPointX();
    point.y=serial->getPointY();
    point.colorCounter=serial->getPointColorCount();

    //keep drawing inside of the window
    checkWindowEdges();

     color = (image.pixel(point.x, point.y));
     if (color == Qt::black)
     {
         std::cout << " BLACK " << std::endl;
         point = prevpoint;
         serial->setPointX(prevpoint.x);
         serial->setPointY(prevpoint.y);
     }
     else
     {
         std::cout << " OK  WHITE " << std::endl;
     }

    //draw initial point
    int w = this->meretPen / 4;
    painter.setPen(QPen(static_cast<QColor>(serial->getMyColor()), w, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.drawPoint(this->iniPoint.x,this->iniPoint.y);

    //save into a vector and draw each point
    pointList.push_back(point);
    for(std::vector<Points>::iterator it = pointList.begin(); it != pointList.end(); ++it) {
        if (it != pointList.end())
        {
            std::vector<Points>::iterator it2 = it;
            it2++;
            if (it2!=pointList.end())
            {
              serial->setMyColor(it->colorCounter);
              painter.setPen(QPen(static_cast<QColor>(serial->getMyColor()), w, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
              painter.drawLine(it->x,it->y,it2->x,it2->y);
            }
        }else{
            break;
        }
    }


    painter.restore();

    painter.setRenderHint(QPainter::Antialiasing, false);
    painter.setPen(palette().dark().color());
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(QRect(0, 0, width() - 1, height() - 1));

    std::cout << "x: " << point.x << std::endl;
    if (endLineBeginX <= point.x)
    {
        if (point.y > endLineBeginY && point.y < endLineEndY)
        {
            restoreRotaryPosition();
            emit winGame();
        }
    }


}
