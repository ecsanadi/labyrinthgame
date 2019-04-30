#ifndef MAZEWIDGET_H
#define MAZEWIDGET_H
#include <QPixmap>
#include <QPainter>
#include <QList>
#include <QWidget>
#include "line.h"


#define MERETX 79
#define MERETY 29

/* szandekosan karakterkodok, igy konnyu printfelni */


typedef enum Cella { Jarat = 0, Fal = 1 } Cella;
typedef Cella Palya[MERETY][MERETX];
/*typedef Cella Palya2[11][15];
typedef Cella Palya3[23][31];
typedef Cella Palya4[47][63];
typedef Cella Palya5[95][127];
typedef Cella Palya6[191][255];
typedef Cella Palya7[383][511];
typedef Cella Palya8[500][700];*/

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
    void setMaze(/*int newMaze*/);
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
    void generate();
    void ures(Palya p);
    void labirintus(Palya p, int x, int y);


};

#endif // MAZEWIDGET_H
