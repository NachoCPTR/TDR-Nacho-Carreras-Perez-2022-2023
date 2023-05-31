#include <Servo.h>
#include <LiquidCrystal.h>

#define COLS 16 
#define ROWS 2 

const int PinTrig = 2;
const int PinEcho = 3;
Servo servomotor;
LiquidCrystal lcd(0, 0, 0, 0, 0, 0);

 
// Constante velocidad sonido en cm/s
const float VelSon = 34000.0;
 
float distancia;

void setup()
{
  Serial.begin(9600);
  pinMode(PinTrig, OUTPUT);
  pinMode(PinEcho, INPUT);
  servomotor.attach(6);//assignacion del servomotor al pin 5
  servomotor.write(0);//giro del servo colocado a 0º
  lcd.begin(COLS, ROWS);
  lcd.setCursor(0,0);
  lcd.clear();
}
void loop()
{
  iniciarTrigger();
  // La función pulseIn obtiene el tiempo que tarda en cambiar entre estados, en este caso a HIGH
  //unsigned long tiempo = pulseIn(PinEcho, HIGH);
  
  // Obtenemos la distancia en cm, hay que convertir el tiempo en segudos ya que está en microsegundos
  // por eso se multiplica por 0.000001
  //distancia = tiempo * 0.000001 * VelSon / 2.0;

  while(distancia<= 30)
  {
    servomotor.write(180);
    iniciarTrigger();
    if(distancia>30)
      {
        break;
      } 
    servomotor.write(-180);
    iniciarTrigger(); 
    if(distancia>30)
      {
        
        break;
      }       
        
  }

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
  lcd.print(distancia);
  lcd.print("cm");
  delay(750);
  lcd.clear();
}