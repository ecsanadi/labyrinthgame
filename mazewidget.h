#ifndef MAZEWIDGET_H
#define MAZEWIDGET_H
#include <QPixmap>
#include <QPainter>
#include <QList>
#include <QWidget>
#include "line.h"

class MazeWidget : public QWidget
{
    Q_OBJECT
private:
    QList<QList<bool>> vec_;
    std::vector<Line *> lineList;
    std::vector<std::vector<Line *> > lineVecList;
    std::vector<Line *> actualLineList;
    Line *line;
    void generate();

public:
    MazeWidget(QWidget *parent = 0) :
        QWidget(parent)
    {
    }
    void setVec(QList<QList<bool>> const& vec);
    void setMaze(/*int newMaze*/);
    void createLine(int, int, int, int);

protected:
    void paintEvent(QPaintEvent *event);

};

#endif // MAZEWIDGET_H
