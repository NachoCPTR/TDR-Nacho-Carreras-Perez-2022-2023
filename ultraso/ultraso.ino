#include <Ultrasonic.h>

#include <EasyUltrasonic.h>

const int PinTrig = 2;
const int PinEcho = 3;
 
// Constante velocidad sonido en cm/s
const float VelSon = 34320.0;
 
float distancia;
 
void setup()
{
  Serial.begin(9600);
  pinMode(PinTrig, OUTPUT);//disparador
  pinMode(PinEcho, INPUT);//receptor
}  
void loop()
{
  iniciardisparador();
  
    unsigned long tiempo = pulseIn(PinEcho, HIGH);
  
    distancia = tiempo * 0.000001 * VelSon / 2.0;
  Serial.print(distancia);
  Serial.print("cm");
  Serial.println();
  delay(1000);
  
}
 
void iniciardisparador()
{
  digitalWrite(PinTrig, LOW);
  delayMicroseconds(2);
  
  digitalWrite(PinTrig, HIGH);
  delayMicroseconds(10);
  
  digitalWrite(PinTrig, LOW);
}
