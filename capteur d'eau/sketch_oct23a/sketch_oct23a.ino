#include <LiquidCrystal_I2C.h>

#define BuzzerPin 16
#define SoilHumidityPin 32
#define WaterLevelPin 33
#define RelayPin 25
#define ButtonPin 5 
int value = 0;      

LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  Serial.begin(9600);
  pinMode(BuzzerPin,OUTPUT);
  pinMode(SoilHumidityPin,INPUT);
  pinMode(WaterLevelPin,INPUT);
  pinMode(RelayPin, OUTPUT);
  
  

  lcd.init();
  lcd.backlight();  
  lcd.clear();

}

void loop() {
  int shvalue = analogRead(SoilHumidityPin);
  int wlvalue = analogRead(WaterLevelPin);
 Serial.println(shvalue);
 Serial.println(wlvalue); 
  lcd.setCursor(0, 0);
  lcd.print("SoilHum:");
  lcd.setCursor(9, 0);
  lcd.print(shvalue);
  lcd.setCursor(0, 1);
  lcd.print("Watlvl:");
  lcd.setCursor(9, 1);
  lcd.print(wlvalue);

   if(500 >= wlvalue && value == 0)
  {
    tone(BuzzerPin,411);
    delay(100);
    tone(BuzzerPin,639);
    delay(100);
    tone(BuzzerPin,411);
    delay(100);
    noTone(BuzzerPin);  
  }
   
   if(shvalue <= 500 && wlvalue >= 1000) {
    digitalWrite(RelayPin,HIGH);
    delay(400);
    digitalWrite(RelayPin,LOW);
    delay(700);
  }
  delay(500);
  lcd.clear();
}
