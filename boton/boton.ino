const int boton=6;
const int led=7;
int val;

void setup() 
{
  pinMode(led,OUTPUT);
  pinMode(boton, INPUT);
}

void loop()
{
  val=digitalRead(boton);
  if(val==LOW)
  {
    digitalWrite(led, LOW);  
  }
  else
  {
   digitalWrite(led,HIGH); 
  }
}
