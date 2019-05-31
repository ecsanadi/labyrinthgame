#ifndef MAZEWIDGET_H
#define MAZEWIDGET_H
#include <QPixmap>
#include <QPainter>
#include <QList>
#include <QWidget>
#include "serialreader.h"
#include <QImage>
#include <QColor>

#define SIZEX 153
#define SIZEY 119

typedef enum Cell { Path = 0, Wall = 1 } Cell;
typedef Cell Field[SIZEY][SIZEX];

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
    void checkWalls(Points tempPoint, Points endPoint);
    void getImage(QPixmap pQPix);

protected:
    void paintEvent(QPaintEvent *event) override;

private:   
    Field p;
    void empty(Field p);
    void labyrintGenerator(Field p, int x, int y);
    int sizeX = 33;
    int sizeY = 25;
    int sizePen = 27;
    Shape shape;
    SerialReader* serial;
    Points point;
    Points iniPoint;
    std::vector<Points> pointList;
    void checkWindowEdges();
    void restoreRotaryPosition();
    void getEndPixels();
    //void getImage(QPixmap pQPix);
    void getImage();
    Points endpoints;
    Points prevpoint;
    int endLineBeginX;
    int endLineBeginY;
    int endLineEndY;
    QImage image;
    QPixmap qPix;
    QColor color;
    //void checkWalls(Points tempPoint, Points endPoint);
    bool checkBlackPix(int px, int py);


public slots:
    void setShape(Shape shape);

signals:
    void winGame();

};

#endif // MAZEWIDGET_H
