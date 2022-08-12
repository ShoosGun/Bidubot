#include <Arduino.h>
#include <ServoEasing.hpp>

char Bsig = 0;
char Bev = '0';

static int a[]={53,29,8};
static int b[]={49,25,12};
static int c[]={17,21,45};
static int d[]={4,33,37};

bool st = true;
bool canMove = false;

class Leg
{
	public:	
		//this defines to robot original pose.
	int x = 20 , y = -40 , z = 0; 
	ServoEasing Mov[3];
	int Sym[2];
	
	//the a,b,c must be set considering the servo orientation, this serves to normalize the positions of adjacent legs.

	void LegAttach(int pin[],int a, int b, int c)
	{
	Sym[0] = a; Sym[1] = b; Sym[2] = c;
 	Mov[0].attach(pin[0],90+x*a); //foot - S0
 	Mov[1].attach(pin[1],90+y*b);  //elbow - S1
 	Mov[2].attach(pin[2],60+z*c); 	//sholder - S2
	}

	void LegDetach()
	{
		//THIS 'KILLS' BIDU 
 	Mov[0].detach(); Mov[1].detach(); Mov[2].detach(); 
	}
};


//It was decided that, letters would better define a which leg is being mentioned
// N - (NORTE) reffers to front legs | S - (SUL) reffers to the back legs
// 		O - (OESTE) and L - (LESTE) are intuitive

	// ( N )  ( O )  ( S )  ( L )  //

Leg NO; Leg NL; Leg SL; Leg SO;

//You can change the initial pose of Bidu by changing x,y,z values in Leg class. If you want to change only one leg consider this example
// NO.x = 30; will change only the NORTE-OESTE leg; note that it must be set in setup() before LegAttaching.

void setup(){
	//The st boolean in pointless for now.
	//It was going to be used if there was another function that can be used only inside setup() |Attach is a example|
	if(st){

		NO.LegAttach(a,-1,-1,-1); NL.LegAttach(b,1,1,1);
		SO.LegAttach(c,-1,-1,1);  SL.LegAttach(d,1,1,-1);

	}
	Serial.begin(9600);
	Serial.println("Bidu is waking up!");
}

void loop()
{
	//this serves to send a signal to Bidu via bluetooth	
   if (Serial.available() > 0 ) 
   {	
   Bsig =  Serial.read(); 
   Behavior(Bsig);
   }

	//this is a alternative walking cycle, for now it is broken.
//Delegate(NO,-1,1,15,40,90,100);
//Delegate(SL,-1,1,15,40,90,100);
//delay(600);
//Delegate(SO,-1,1,15,40,90,100);
//Delegate(NL,-1,1,15,40,90,100);
//
//delay(200);
//
//Delegate(NO,1,-1,30,40,90,100);
//Delegate(SL,1,-1,30,40,90,100);
//delay(450);
//Delegate(SO,1,-1,30,40,90,100);
//Delegate(NL,1,-1,30,40,90,100);
//
//delay(200);
//
//Delegate(NO,-1,0,15,0,90,0);
//Delegate(SL,-1,0,15,0,90,0);
//delay(200);
//Delegate(SO,-1,0,15,0,90,0);
//Delegate(NL,-1,0,15,0,90,0);
   
   //this moves bidu for now,
   	//but it is lacking impulse.
if (canMove){
Delegate(SL,1,-1,45,30,90,100);
delay(500);
Delegate(NL,1,-1,45,25,90,100);
Delegate(SO,1,-1,45,30,90,100);
Delegate(SL,-1,1,45,30,90,100);
Delegate(NO,-1,1,45,25,90,100);
delay(500);
Delegate(SO,-1,1,45,30,90,100);
Delegate(NL,-1,1,45,25,90,100);

}
}

void Delegate(Leg& obj, int rot1,int rot2,int angle1,int angle2,int speed1,int speed2)
{
		//This function moves S0 and S1 smoothly.
			//Do not try to implement another component here (S2) it will break;
	float a,b;
        a = obj.Mov[0].read(); 
        b = obj.Mov[1].read(); 
	obj.Mov[0].startEaseTo(a+angle1*obj.Sym[0]*rot1, speed1 , START_UPDATE_BY_INTERRUPT);
	obj.Mov[1].startEaseTo(b+angle2*obj.Sym[1]*rot2, speed2 , START_UPDATE_BY_INTERRUPT);

}
	//Sets behavir of Bidu, he is not bipolar
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
