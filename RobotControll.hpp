#ifndef ROBOT_CONTROLL_H
#define ROBOT_CONTROLL_H

#include "VectorMath.hpp"

static int northWestPins[]={53,29,8};
static int northEastPins[]={49,25,12};
static int southWestPins[]={17,21,45};
static int southEastPins[]={4,33,37};

class Leg
{
public: 
  //this defines to robot original pose.
  Vector3 baseRot{20,-40,0}; //Rotation In Euler Angles
  ServoEasing Mov[3];
  Vector3 rotationOnAttach{}; //Rotation In Euler Angles
  
  //the a,b,c must be set considering the servo orientation, this serves to normalize the positions of adjacent legs.
  void LegAttach(int pin[],int x, int y, int z);

  void LegDetach();

  void Update();
  
  void Write(Vector3 r);
};
#endif
