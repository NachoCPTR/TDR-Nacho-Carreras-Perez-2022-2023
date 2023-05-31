#include <Servo.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

Adafruit_DCMotor *Motor1 = AFMS.getMotor(1);
Adafruit_DCMotor *Motor2 = AFMS.getMotor(2);
Adafruit_DCMotor *Motor3 = AFMS.getMotor(3);
Adafruit_DCMotor *Motor4 = AFMS.getMotor(4);

int speed = 100;

const int s0 = 8;
const int s1 = 9;
const int s2 = 12;
const int s3 = 11;
const int out = 13;

const int PinTrig = 6;
const int PinEcho = 7;
const float VelSon = 34000.0;
float distancia;

byte countRed = 0;
byte countGreen = 0;
byte countBlue = 0;

bool lado = false;
bool detectado = false;
int error = 0;
bool primerWhile = true;

Servo servomotor;


void setup() { 
  Serial.begin(9600);

  servomotor.attach(10);
  servomotor.write(90);

  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(PinTrig, OUTPUT);
  pinMode(PinEcho, INPUT);

  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(out, INPUT);
  digitalWrite(s0, HIGH);
  digitalWrite(s1, HIGH);
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);

  pinMode(PinTrig, OUTPUT);
  pinMode(PinEcho, INPUT);
  AFMS.begin();

  Motor1->setSpeed(speed);
  Motor2->setSpeed(speed);
  Motor3->setSpeed(speed);
  Motor4->setSpeed(speed); 

  Motor1->run(FORWARD);
  Motor2->run(FORWARD);
  Motor3->run(FORWARD);
  Motor4->run(FORWARD);
  
  
  Motor1->run(RELEASE);
  Motor2->run(RELEASE);
  Motor3->run(RELEASE);
  Motor4->run(RELEASE);

}

void loop() {
  iniciarTrigger();
  while(distancia <= 50)
  {
    iniciarTrigger();
    if(primerWhile)
    {
    Motor1->run(BACKWARD);
    Motor2->run(BACKWARD);
    Motor3->run(BACKWARD);
    Motor4->run(BACKWARD);
               
    delay(50);
    primerWhile =  false;   
    }
    
    Motor1->run(RELEASE);
    Motor2->run(RELEASE);
    Motor3->run(RELEASE);
    Motor4->run(RELEASE);
    servomotor.write(0);      
    for(int i = 0; i < 180; i++)
    {
      iniciarTrigger();
      servomotor.write(i);
      if(distancia <= 50 && i <= 90)
      {
        Motor3->run(BACKWARD);
        Motor4->run(BACKWARD);
        Motor1->run(FORWARD);
        Motor2->run(FORWARD);        
      }
      else if(distancia <= 50 && i >=90)
      {
        Motor3->run(FORWARD);
        Motor4->run(FORWARD);
        Motor1->run(BACKWARD);
       Motor2->run(BACKWARD);          
      }    
      else
      {
            Motor1->run(RELEASE);
    Motor2->run(RELEASE);
    Motor3->run(RELEASE);
    Motor4->run(RELEASE);        
      }  
    }       
  servomotor.write(90);
  }
  servomotor.write(90);
  primerWhile = true;  
  if(error % 5 == 0)
  {
    if(error >= 30)
    {
      Motor3->run(RELEASE);
      Motor4->run(RELEASE);
      Motor1->run(FORWARD);
      Motor2->run(FORWARD);
    }
  }
  else
  {
      Motor1->run(FORWARD);
      Motor2->run(FORWARD);
      Motor3->run(FORWARD);
      Motor4->run(FORWARD);
  }
  error++; 
}
/*
  for(int tiempoMotor = 0; tiempoMotor <= 550; tiempoMotor++)
  {
    if(tiempoMotor % 5 == 0)
    {
      Motor3->run(RELEASE);
      Motor4->run(RELEASE);
      Motor1->run(FORWARD);
      Motor2->run(FORWARD);
    }
    else
    {
      Motor1->run(FORWARD);
      Motor2->run(FORWARD);
      Motor3->run(FORWARD);
      Motor4->run(FORWARD); 
    }

  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
  }
Motor1->run(RELEASE);
Motor2->run(RELEASE);
Motor3->run(RELEASE);
Motor4->run(RELEASE); 

for(int tiempoMotor = 0; tiempoMotor <= 110; tiempoMotor++)
{
  if(tiempoMotor <= 45)
  {
    Motor1->run(FORWARD);
    Motor2->run(FORWARD);
    Motor3->run(BACKWARD);
    Motor4->run(BACKWARD);     
  }
  Motor1->run(FORWARD);
  Motor2->run(FORWARD);
  Motor3->run(RELEASE);
  Motor4->run(RELEASE); 

  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
  
}
Motor1->run(RELEASE);
Motor2->run(RELEASE);
Motor3->run(RELEASE);
Motor4->run(RELEASE); 

delay(1000); 
}
/*  
for(int i = 0; i <= 180; i++)
{
  angulo = i;
  servomotor.write(i);
  iniciarTrigger();

} 
  switch (angulo)
  {
    case 1 : distancia >= 30;
      Motor1->run(BACKWARD);
      Motor2->run(BACKWARD);
      Motor3->run(FORWARD);
      Motor4->run(FORWARD);
    break;

    case 2 : distancia <= 30;
      Motor1->run(FORWARD);
      Motor2->run(FORWARD);
      Motor3->run(BACKWARD);
      Motor4->run(BACKWARD);
    break;
    
    default :
      Motor1->run(FORWARD);
      Motor2->run(FORWARD);
      Motor3->run(FORWARD);
      Motor4->run(FORWARD);
  }
  servomotor.write(0);

/*
   for (int i = 0; i <= 180; i++)
  {
    //lado = false;
    angulo = i;
    iniciarTrigger();
    //movimientoMotores();
    servomotor.write(i);
    delay(5);
  }
  // Para el sentido negativo
  for (int i = 180; i >= 0; i--)
  {
    //lado = true;
    angulo = i; 
    iniciarTrigger();
  //movimientoMotores();
    servomotor.write(i);
    delay(5);
  }
  /*
  while(detectado == true)
  {
    Serial.print(angulo);
    iniciarTrigger();
    if(distancia>30)
    {
      detectado = false;
    }
    if(lado == true)
      {
        for (int y = 180; y >= angulo; y--)
        {
          movimientoMotores();
          servomotor.write(y);
          // Hacemos una pausa de 25ms
          delay(5);
        }
        for (int y = angulo; y <= 0; y++)
        {
          movimientoMotores();
          servomotor.write(y);
          // Hacemos una pausa de 25ms
          // Hacemos una pausa de 25ms
        delay(5);
        }
      }
    else
    {
      for (int y = 0; y <= angulo; y++)
      {
        movimientoMotores();
        servomotor.write(y);
        // Hacemos una pausa de 25ms
        // Hacemos una pausa de 25ms
        delay(5);
      }
      for (int y = angulo; y >= angulo; y--)
      {
        movimientoMotores();
        servomotor.write(y);
        // Hacemos una pausa de 25ms
        delay(5);
      }
    }
  }
  */




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


