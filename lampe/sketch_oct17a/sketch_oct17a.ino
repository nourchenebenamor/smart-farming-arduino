#define LED 27
#define photores 34

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(photores,INPUT);
  pinMode(LED,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int ReadValue = analogRead(photores);
  Serial.print("photores value: ");
  Serial.println(ReadValue);
  if(ReadValue >= 800) {
    digitalWrite(LED,LOW);
    Serial.println("LED OFF");
  }
  else{
    digitalWrite(LED,HIGH);
    Serial.println("LED ON");
  }
  delay(1000);
}
  
