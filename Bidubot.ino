#include <Arduino.h>
#include <ServoEasing.hpp>

#define pi 3.141592653589793
// N  O  S  L  //
ServoEasing NO[3];
ServoEasing SO[3];
ServoEasing NL[3];
ServoEasing SL[3];

int x,y,z;
bool whave = false;

void setup(){
// 0 ==> Braço | 1 ==> Ombro | 2 ==> Joelho //
   x = 30; //| 0---to---80 |// Maximum
   y = -30;//| -50---to---50 |// Maximum
   z = 0; //| 40--to---80 |// Maximum

   NO[0].attach(53);
   NO[1].attach(29);
   NO[2].attach(8);
   NO[0].write(90-x);
   NO[1].write(90-y);
   NO[2].write(60-z);
//
   SO[0].attach(17); 
   SO[1].attach(21); 
   SO[2].attach(45);
   SO[0].write(90-x);
   SO[1].write(90-y); 
   SO[2].write(60+z);
//
   NL[0].attach(49);
   NL[1].attach(25);
   NL[2].attach(12);
   NL[0].write(90+x);
   NL[1].write(90+y);
   NL[2].write(60+z); // Má distribuição de peso 
//   
   SL[0].attach(4);
   SL[1].attach(33);
   SL[2].attach(37);
   SL[0].write(90+x);
   SL[1].write(90+y);
   SL[2].write(60-z);
//Group Manipulation

}


void loop()
{

Waving(SL,1);
Waving(SO,-1);
delay(5000);
Waving(NL,-1);
Waving(NO,1);
delay(5000);


Waving(NL,1);
Waving(NO,-1);
delay(5000);
Waving(SL,-1);
Waving(SO,1);
delay(5000);

}



void Waving(ServoEasing LEG[],int al){

	float a,b,c;
        a = LEG[0].read(); 
        b = LEG[1].read();
	LEG[0].startEaseTo(a+25*al,40,START_UPDATE_BY_INTERRUPT);
	LEG[1].startEaseTo(b-20*al,30,START_UPDATE_BY_INTERRUPT);


}

