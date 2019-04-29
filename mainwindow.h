#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QPushButton>
#include <QMainWindow>
#include "mazewidget.h"

namespace Ui {
class MainWindow;
}
class MazeWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void mazeChanged(int step);
    MazeWidget *myMaze;
private:
    Ui::MainWindow *ui;
    QPushButton *m_button_next;
    QPushButton *m_button_prev;
private slots:

    void buttonNext();
    void buttonPrev();
};

#endif // MAINWINDOW_H
