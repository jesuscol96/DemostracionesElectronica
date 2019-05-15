#include <Arduino.h>
#include "Servo.h"
/*
Interaccion entre Arduino y OpenCV
Codigo para Arduino


Por Glar3
*/

#define VERDE 6
#define AZUL 7
#define ROJO 11
char lectura; //Variable para guardar la lectura del Serial

void setup()
{
   //Iniciamos el Serial:
   Serial.begin(9600);
   //servoMotor.attach(12);
   //Inicializamos el pin 13
   pinMode(VERDE, OUTPUT);
   pinMode(AZUL, OUTPUT);
   pinMode(ROJO, OUTPUT);
}

void loop()
{
   //Si recibimos algo por serial, lo guardamos
   if(Serial.available() >= 1)
   {
      lectura = Serial.read();
      switch ( lectura )
      {
         case 'h':
            digitalWrite(VERDE, HIGH);
          //  servoMotor.write(80);
          //  delay(1000);
            break;
         case 'a':
            digitalWrite(AZUL, HIGH);
            //servoMotor.write(80);
            //  delay(1000);
            break;
        case 'r':
            digitalWrite(ROJO, HIGH);
            break;

         default:

            digitalWrite(VERDE, LOW);
            digitalWrite(ROJO, LOW);
            digitalWrite(AZUL, LOW);
      }

   }
}
