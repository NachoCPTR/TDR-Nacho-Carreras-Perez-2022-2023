#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61);

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *Motor1 = AFMS.getMotor(1);
// You can also make another motor on port M2
Adafruit_DCMotor *Motor2 = AFMS.getMotor(2);
// You can also make another motor on port M3
Adafruit_DCMotor *Motor3 = AFMS.getMotor(3);
// You can also make another motor on port M4
Adafruit_DCMotor *Motor4 = AFMS.getMotor(4);

const int PinTrig = 2;
const int PinEcho = 3;
const float VelSon = 34000.0;
float distancia;

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  pinMode(PinTrig, OUTPUT);
  pinMode(PinEcho, INPUT);
  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  
  // Set the speed to start, from 0 (off) to 255 (max speed)
  Motor1->setSpeed(150);
  Motor2->setSpeed(150);
  Motor3->setSpeed(150);
  Motor4->setSpeed(150); 

  //Direccion de los motores
  Motor1->run(FORWARD);
  Motor2->run(FORWARD);
  Motor3->run(FORWARD);
  Motor4->run(FORWARD);
  
  
  Motor1->run(RELEASE);
  Motor2->run(RELEASE);
  Motor3->run(RELEASE);
  Motor4->run(RELEASE);

  
}
//FORWARD motores van hacia delante
//BACKWARD motores van hacia atras
//RELEASE los motores pierden corriente y se paran
void loop() {
  iniciarTrigger();
    if(distancia < 30)
    {
      
      Motor1->run(FORWARD);
      Motor2->run(BACKWARD);
      Motor3->run(BACKWARD);
      Motor4->run(FORWARD);
      iniciarTrigger();
    }
    else
    {
      Motor1->run(FORWARD);
      Motor2->run(BACKWARD);
      Motor3->run(FORWARD);
      Motor4->run(BACKWARD);
    }
    /*Motor1->run(RELEASE);
    Motor2->run(RELEASE);
   Motor3->run(RELEASE);
    Motor4->run(RELEASE);
   delay(1000);*/
}
  
  

void iniciarTrigger()//describir que hace!!!!!!!!
{
  digitalWrite(PinTrig, LOW);
  delayMicroseconds(2);
  
  digitalWrite(PinTrig, HIGH);
  delayMicroseconds(10);
  
  // Comenzamos poniendo el pin Trigger en estado bajo
  digitalWrite(PinTrig, LOW);
  unsigned long tiempo = pulseIn(PinEcho, HIGH);
  distancia = tiempo * 0.000001 * VelSon / 2.0;
  Serial.print(distancia);
  Serial.print("cm");
  Serial.println();
}
