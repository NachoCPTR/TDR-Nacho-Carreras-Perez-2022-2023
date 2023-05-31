// Display LCD más pulsador 

#include <LiquidCrystal.h>


LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
void setup()
{
 lcd.begin(16, 2);
 pinMode(6, INPUT);
}
void loop() 
{
 
 if (digitalRead(6)== LOW) 
 {
   lcd.print("jaja");
 }
 else 
 {
 lcd.print("Pulsa el boton ");
 lcd.setCursor(0,1);
 lcd.print("============>");
 }
 }
