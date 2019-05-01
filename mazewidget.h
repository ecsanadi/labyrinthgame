#ifndef MAZEWIDGET_H
#define MAZEWIDGET_H
#include <QPixmap>
#include <QPainter>
#include <QList>
#include <QWidget>
#include "serialreader.h"

#define MERETX 153
#define MERETY 119

typedef enum Cella { Jarat = 0, Fal = 1 } Cella;
typedef Cella Palya[MERETY][MERETX];

class MazeWidget : public QWidget
{
    Q_OBJECT

public:
    MazeWidget(QWidget *parent = 0) :
        QWidget(parent)
    {
        setBackgroundRole(QPalette::Base);
        shape = Line;
        iniPoint.x=2;
        iniPoint.y=20;
        pointList.push_back(iniPoint);
    }
    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;
    void setMaze(int size);
    enum Shape { Line/*, Points, Polyline, Polygon, Rect, RoundedRect, Ellipse, Arc,
                 Chord, Pie, Path, Text, Pixmap */};
    void setSerialReader(SerialReader *);

protected:
    void paintEvent(QPaintEvent *event) override;

private:   
    Palya p;
    void ures(Palya p);
    void labirintus(Palya p, int x, int y);
    int meretX = 33;
    int meretY = 25;
    int meretPen = 27;
    Shape shape;
    SerialReader* serial;
    Points point;
    Points iniPoint;
    std::vector<Points> pointList;

public slots:
    void setShape(Shape shape);

};

#endif // MAZEWIDGET_H
