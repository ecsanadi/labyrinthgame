#include "mazewidget.h"
#include "points.h"
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

    endLineBeginY = ((meretY - 2) * meretPen) - (meretPen / 2);
    endLineEndY = ((meretY - 2) * meretPen) + (meretPen / 2);
    endLineBeginX = ((meretX - 1) * meretPen) + (meretPen / 2);

    qPix = QPixmap::grabWidget(this);
   // qPix = QWidget::grab(this);
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

    this->prevpoint = this->iniPoint;

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
    prevpoint = iniPoint;
}


void MazeWidget::checkWalls()
{
    if (prevpoint.x != 0 && prevpoint.y != 0)
    {
        bool xSideBigger = abs(point.x - prevpoint.x) >= abs(point.y - prevpoint.y);
        bool ySideBigger = abs(point.x - prevpoint.x) < abs(point.y - prevpoint.y);

        int stepCount = 0;
        int longSide = 0;
        int shortSide = 0;

        bool blackFound = false;

        if(xSideBigger)
        {
            longSide  = abs(prevpoint.x - point.x);
            shortSide = abs(prevpoint.y - point.y);
        }
        if(ySideBigger)
        {
            shortSide = abs(prevpoint.x - point.x);
            longSide  = abs(prevpoint.y - point.y);
        }

        Points tempPoint = this->prevpoint;

        if (prevpoint.x < point.x)
        {
                if (prevpoint.y < point.y)
                {
                    if( xSideBigger )
                    {
                        // X1********
                        // *        *
                        // ********X2
                        while ( ((tempPoint.x != point.x) && (tempPoint.y != point.y)) || !blackFound )
                        {
                            while (stepCount < longSide)
                            {
                                color = (image.pixel(tempPoint.x, tempPoint.y));
                                if (color == Qt::black)
                                {
                                    blackFound = true;
                                    serial->setPointX(tempPoint.x-((meretPen/4)/2));
                                    serial->setPointY(tempPoint.y-((meretPen/4)/2));
                                    break;
                                }
                                tempPoint.x++;
                                stepCount += shortSide;
                            }
                            tempPoint.y++;
                            stepCount = stepCount - longSide;
                        }

                    }
                    else if ( ySideBigger )
                    {
                        // X1***
                        // *   *
                        // *   *
                        // *   *
                        // ***X2
                        while ( ((tempPoint.x != point.x) && (tempPoint.y != point.y)) || !blackFound )
                        {
                            while (stepCount < longSide)
                            {
                                color = (image.pixel(tempPoint.x, tempPoint.y));
                                if (color == Qt::black)
                                {
                                    blackFound = true;
                                    serial->setPointX(tempPoint.x-((meretPen/4)/2));
                                    serial->setPointY(tempPoint.y-((meretPen/4)/2));
                                    break;
                                }
                                tempPoint.y++;
                                stepCount += shortSide;
                            }
                            tempPoint.x++;
                            stepCount = stepCount - longSide;
                        }
                    }
                }  // if (prevpoint.x < point.x)

                else if (prevpoint.y > point.y)
                {
                    if( xSideBigger )
                    {
                        // ********X2
                        // *        *
                        // X1********
                        while ( ((tempPoint.x != point.x) && (tempPoint.y != point.y)) || !blackFound )
                        {
                            while (stepCount < longSide)
                            {
                                color = (image.pixel(tempPoint.x, tempPoint.y));
                                if (color == Qt::black)
                                {
                                    blackFound = true;
                                    serial->setPointX(tempPoint.x-((meretPen/4)/2));
                                    serial->setPointY(tempPoint.y+((meretPen/4)/2));
                                    break;
                                }
                                tempPoint.x++;
                                stepCount += shortSide;
                            }
                            tempPoint.y--;
                            stepCount = stepCount - longSide;
                        }
                    }
                    else if ( ySideBigger )
                    {
                        // ***X2
                        // *   *
                        // *   *
                        // *   *
                        // X1***
                        while ( ((tempPoint.x != point.x) && (tempPoint.y != point.y)) || !blackFound )
                        {
                            while (stepCount < longSide)
                            {
                                color = (image.pixel(tempPoint.x, tempPoint.y));
                                if (color == Qt::black)
                                {
                                    blackFound = true;
                                    serial->setPointX(tempPoint.x-((meretPen/4)/2));
                                    serial->setPointY(tempPoint.y+((meretPen/4)/2));
                                    break;
                                }
                                tempPoint.y--;
                                stepCount += shortSide;
                            }
                            tempPoint.x++;
                            stepCount = stepCount - longSide;
                        }
                    }
                }
                else if (prevpoint.y == point.y)
                {
                    // X1*******X2
                    while ( (tempPoint.x != point.x) || !blackFound )
                    {
                            color = (image.pixel(tempPoint.x, tempPoint.y));
                            if (color == Qt::black)
                            {
                                blackFound = true;
                                serial->setPointX(tempPoint.x-((meretPen/4)/2));

                                break;
                            }
                            tempPoint.x++;
                    }
                }
                else
                {
                    std::cout<<"should not be here"<<std::endl;
                }
        }
        else if (prevpoint.x > point.x)
        {
                if (prevpoint.y < point.y)
                {
                    if( xSideBigger )
                    {
                        // ********X1
                        // *        *
                        // X2********
                        while ( ((tempPoint.x != point.x) && (tempPoint.y != point.y)) || !blackFound )
                        {
                            while (stepCount < longSide)
                            {
                                color = (image.pixel(tempPoint.x, tempPoint.y));
                                if (color == Qt::black)
                                {
                                    blackFound = true;
                                    //serial->setPointX(tempPoint.x+((meretPen/4)/2));
                                    //serial->setPointY(tempPoint.y-((meretPen/4)/2));
                                    break;
                                }
                                tempPoint.x--;
                                stepCount += shortSide;
                            }
                            tempPoint.y++;
                            stepCount = stepCount - longSide;
                        }
                    }
                    else if ( ySideBigger )
                    {
                        // ***X1
                        // *   *
                        // *   *
                        // *   *
                        // X2***
                        while ( ((tempPoint.x != point.x) && (tempPoint.y != point.y)) || !blackFound )
                        {
                            while (stepCount < longSide)
                            {
                                color = (image.pixel(tempPoint.x, tempPoint.y));
                                if (color == Qt::black)
                                {
                                    blackFound = true;
                                    //serial->setPointX(tempPoint.x+((meretPen/4)/2));
                                    //serial->setPointY(tempPoint.y-((meretPen/4)/2));
                                    break;
                                }
                                tempPoint.y++;
                                stepCount += shortSide;
                            }
                            tempPoint.x--;
                            stepCount = stepCount - longSide;
                        }
                    }
                }
                else if (prevpoint.y > point.y)
                {
                    if( xSideBigger )
                    {
                        // X2********
                        // *        *
                        // *********X1
                        while ( ((tempPoint.x != point.x) && (tempPoint.y != point.y)) || !blackFound )
                        {
                            while (stepCount < longSide)
                            {
                                color = (image.pixel(tempPoint.x, tempPoint.y));
                                if (color == Qt::black)
                                {
                                    blackFound = true;
                                    //serial->setPointX(tempPoint.x+((meretPen/4)/2));
                                    //serial->setPointY(tempPoint.y+((meretPen/4)/2));
                                    break;
                                }
                                tempPoint.x--;
                                stepCount += shortSide;
                            }
                            tempPoint.y--;
                            stepCount = stepCount - longSide;
                        }
                    }
                    else if ( ySideBigger )
                    {
                        // X2***
                        // *   *
                        // *   *
                        // *   *
                        // ***X1
                        while ( ((tempPoint.x != point.x) && (tempPoint.y != point.y)) || !blackFound )
                        {
                            while (stepCount < longSide)
                            {
                                color = (image.pixel(tempPoint.x, tempPoint.y));
                                if (color == Qt::black)
                                {
                                    blackFound = true;
                                    //serial->setPointX(tempPoint.x+((meretPen/4)/2));
                                    //serial->setPointY(tempPoint.y+((meretPen/4)/2));
                                    break;
                                }
                                tempPoint.y--;
                                stepCount += shortSide;
                            }
                            tempPoint.x--;
                            stepCount = stepCount - longSide;
                        }
                    }
                }
                else if (prevpoint.y == point.y)
                {
                    // X2*******X1
                    while ( (tempPoint.x != point.x) || !blackFound )
                    {
                            color = (image.pixel(tempPoint.x, tempPoint.y));
                            if (color == Qt::black)
                            {
                                blackFound = true;
                                serial->setPointX(tempPoint.x+((meretPen/4)/2));
                                break;
                            }
                            tempPoint.x--;
                    }
                }
                else
                {
                    std::cout<<"should not be here"<<std::endl;
                }
        }
        else if(prevpoint.x == point.x)
        {
            if (prevpoint.y < point.y)
            {
                // X1
                // *
                // *
                // *
                // X2
                while (  (tempPoint.y != point.y) || !blackFound )
                {
                        color = (image.pixel(tempPoint.x, tempPoint.y));
                        if (color == Qt::black)
                        {
                            blackFound = true;
                            serial->setPointY(tempPoint.y-((meretPen/4)/2));
                            break;
                        }
                        tempPoint.y++;
                }
            }
            else if (prevpoint.y > point.y)
            {
                // X2
                // *
                // *
                // *
                // X1
                while (  (tempPoint.y != point.y) || !blackFound )
                {
                        color = (image.pixel(tempPoint.x, tempPoint.y));
                        if (color == Qt::black)
                        {
                            blackFound = true;
                            serial->setPointY(tempPoint.y+((meretPen/4)/2));
                            break;
                        }
                        tempPoint.y--;
                }
            }

        }
        /*if (blackFound)
        {

            point.x=serial->getPointX();
            point.y=serial->getPointY();
            point.colorCounter=serial->getPointColorCount();
            blackFound = false;
        }*/
    }


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

    //Get current point
    point.x=serial->getPointX();
    point.y=serial->getPointY();
    point.colorCounter=serial->getPointColorCount();    

    // if moving
    //if(point.x != prevpoint.x && point.y != prevpoint.y)
   // {
        //keep drawing inside of the window
        checkWindowEdges();

        //Don!t walk trough walls
        checkWalls();

        // Save changes
        point.x=serial->getPointX();
        point.y=serial->getPointY();
        point.colorCounter=serial->getPointColorCount();

        pointList.push_back(point);

        prevpoint = point;
   // }

     /*color = (image.pixel(point.x, point.y));
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
     }*/

    //draw initial point
    int w = this->meretPen / 4;
    painter.setPen(QPen(static_cast<QColor>(serial->getMyColor()), w, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.drawPoint(this->iniPoint.x,this->iniPoint.y);

    //save into a vector and draw each point


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
