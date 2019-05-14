#include <Arduino.h>


int get_freq(int nota,int oct){

  int freq;
  switch(nota){
    case 1: freq=440; break;
    case 2: freq=466; break;
    case 3: freq=494; break;
    case 4: freq=523; break;
    case 5: freq=554; break;
    case 6: freq=587; break;
    case 7: freq=622; break;
    case 8: freq=659; break;
    case 9: freq=698; break;
    case 10: freq=740; break;
    case 11: freq=784; break;
    case 12: freq=831; break;
  }

  for(int i=0; i<oct-1; i++)
    freq*=2;

  return freq;
}

//pins
int tone_pin=13;
//--------------------------------------------------------------------

// Declared weak in Arduino.h to allow user redefinitions.
int atexit(void (* /*func*/ )()) { return 0; }

// Weak empty variant initialization function.
// May be redefined by variant files.
void initVariant() __attribute__((weak));
void initVariant() { }

void setupUSB() __attribute__((weak));
void setupUSB() { }

int main(void)
{
	init();

	initVariant();

#if defined(USBCON)
	USBDevice.attach();
#endif

//----------------------------------SETUP--------------------------------------------------------

	Serial.begin(9600);

	//LEDs 1-12
	for (int i = 1; i <= 12; i++)
		pinMode(i, OUTPUT);

	//Variables
	int u_tiempo=150;
	int freq=0;
	int tmax=0;
  #include "melody.h";
  uint8_t n_melody=n_melody_mario;
  uint8_t melody[n_melody][3];
  for (int a = 0; a < n_melody; a++)
    for (int b = 0; b < 3; b++)
        melody[a][b]=melody_mario[a][b];

	bool play =false;
	bool rst=false;
	int i=0;

//----------------------------------------------------------------------------------------------

	for (;;) {

	//--------------------------------------LOOP--------------------------------------------------------


		if(Serial.available() > 0){

      		char r=Serial.read();
			if(r=='y'){
				play=true;
       			Serial.println("Playing song");
			}
			else if(r=='r'){
				i=0;
        		Serial.println("Reset playing");
			}
			else if(r=='s'){
				play=false;
		        noTone(tone_pin);
		        Serial.println("Stop playing");
			}
		}

		if(play){

			//Parameters calculation
   		int prev_nota;
			if(i>0)
				prev_nota=melody[i-1][1];
			else
				prev_nota=1;

			freq= get_freq(melody[i][1],melody[i][0]);
			tmax = (melody[i][2] * u_tiempo)/2;

			//Put tone
			noTone(tone_pin);
			digitalWrite(prev_nota, LOW);

			if(melody[i][1]!=0){
		        tone(tone_pin,freq);
		        digitalWrite(melody[i][1], HIGH);
     		 }
		 	delay(tmax);
		 	i++;
		 	if(i>=n_melody){
		 		play=false;
        noTone(tone_pin);
		 		i=0;
		 	}

		}


	//--------------------------------------------------------------------------------------------------

		if (serialEventRun) serialEventRun();
	}

	return 0;
}
