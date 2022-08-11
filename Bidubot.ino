#include <Arduino.h>
#include <ServoEasing.hpp>

char Bsig = 0;
char Bev = '0';

static int a[]={53,29,8};
static int b[]={49,25,12};
static int c[]={17,21,45};
static int d[]={4,33,37};

bool st = true;

class Leg
{
	public:	
	int x = 20 , y = -40 , z = 0; 
	ServoEasing Mov[3];
	int Sym[2];
	void LegAttach(int pin[],int a, int b, int c)
	{
	Sym[0] = a; Sym[1] = b; Sym[2] = c;
 	Mov[0].attach(pin[0],90+x*a);
 	Mov[1].attach(pin[1],90+y*b);
 	Mov[2].attach(pin[2],60+z*c); 
	}
	void LegDetach()
	{
 	Mov[0].detach(); Mov[1].detach(); Mov[2].detach(); 
	}
};
	// ( N )  ( O )  ( S )  ( L )  //

Leg NO; Leg NL; Leg SL; Leg SO;

void setup(){
	if(st){
		NO.LegAttach(a,-1,-1,-1); NL.LegAttach(b,1,1,1);
		SO.LegAttach(c,-1,-1,1);  SL.LegAttach(d,1,1,-1);
	}
	Serial.begin(9600);
	Serial.println("WAKE");
}
void loop()
{
   if (Serial.available() > 0 ) 
   {	
   Bsig =  Serial.read(); 
   Behavior(Bsig);
   }

//This moves Bidu for now
Delegate(NO,1,-1,45,25,90,100);
Delegate(SL,1,-1,45,30,90,100);
delay(400);
Delegate(NL,1,-1,45,25,90,100);
Delegate(SO,1,-1,45,30,90,100);
Delegate(SL,-1,1,45,30,90,100);
Delegate(NO,-1,1,45,25,90,100);
delay(400);
Delegate(SO,-1,1,45,30,90,100);
Delegate(NL,-1,1,45,25,90,100);

//Leg retraction 
   //Sholder rotation
   	//Foot tracing
   		//Reset postion
	//This move delegation is not working due to Servo malfunction
}

void Delegate(Leg& obj, int rot1,int rot2,int angle1,int angle2,int speed1,int speed2)
{
	float a,b;
        a = obj.Mov[0].read(); 
        b = obj.Mov[1].read(); 
	obj.Mov[0].startEaseTo(a+angle1*obj.Sym[0]*rot1, speed1 , START_UPDATE_BY_INTERRUPT);
	obj.Mov[1].startEaseTo(b+angle2*obj.Sym[1]*rot2, speed2 , START_UPDATE_BY_INTERRUPT);
}
void Behavior(char a)
{
	if (a != Bev){
		switch (a) {
			case '1':
			//Wake up
				Bev = '1';
				st = true;
				setup();
				break;
			case '2':
			//Move	
				Bev = '2';
				Serial.println("MOVE");
				break;
			case '3':
			//Rotate -- cant apply rotation yet due to servo  S2 quality		
				Bev = '3';
				Serial.println("ROTATE");
				break;
			case '4':
				NO.LegDetach();
				Serial.println("SLEEP");
				Bev = '4';
				break;	

	//Non-Essential interactions | Bown - Wave - Grove - Oscillate | for now wont be implemented
		}
	}
}
