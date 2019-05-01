#ifndef MAZEWIDGET_H
#define MAZEWIDGET_H
#include <QPixmap>
#include <QPainter>
#include <QList>
#include <QWidget>


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
    }
    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;
    void setMaze(int size);

protected:
    void paintEvent(QPaintEvent *event) override;

private:   
    Palya p;
    void ures(Palya p);
    void labirintus(Palya p, int x, int y);
    int meretX = 33;
    int meretY = 25;
    int meretPen = 27;

};

#endif // MAZEWIDGET_H
