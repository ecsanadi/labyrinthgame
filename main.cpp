#include "mainwindow.h"
#include <QApplication>
//#include <QSize>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //QSize screenSize = a.desktop()->availableGeometry().size();

    MainWindow w;

    //QSize screenSize = a.desktop()->availableGeometry().size();


    /*int myHeight = screenSize.height();
    int myWidth =screenSize.width();
    myHeight *= 0.9;
    myWidth *= 0.9;    
*/
    w.resize(900,800);


    w.show();

    return a.exec();
}
