#include "mainwindow.h"
#include <QApplication>
#include "serialreader.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    SerialReader serialReader;

    MainWindow w(&serialReader);

    QSize screenSize = a.desktop()->availableGeometry().size();

    int myHeight = screenSize.height();
    int myWidth =screenSize.width();

    if (myWidth-myHeight>=500)
    {

        w.resize(900,850);
    }

    w.show();

    serialReader.readingSerial();

    return a.exec();
}
