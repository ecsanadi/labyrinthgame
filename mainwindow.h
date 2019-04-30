#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QPushButton>
#include <QSlider>
#include <QLabel>
//#include <QMainWindow>
#include <QWidget>
#include "mazewidget.h"

/*namespace Ui {
class MainWindow;
}*/
class MazeWidget;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    //explicit MainWindow(QWidget *parent = 0);
    MainWindow();
    ~MainWindow();

    MazeWidget *myMaze;
private:
   // Ui::MainWindow *ui;
    QPushButton *m_button_next;
    QPushButton *m_button_prev;
    QSlider *slider;
    QLabel *sizeLabel;
    int mysize = 3;
private slots:

    void buttonNext();
    void buttonPrev();
    void setSize(int);
    void mazeChanged(int step);
};

#endif // MAINWINDOW_H
