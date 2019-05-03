#include "mainwindow.h"
#include <QApplication>
#include "serialreader.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    SerialReader serialReader;

    MainWindow w(&serialReader);

    //w.resize(900,800);



    w.show();



    serialReader.readingSerial();

    return a.exec();
}
