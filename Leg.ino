//#include "CalledLibs.hpp"
//This is a .ino file, so we don't need to worry about calling #include <ServoEasing.hpp> (why arduino why)
void Leg::LegAttach(int pin[],int x, int y, int z) 
{
  rotationOnAttach= Vector3{x, y, z};
  Mov[0].attach(pin[0], 90 + baseRot.x*x); //foot - S0
  Mov[1].attach(pin[1], 90 + baseRot.y*y);  //elbow - S1
  Mov[2].attach(pin[2], 60 + baseRot.z*z);   //sholder - S2
}

void Leg::LegDetach()
{
  //THIS 'KILLS' BIDU 
  Mov[0].detach();
  Mov[1].detach();
  Mov[2].detach(); 
}

void  Leg::Write(Vector3 r)
{  
  Mov[0].write(r.x);
  Mov[1].write(r.y);
  Mov[2].write(r.z); 
}
  
void Leg::Update()
{ 
  Mov[0].update();
  Mov[1].update();
  Mov[2].update(); 
}
