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

    endLineBeginY = ((sizeY - 2) * sizePen) - (sizePen / 2);
    endLineEndY = ((sizeY - 2) * sizePen) + (sizePen / 2);
    endLineBeginX = ((sizeX - 1) * sizePen) + (sizePen / 2);

    qPix = QPixmap::grabWidget(this);
    image = (qPix.toImage());
}

void MazeWidget::setMaze(int size)
{
    srand(time(0));
    switch (size) {
    case 1:
        this->sizeY=7;
        this->sizeX=9;
        this->sizePen=100;
        this->iniPoint.x=10;
        this->iniPoint.y=110;

        break;
    case 2:
        this->sizeY=15;
        this->sizeX=19;
        this->sizePen=47;
        this->iniPoint.x=5;
        this->iniPoint.y=50;

        break;
    case 3:
        this->sizeY=25;
        this->sizeX=33;
        this->sizePen=27;
        this->iniPoint.x=2;
        this->iniPoint.y=30;

        break;
    case 4:
        this->sizeY=59;
        this->sizeX=75;
        this->sizePen=12;
        this->iniPoint.x=2;
        this->iniPoint.y=15;

        break;
    case 5:
        this->sizeY=117;
        this->sizeX=151;
        this->sizePen=6;
        this->iniPoint.x=1;
        this->iniPoint.y=7;

        break;
    default:
        this->sizeY=25;
        this->sizeX=33;
        this->sizePen=27;
        this->iniPoint.x=2;
        this->iniPoint.y=30;
        break;
    }

    empty(p);
    labyrintGenerator(p, 1, 1);

    /* bejarat es kijarat */
    p[1][0] = Path;
    p[this->sizeY - 2][this->sizeX - 1] = Path;

    this->prevpoint = this->iniPoint;

    getEndPixels();    

    update();
}


void MazeWidget::empty(Field p) {
    for (int y = 0; y < sizeY; ++y)
        for (int x = 0; x < sizeX; ++x)
            p[y][x] = Path;


    for (int y = 0; y < this->sizeY; ++y)
        for (int x = 0; x < this->sizeX; ++x)
            p[y][x] = Wall;
}

