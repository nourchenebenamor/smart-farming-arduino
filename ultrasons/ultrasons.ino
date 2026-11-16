
#define Trigpin 12 
#define Echopin 13 
#define buzzerPin 16
int duration,distance;
const int distanceSeuil = 20; 

void setup(){
  Serial.begin(9600); 
  pinMode(Trigpin,OUTPUT);
  pinMode(buzzerPin,OUTPUT);  
  pinMode(Echopin,INPUT);   
}
void loop(){
  digitalWrite(Trigpin,LOW);
  delayMicroseconds(2);
  digitalWrite(Trigpin,HIGH);
  delayMicroseconds(10);  
  digitalWrite(Trigpin,LOW);
  duration = pulseIn(Echopin,HIGH); 
  distance = duration/58;   
  delay(50);
  Serial.print("distance:");  
  Serial.print(distance);
  Serial.println("cm");

  if (distance > 0 && distance <= distanceSeuil) {
    
    tone(buzzerPin,411);
    delay(100);
    tone(buzzerPin,639);
    delay(100);
    tone(buzzerPin,411);
    delay(100);
    noTone(buzzerPin);  
  } else {
    
    digitalWrite(buzzerPin, LOW);
  }

  delay(200);
}
