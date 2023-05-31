//LED
int Led=7;
int numero=1;
void setup() 
{
pinMode(Led, OUTPUT);
Serial.begin(9600);
}

void loop() 
{
  funcion();
}
void funcion()
{
  digitalWrite(Led,HIGH);
   Serial.write("Ahora Ta Encendido");Serial.println("");
  delay(1000);
  digitalWrite(Led,LOW);
  Serial.write("Ahora Ta Apagao"); Serial.println("");
  delay(1000);
}
