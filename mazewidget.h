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
    void generate();

};

#endif // MAZEWIDGET_H
