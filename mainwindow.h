#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include <QWidget>
#include "mazewidget.h"


class MazeWidget;
class SerialReader;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(SerialReader *);
    ~MainWindow();
    MazeWidget *myMaze;
    SerialReader* serial;
    void setSerialReader(SerialReader *);
private:
    QPushButton *m_button_next;
    QSlider *slider;
    //TODO: QLabel *sizeLabel;
    int mysize = 3;

private slots:
    void buttonNext();    
    void mazeChanged(int step);
    void shapeChanged();
};

#endif // MAINWINDOW_H
