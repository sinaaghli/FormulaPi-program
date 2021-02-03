#include <webots/Robot.hpp>
#include <webots/Motor.hpp>
#include <webots/Camera.hpp>
#include <iostream>

using namespace webots;
using namespace std;

int main(int argc, char **argv) {
  // create the Robot instance.
  Robot *robot = new Robot();

  // get the time step of the current world.
  int timeStep = (int)robot->getBasicTimeStep();
  
  Camera* fpi_cam_dev = robot->getCamera("fpi_cam");
  fpi_cam_dev->enable(timeStep);
  const unsigned char *image = fpi_cam_dev->getImage();

  Motor *wheels[2];
  char wheelsNames[2][8] = {"wheel1", "wheel2"};
  wheels[0] = robot->getMotor(wheelsNames[0]);
  wheels[1] = robot->getMotor(wheelsNames[1]);
  double speed = 1.5; // [rad/s]
  wheels[0]->setPosition(INFINITY);
  wheels[0]->setVelocity(speed);
  wheels[1]->setPosition(INFINITY);
  wheels[1]->setVelocity(speed);
  
  Motor *servo[2];
  servo[0] = robot->getMotor("servo3");
  servo[1] = robot->getMotor("servo4");
  // servo[0]->setPosition(0.5);
  //servo[0]->setVelocity(speed);
//  servo[1]->setPosition(INFINITY);
//  servo[1]->setVelocity(speed);
  
  float pos=-1;
  
  while (robot->step(timeStep) != -1) {
    if(pos<1){
      pos +=0.01;
    }else{
      pos = -1;
    }
    servo[0]->setPosition(pos);
    servo[1]->setPosition(pos);
  };

  delete robot;
  return 0;
}
