#include "mazewidget.h"


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

    return QSize(800, 700);
}


void MazeWidget::setMaze(/*int newMaze*/)
{
    //todo this vector that vector
    //actualLineList = lineVecList[newMaze];
    generate();
    this->actualLineList = this->lineList;
    //repaint();
    //this->repaint();
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

    for(std::vector<Line *>::iterator it = actualLineList.begin(); it != actualLineList.end(); ++it) {

              int w = 4;
              painter.setPen(QPen(Qt::blue, w, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin));
              painter.drawLine((*it)->beginX,(*it)->beginY,(*it)->endX,(*it)->endY);

    }




    //draw a "cursor" point

    painter.restore();

    painter.setRenderHint(QPainter::Antialiasing, false);
    painter.setPen(palette().dark().color());
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(QRect(0, 0, width() - 1, height() - 1));
}