void getColor()
{
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  countRed = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
  digitalWrite(s3, HIGH);
  countBlue = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
  digitalWrite(s2, HIGH);
  countGreen = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
}

void movimientoMotores()
{
  iniciarTrigger();
  if(distancia <= 30)
  {
    getColor();
    Motor1->run(RELEASE);
    Motor2->run(RELEASE);
    Motor3->run(RELEASE);
    Motor4->run(RELEASE);

    Serial.print("Red: ");
    Serial.print(countRed, DEC);
    Serial.print("Green: ");
    Serial.print(countGreen, DEC);
    Serial.print("Blue: ");
    Serial.print(countBlue, DEC);
  
    if (countRed < countBlue && countGreen > 100 && countRed < 80) //derecha
    {
      
      Serial.println(" - Red");
      digitalWrite(6,HIGH);
      while(distancia<=30 && (countRed < countBlue && countGreen > 100 && countRed < 80))
      {
        getColor();  
        iniciarTrigger();  
        Motor1->run(BACKWARD);
        Motor2->run(BACKWARD);
        Motor3->run(FORWARD);
        Motor4->run(FORWARD);

        Serial.print("Red: ");
        Serial.print(countRed, DEC);
        Serial.print("Green: ");
        Serial.print(countGreen, DEC);
        Serial.print("Blue: ");
       Serial.print(countBlue, DEC);

        Serial.println(" - Red");
        digitalWrite(6,HIGH);
            
      }
    }
    else if (countBlue < countRed && countBlue < countGreen)
    {
      Serial.println(" - Blue");
      digitalWrite(5,HIGH);
    }
    else if (countGreen < countRed && countGreen < countBlue) //izquierda
    {
      Serial.println(" - Green");
      digitalWrite(4,HIGH);
    }
    while(distancia<=30 && (countGreen < countRed && countGreen < countBlue))
    {
      getColor();  
      iniciarTrigger();  
      Motor1->run(FORWARD);
      Motor2->run(FORWARD);
      Motor3->run(BACKWARD);
      Motor4->run(BACKWARD);

      Serial.print("Red: ");
      Serial.print(countRed, DEC);
      Serial.print("Green: ");
      Serial.print(countGreen, DEC);
      Serial.print("Blue: ");
      Serial.print(countBlue, DEC);

      Serial.println(" - Green");
      digitalWrite(4,HIGH);
            
    }   
  }
}
