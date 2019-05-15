#include <Arduino.h>
#include "Servo.h"

// Declaramos la variable para controlar el servo
Servo servoMotor;

void setup() {
  // Iniciamos el monitor serie para mostrar el resultado
  Serial.begin(9600);

  // Iniciamos el servo para que empiece a trabajar con el pin 9
  servoMotor.attach(12);
}

void loop() {

  // Desplazamos a la posición 0º
  servoMotor.write(80);
  // Esperamos 1 segundo
  delay(1000);
  servoMotor.write(150);
  // Esperamos 1 segundo
  delay(1000);

}