/* ez maga a generalo fuggveny */
void MazeWidget::labyrintGenerator(Field p, int x, int y) {
    typedef enum { fel, le, jobbra, balra } Irany;
    Irany iranyok[4] = {fel, le, jobbra, balra};

    /* erre a pontra hivtak minket, ide lerakunk egy darabka jaratot. */
    p[y][x] = Path;

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
            if (y >= 2 && p[y - 2][x] != Path) {
                p[y - 1][x] = Path;      /* elinditjuk arrafele a jaratot */
                labyrintGenerator(p, x, y - 2); /* es rekurzive megyunk tovabb */
            }
            break;
        case balra:
            if (x >= 2 && p[y][x - 2] != Path) {
                p[y][x - 1] = Path;
                labyrintGenerator(p, x - 2, y);
            }
            break;
        case le:
            if (y < ((this->sizeY) - 2) && p[y + 2][x] != Path) {
                p[y + 1][x] = Path;
                labyrintGenerator(p, x, y + 2);
            }
            break;
        case jobbra:
            if (x < ((this->sizeX) - 2) && p[y][x + 2] != Path) {
                p[y][x + 1] = Path;
                labyrintGenerator(p, x + 2, y);
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

bool MazeWidget::checkBlackPix(int px, int py)
{
    color = (image.pixel(px, py));
    if (color == Qt::black)
    {
        // BLACK px found
        return true;
    }

    int yRangeEnd = 0 + ((sizePen / 10)+1);
    int XRangeEnd = 0 + ((sizePen / 10)+1);

    for (int yRangeStart = 0 - ((sizePen / 10)+1); yRangeStart<yRangeEnd; yRangeStart++)
    {
        for (int XRangeStart = 0 - ((sizePen / 10)+1); XRangeStart<XRangeEnd; XRangeStart++)
        {
            if (px+XRangeStart >= 0 && py+yRangeStart >= 0)
            {
                color = (image.pixel(px+XRangeStart, py+yRangeStart));
                if (color == Qt::black)
                {
                    // BLACK px found
                    return true;
                }
            }
            else
            {
                checkWindowEdges();
                return false;
            }
        }
    }
    return false;
}

void MazeWidget::checkWalls()
{
    std::cout<<"prevpoint.x: "<<prevpoint.x<<", prevpoint.y: "<<prevpoint.y<<", point.x: "<<point.x<<", point.y: "<<point.y<<std::endl;
    if ((prevpoint.x != 0 && prevpoint.y != 0) && (prevpoint.x != point.x || prevpoint.y != point.y))
    {
        std::cout<<"INSIDE"<<std::endl;
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
            std::cout << "X is bigger. LongS: " << longSide << ", ShortS: "<< shortSide << std::endl;
        }
        else if(ySideBigger)
        {
            shortSide = abs(prevpoint.x - point.x);
            longSide  = abs(prevpoint.y - point.y);
            std::cout << "Y is bigger. LongS: " << longSide << ", ShortS: "<< shortSide << std::endl;
        }

        Points tempPoint;
        Points endPoint;
        int stepBack;

        if (prevpoint.x < point.x)
        {
            tempPoint = this->prevpoint;
            endPoint  = this->point;
            stepBack = -1;
        }
        else if(prevpoint.x > point.x)
        {
            tempPoint = this->point;
            endPoint  = this->prevpoint;
            stepBack = 1;
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
                tempPoint = this->prevpoint;
                endPoint  = this->point;

            }
            else if (prevpoint.y > point.y)
            {
                // X2
                // *
                // *
                // *
                // X1
                tempPoint = this->point;
                endPoint  = this->prevpoint;
                std::cout << "12. case:" << std::endl;

            }
            std::cout << "11. case:" << std::endl;
            while (  (tempPoint.y <= endPoint.y) && !blackFound )
            {
                 std::cout<<"stepCount: "<<stepCount<<std::endl;
                std::cout<<"tempPoint.x: "<<tempPoint.x<<", tempPoint.y: "<<tempPoint.y<<std::endl;
                blackFound = checkBlackPix(tempPoint.x, tempPoint.y);
                if (blackFound)
                {

                    serial->setPointY(tempPoint.y - 1);
                    break;
                }
                tempPoint.y++;
            }

        }

        if (prevpoint.y < endPoint.y)
        {
            if( xSideBigger )
            {
                // X1********
                // *        *
                // ********X2
                std::cout << "1. case:" << std::endl;
                while ( ((tempPoint.x <= endPoint.x) || (tempPoint.y <= endPoint.y)) && !blackFound )
                {

                    while (stepCount < longSide )
                    {
                        std::cout<<"stepCount: "<<stepCount<<std::endl;
                        std::cout<<"tempPoint.x: "<<tempPoint.x<<", tempPoint.y: "<<tempPoint.y<<std::endl;
                        if (checkBlackPix(tempPoint.x, tempPoint.y))
                        {
                            blackFound = true;
                            serial->setPointX(tempPoint.x + stepBack);
                            serial->setPointY(tempPoint.y + stepBack);
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
                std::cout << "2. case:" << std::endl;
                while ( ((tempPoint.x <= endPoint.x) || (tempPoint.y <= endPoint.y)) && !blackFound )
                {
                    while (stepCount < longSide )
                    {
                        std::cout<<"stepCount: "<<stepCount<<std::endl;
                        std::cout<<"tempPoint.x: "<<tempPoint.x<<", tempPoint.y: "<<tempPoint.y<<std::endl;
                        if (checkBlackPix(tempPoint.x, tempPoint.y))
                        {
                            blackFound = true;
                            serial->setPointX(tempPoint.x + stepBack);
                            serial->setPointY(tempPoint.y + stepBack);
                            break;
                        }
                        tempPoint.y++;
                        stepCount += shortSide;
                    }
                    tempPoint.x++;
                    stepCount = stepCount - longSide;
                }
            }
        }  //  if (prevpoint.y < point.y)

        else if (prevpoint.y > endPoint.y)
        {
            if( xSideBigger )
            {
                // ********X2
                // *        *
                // X1********
                std::cout << "3. case:" << std::endl;
                while ( ((tempPoint.x <= endPoint.x) || (tempPoint.y >= endPoint.y)) && !blackFound )
                {
                    while (stepCount < longSide)
                    {
                        std::cout<<"stepCount: "<<stepCount<<std::endl;
                        std::cout<<"tempPoint.x: "<<tempPoint.x<<", tempPoint.y: "<<tempPoint.y<<std::endl;
                        if (checkBlackPix(tempPoint.x, tempPoint.y))
                        {
                            blackFound = true;
                            serial->setPointX(tempPoint.x + stepBack);
                            serial->setPointY(tempPoint.y - stepBack);
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
                std::cout << "4. case:" << std::endl;
                while ( ((tempPoint.x <= endPoint.x) || (tempPoint.y >= endPoint.y)) && !blackFound )
                {
                    while (stepCount < longSide )
                    {
                        std::cout<<"stepCount: "<<stepCount<<std::endl;
                        std::cout<<"tempPoint.x: "<<tempPoint.x<<", tempPoint.y: "<<tempPoint.y<<std::endl;
                        if (checkBlackPix(tempPoint.x, tempPoint.y))
                        {
                            blackFound = true;
                            serial->setPointX(tempPoint.x + stepBack);
                            serial->setPointY(tempPoint.y - stepBack);
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
        else if (prevpoint.y == endPoint.y)
        {
            // X1*******X2
            std::cout << "5. case:" << std::endl;
            while ( (tempPoint.x <= endPoint.x) && !blackFound )
            {
                //std::cout<<"stepCount: "<<stepCount<<std::endl;
                std::cout<<"tempPoint.x: "<<tempPoint.x<<", tempPoint.y: "<<tempPoint.y<<", point.x: "<<endPoint.x<<", point.y: "<<endPoint.y<<std::endl;
                blackFound = checkBlackPix(tempPoint.x, tempPoint.y);
                if (blackFound)
                {
                    serial->setPointX(tempPoint.x + stepBack);
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


}


void MazeWidget::paintEvent(QPaintEvent */*event*/)
{
    QPainter painter(this);
    painter.save();

    // draw the labyrinth
    for (int y = 0; y < this->sizeY; ++y) {
        for (int x = 0; x < this->sizeX; ++x){
            if (p[y][x] == Wall){
                painter.setPen(QPen(Qt::black, this->sizePen, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
                painter.drawPoint(x*this->sizePen,y*this->sizePen);
            }
            if (p[y][x] == Path){
                painter.setPen(QPen(Qt::white, this->sizePen, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
                painter.drawPoint(x*this->sizePen,y*this->sizePen);
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
    int w = this->sizePen / 4;
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
