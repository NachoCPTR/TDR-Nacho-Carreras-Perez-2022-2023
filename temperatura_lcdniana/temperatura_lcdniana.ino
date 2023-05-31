#include <LiquidCrystal.h>
#include <DHT.h>
#define DHTPIN 7
#define DHTTYPE DHT11
 
// Inicializamos el sensor DHT11
DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal lcd (12, 11, 5, 4, 3, 2);

void setup()
{
  lcd.begin(16, 2); //inicio lcd
  Serial.begin(9600);// consola no funcional
  dht.begin();
}
void loop() 
{
    delay(5000);
 
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    float f = dht.readTemperature(true);
 
    if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Error obteniendo los datos del sensor DHT11");
    return;
  }
  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);
 
  Serial.print("Humedad: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.print("Índice de calor: ");
  Serial.print(hic);
  Serial.print(" *C ");
  Serial.print(hif);
  Serial.println(" *F");
  lcd.begin(16,1);
  lcd.setCursor(0,0);
  lcd.print("temperatura"); //algo inutil
  lcd.setCursor(0,1);
  lcd.print(t); //temperatura variable
  lcd.display();   
  }
