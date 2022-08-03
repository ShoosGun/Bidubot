#include <Arduino.h>
#include <ServoEasing.hpp>

class Leg
{
	public:
	int x = 30 , y = -30 , z =  0; 
	ServoEasing Mov[3];
	int Sym[2];
	void LegAttach(int pin[],int a, int b, int c)
	{
	Sym[0] = a; Sym[1] = b; Sym[2] = c;
 	Mov[0].attach(pin[0],90+x*a);
 	Mov[1].attach(pin[1],90+y*b);
 	Mov[2].attach(pin[2],60+z*c); 
	}

};
// N  O  S  L  //
Leg NO; Leg NL;
Leg SL; Leg SO;
void setup(){
	//Put port definition in only one array
static int a[]={53,29,8};
static int b[]={49,25,12};
static int c[]={17,21,45};
static int d[]={4,33,37};

NO.LegAttach(a,-1,-1,-1);

NL.LegAttach(b,1,1,1);

SO.LegAttach(c,-1,-1,1);

SL.LegAttach(d,1,1,-1);

}

void loop()
{

}

void Waving(Leg& obj, int rot,int angle,int speed){
	float a,b,c;
        a = obj.Mov[0].read(); //Triangle Rule Implementation Needed
        b = obj.Mov[1].read(); 
        c = obj.Mov[2].read(); 
	obj.Mov[0].startEaseTo(a+angle*obj.Sym[0]*rot, speed , START_UPDATE_BY_INTERRUPT);
	obj.Mov[1].startEaseTo(b+(angle-10)*-1*obj.Sym[1]*rot, speed , START_UPDATE_BY_INTERRUPT);
	//obj.Mov[2].startEaseTo(a+20*obj.Sym[2]*rot, 20 , START_UPDATE_BY_INTERRUPT);
}
