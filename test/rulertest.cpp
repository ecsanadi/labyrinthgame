#include <limits.h>

#include "gtest/gtest.h"

#include "mazewidget.h"



class RulerTest : public ::testing::Test {

 protected:

  virtual void SetUp() {

  }



  virtual void TearDown() {

    // Code here will be called immediately after each test

    // (right before the destructor).

  }

};



TEST_F(RulerTest,twoValues){

    MazeWidget myTestMaze;


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

     myTestMaze.getImage(qPixTest);
     myTestMaze.checkWalls(startP, endP);

     EXPECT_EQ(117, serial.getPointX());
     EXPECT_EQ(145, serial.getPointY());

}
