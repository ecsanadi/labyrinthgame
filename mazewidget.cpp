#include "mazewidget.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*MazeWidget::MazeWidget(QWidget *parent = 0):
    QWidget(parent)
{
}*/




void MazeWidget::setVec(QList<QList<bool>> const& vec)
{
    vec_ = vec;
    // You can pre-paint pixmaps here, if you keep vec_ as value or make a function and keep it updated.
}

QSize MazeWidget::minimumSizeHint() const
{
    return QSize(100, 100);
}

QSize MazeWidget::sizeHint() const
{

    return QSize(900, 700);
}


void MazeWidget::setMaze(/*int newMaze*/)
{
    //todo this vector that vector
    //actualLineList = lineVecList[newMaze];
    //generate();
    //this->actualLineList = this->lineList;
    //repaint();
    //this->repaint();
    //Palya p;

    srand(time(0));
    /* ures palyara general egy labirintust */
    ures(p);
    labirintus(p, 1, 1);
    /* bejarat es kijarat */
    p[1][0] = Jarat;
    p[MERETY - 2][MERETX - 1] = Jarat;
    /* mehet kirajzolasra */
    //kirajzol(p);
    update();
}

void MazeWidget::createLine(int sx, int sy, int ex, int ey)
{
    line = new Line(sx,sy,ex,ey);
    this->lineList.push_back(line);

}



void MazeWidget::generate()
{
    //todo generate constant labyrinths into lineList and than store in the base vector
    //std::vector<Lines> lineList;
    //std::vector<std::vector<Lines> > lineVecList;
    //std::vector<Lines> actualLineList;

    createLine(1,1,799,1);
    createLine(1,1,799,1);
    createLine(100,1,100,100);
    createLine(100,100,799,100);
    createLine(799,1,799,600);
    createLine(700,100,700,200);
    createLine(700,200,799,200);
    createLine(1,100,1,699);
    createLine(1,200,100,200);
    createLine(100,200,100,600);
    createLine(1,600,100,600);
    createLine(1,699,799,699);
    createLine(200,200,200,699);
    createLine(200,200,600,200);
    createLine(300,300,799,300);
    createLine(300,300,300,400);
    createLine(300,400,799,400);
    createLine(300,600,600,600);
    createLine(300,600,300,699);
    createLine(700,600,799,600);

}

void MazeWidget::ures(Palya p) {
    for (int y = 0; y < MERETY; ++y)
        for (int x = 0; x < MERETX; ++x)
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
            if (y < MERETY - 2 && p[y + 2][x] != Jarat) {
                p[y + 1][x] = Jarat;
                labirintus(p, x, y + 2);
            }
            break;
        case jobbra:
            if (x < MERETX - 2 && p[y][x + 2] != Jarat) {
                p[y][x + 1] = Jarat;
                labirintus(p, x + 2, y);
            }
            break;
        }
}

void MazeWidget::paintEvent(QPaintEvent */*event*/)
{

    /*QPixmap pixmap(vec_.front().size(), vec_.size()); // pixmap with scale 1:1
    QPainter pixmap_painter(&pixmap);

    for(int y = 0; y < vec_.size(); y++)
        for(int x = 0; x < vec_[y].size(); x++)
        {
            pixmap_painter.setPen(vec_[y][x] ? QColor("white") : QColor("red"));
            pixmap_painter.drawPoint(x, y); // Draw individual pixels
        }

    QPainter painter(this);
    QPixmap pixmap_scaled = pixmap.scaled(size(), Qt::KeepAspectRatio); // scale to fit the widget
    painter.drawPixmap(
        (width() - pixmap_scaled.width()) / 2,
        (height() - pixmap_scaled.height()) / 2,
        pixmap_scaled.width(), pixmap_scaled.height(), pixmap_scaled); // draw with alignment in the middle*/

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.save();



    //save into a vector and draw each point

   /* for(std::vector<Line *>::iterator it = actualLineList.begin(); it != actualLineList.end(); ++it) {

              int w = 4;
              painter.setPen(QPen(Qt::blue, w, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin));
              painter.drawLine((*it)->beginX,(*it)->beginY,(*it)->endX,(*it)->endY);

    }*/
    int w = 25;
    painter.setPen(QPen(Qt::blue, w, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin));

    for (int y = 0; y < MERETY; ++y) {
            for (int x = 0; x < MERETX; ++x){
                /* itt hasznalja ki, hogy az enum ertekek szandekosan
                 * egyeznek a karakterkodokkal */
                //putchar(p[y][x]);
                if (p[x][y] == Fal){
                    painter.drawPoint(x*25,y*25);
                }
            }
            //putchar('\n');
        }


    //draw a "cursor" point

    painter.restore();

    painter.setRenderHint(QPainter::Antialiasing, false);
    painter.setPen(palette().dark().color());
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(QRect(0, 0, width() - 1, height() - 1));
}
