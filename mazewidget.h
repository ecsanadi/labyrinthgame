#ifndef MAZEWIDGET_H
#define MAZEWIDGET_H
#include <QPixmap>
#include <QPainter>
#include <QList>
#include <QWidget>
#include "line.h"


#define MERETX 159
#define MERETY 119



/* szandekosan karakterkodok, igy konnyu printfelni */


typedef enum Cella { Jarat = 0, Fal = 1 } Cella;
typedef Cella Palya[MERETY][MERETX];
/*typedef Cella Palya1[7][9];
typedef Cella Palya2[15][19];
typedef Cella Palya3[29][39];
typedef Cella Palya4[59][79];
typedef Cella Palya5[119][159];*/


class MazeWidget : public QWidget
{
    Q_OBJECT


public:
    MazeWidget(QWidget *parent = 0) :
        QWidget(parent)
    {
        setBackgroundRole(QPalette::Base);
        setAutoFillBackground(true);

    }
    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;
    void setVec(QList<QList<bool>> const& vec);
    void setMaze(int size);
    void createLine(int, int, int, int);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QList<QList<bool>> vec_;
    std::vector<Line *> lineList;
    std::vector<std::vector<Line *> > lineVecList;
    std::vector<Line *> actualLineList;
    Line *line;
    Palya p;
    /*Palya1 p1;
    Palya2 p2;
    Palya3 p3;
    Palya4 p4;
    Palya5 p5;*/
    int* pp = NULL;
    void generate();
    void ures(Palya p);
    void labirintus(Palya p, int x, int y);
    //void ures(int *);
    //void labirintus(int *, int x, int y);
    int scrollSize=1;
    int meretX = 79;
    int meretY = 29;
    int meretPen = 25;

};

#endif // MAZEWIDGET_H
