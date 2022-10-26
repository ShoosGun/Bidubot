#include <Arduino.h>
#include <ServoEasing.hpp>

#include "VectorMath.hpp"
#include "Curves.hpp"
#include "RobotControll.hpp"

char Bsig = 0;
char Bev = '0';


bool st = true;
bool canMove = false;

//It was decided that, letters would better define a which leg is being mentioned
// N - (NORTE) reffers to front legs | S - (SUL) reffers to the back legs
//    O - (OESTE) and L - (LESTE) are intuitive

  // ( N )  ( O )  ( S )  ( L )  //

Leg NO{};
Leg NL{};
Leg SL{};
Leg SO{};

//You can change the initial rotation of Bidu by changing x,y,z values in Leg class. If you want to change only one leg consider this example
// NO.baseRot.x = 30; will change only the NORTE-OESTE leg; note that it must be set in setup() before LegAttaching.

void setup(){
  //The st boolean in pointless for now.
  //It was going to be used if there was another function that can be used only inside setup() |Attach is an example|
  if(st){
    NO.LegAttach(northWestPins,-1,-1,-1); NL.LegAttach(northEastPins,1,1,1);
    SO.LegAttach(southWestPins,-1,-1,1);  SL.LegAttach(southEastPins,1,1,-1);
  }
  Serial.begin(9600);
  Serial.println("Bidu is waking up!");
}
//This backLegMoveCycle and frontLegMoveCycle are triangle waves, but only the positiv part

Vector3 backLegMoveCycle(float t) 
{
  //This Cycle has period T = 1.f seconds
  const float T = 1.f;
  Vector3 returnValue{};
  
  float timeOnCycle = fmod(t, T);
  if(timeOnCycle < 0.f){
    timeOnCycle += T;
  }
   
  if(timeOnCycle < 0.5f){
    returnValue.x = timeOnCycle*45.f;
    returnValue.y = -timeOnCycle*30.f;    
    return returnValue;
  }
  
  returnValue.x = 45.f - (timeOnCycle - 0.5f)*45.f;
  returnValue.y = (timeOnCycle - 0.5f)*30.f - 30.f;
    
  return returnValue;
}

Vector3 frontLegMoveCycle(float t)
{
  //This Cycle has period T = 1.f seconds
  const float T = 1.f;
  Vector3 returnValue{};
  
  float timeOnCycle = fmod(t, T);
  if(timeOnCycle < 0.f){
    timeOnCycle += T;
  }
   
  if(timeOnCycle < 0.5f){
    returnValue.x = timeOnCycle*45.f;
    returnValue.y = -timeOnCycle*25.f;    
    return returnValue;
  }
  
  returnValue.x = 45.f - (timeOnCycle - 0.5f)*45.f;
  returnValue.y = (timeOnCycle - 0.5f)*25.f - 25.f;
    
  return returnValue;
}

Vector3FloatCurve noLegWalkCycle{frontLegMoveCycle, 0.5f, -1.f};
Vector3FloatCurve nlLegWalkCycle{frontLegMoveCycle, 0.f, 1.f};

Vector3FloatCurve soLegWalkCycle{frontLegMoveCycle, 0.5f, -1.f};
Vector3FloatCurve slLegWalkCycle{frontLegMoveCycle, 0.f, 1.f};

float currentTime = 0.f;
float deltaTime = 0.f;
void loop()//Compared to the previous version, instead of stopping and then resuming the loop, let's have a continuos loop and do math with a deltaT when doing something
{
  float newTime = millis();
  deltaTime = newTime - currentTime;
  currentTime = newTime;
  
  //this serves to send a signal to Bidu via bluetooth  
   if (Serial.available() > 0 ) 
   {
     Bsig =  Serial.read(); 
     Behavior(Bsig);
   }
   
   //Instead of using the write to match the angle, have a method which handles all the interpolation if we only have the target angle and the max speed it should reach
   //On the interpolation
  if (canMove){ //This walk cycles are just a type of curve, this means we should be able to animate it externally
    //or have a external program generate the walk cyle curves and then have bidu read and match the rotations on its joints.
    //Becase it is any function, we could even pass to it a music track and have the walk cycle be modulated to the sound wave
    NO.Write(noLegWalkCycle.Evaluate(currentTime));
    NL.Write(noLegWalkCycle.Evaluate(currentTime));
    SO.Write(noLegWalkCycle.Evaluate(currentTime));
    SL.Write(noLegWalkCycle.Evaluate(currentTime));
  }
  
  SL.Update(); 
  SO.Update(); 
  NL.Update(); 
  NO.Update(); 
}
  //Sets behavior of Bidu, he is not bipolar
void Behavior(char a)
{
  if (a != Bev){
    switch (a) {
      case '1':
        //Wake up
        Bev = '1';
        st = true;
        canMove = false;
        setup();
        break;
      case '2':
        //Move  
        Bev = '2';
        canMove = true;
        Serial.println("😳 look him go!");
        break;
      case '3':
        //Rotate -- cant apply rotation yet due to servo  S2 quality    
        Bev = '3';
        canMove = false;
        Serial.println("Bidu in spinnnnning!");
        break;
      case '4':
        //canSleep() function need to be implemented or Bidu will free fall
        NO.LegDetach();
        canMove = false;
        Serial.println("Bidu will take a nap");
        Bev = '4';
        break;  
  //Non-Essential interactions | Bown - Wave - Grove - Oscillate | for now wont be implemented
    }
  }
}
