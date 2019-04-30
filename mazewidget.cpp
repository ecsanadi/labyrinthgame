#include "mazewidget.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


QSize MazeWidget::minimumSizeHint() const
{
    return QSize(100, 100);
}

QSize MazeWidget::sizeHint() const
{

    return QSize(900, 700);
}


void MazeWidget::setMaze(int size)
{
    srand(time(0));
    switch (size) {
    case 1:
        this->meretY=7;
        this->meretX=9;
        this->meretPen=100;


        break;
    case 2:
        this->meretY=15;
        this->meretX=19;
        this->meretPen=50;


        break;
    case 3:
        this->meretY=29;
        this->meretX=39;
        this->meretPen=25;

        break;
    case 4:
        this->meretY=59;
        this->meretX=79;
        this->meretPen=12;

        break;
    case 5:
        this->meretY=119;
        this->meretX=159;
        this->meretPen=6;

        break;
    default:
        this->meretY=29;
        this->meretX=39;
        this->meretPen=25;
        break;
    }

    ures(p);
    labirintus(p, 1, 1);

    /* bejarat es kijarat */
    p[1][0] = Jarat;
    p[this->meretY - 2][this->meretX - 1] = Jarat;

    update();
}


void MazeWidget::ures(Palya p) {
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
            if (y < this->meretY - 2 && p[y + 2][x] != Jarat) {
                p[y + 1][x] = Jarat;
                labirintus(p, x, y + 2);
            }
            break;
        case jobbra:
            if (x < this->meretX - 2 && p[y][x + 2] != Jarat) {
                p[y][x + 1] = Jarat;
                labirintus(p, x + 2, y);
            }
            break;
        }
}

void MazeWidget::paintEvent(QPaintEvent */*event*/)
{


    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.save();

    painter.setPen(QPen(Qt::blue, this->meretPen, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin));
    for (int y = 0; y < this->meretY; ++y) {
            for (int x = 0; x < this->meretX; ++x){
                if (p[x][y] == Fal){
                    painter.drawPoint(x*this->meretPen,y*this->meretPen);
                }
            }
        }

    painter.restore();

    painter.setRenderHint(QPainter::Antialiasing, false);
    painter.setPen(palette().dark().color());
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(QRect(0, 0, width() - 1, height() - 1));
}
