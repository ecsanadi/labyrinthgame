#ifndef MAZEWIDGET_H
#define MAZEWIDGET_H
#include <QPixmap>
#include <QPainter>
#include <QList>
#include <QWidget>
#include "lines.h"

class MazeWidget : public QWidget
{
    Q_OBJECT
private:
    QList<QList<bool>> vec_;
    std::vector<Lines> lineList;

public:
    MazeWidget(QWidget *parent = 0) :
        QWidget(parent)
    {
    }
    void setVec(QList<QList<bool>> const& vec);
    void setMaze(int newMaze);

protected:
    void paintEvent(QPaintEvent *event);
};

#endif // MAZEWIDGET_H
