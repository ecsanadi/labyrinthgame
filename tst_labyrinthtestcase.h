#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "mazewidget.h"
#include "mazewidget.cpp"
#include "points.h"
#include "serialreader.h"
#include <QPixmap>

using namespace testing;




TEST(labyrinthTestCase, labyrinthTestSet) {


    QPixmap qPixTest;
    qPixTest.load("/home/ecsanadi/Projects/labyrinthG/test/test_lab_img_2.jpg");

    SerialReader serial;

    Points startP;
    Points endP;
    startP.x = 2;
    startP.y = 30;
    serial.setPointX(2);
    serial.setPointY(30);
    endP.x = 19;
    endP.y = 41;
    serial.setPointX(19);
    serial.setPointY(41);

    //MazeWidget::getImage(qPixTest);
    //MazeWidget::checkWalls(startP, endP);

    EXPECT_EQ(117, serial.getPointX());
    EXPECT_EQ(145, serial.getPointY());
}
