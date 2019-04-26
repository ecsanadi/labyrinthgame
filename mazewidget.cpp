#include "mazewidget.h"


/*MazeWidget::MazeWidget(QWidget *parent = 0):
    QWidget(parent)
{
}*/


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

    for(std::vector<Lines>::iterator it = lineList.begin(); it != lineList.end(); ++it) {



              int w = 4;
              painter.setPen(QPen(Qt::black, w, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin));
              painter.drawLine(it->beginX,it->beginY,it->endX,it->endY);


    }

    //draw a "cursor" point

    painter.restore();

    painter.setRenderHint(QPainter::Antialiasing, false);
    painter.setPen(palette().dark().color());
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(QRect(0, 0, width() - 1, height() - 1));
}

void MazeWidget::setVec(QList<QList<bool>> const& vec)
{
    vec_ = vec;
    // You can pre-paint pixmaps here, if you keep vec_ as value or make a function and keep it updated.
}

void MazeWidget::setMaze(int newMaze)
{
    //todo this vector that vector
    update();
}
