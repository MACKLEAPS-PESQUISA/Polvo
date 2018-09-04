const int trigPin = 12;
const int echoPin = 13;
int LED = 5;

void setup()
{
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(LED,OUTPUT);
}

void loop()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  unsigned long duracao = pulseIn(echoPin, HIGH);
  int distancia = duracao / 58;
  Serial.print("Distancia em CM: ");
  Serial.println(distancia);
  
  if(distancia < 10)
  {
    digitalWrite(LED,HIGH);
  }
  else
  {
    digitalWrite(LED,LOW);
  }
  delay(1000);
}
