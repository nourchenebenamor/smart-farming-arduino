#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 17       // Broche où le capteur est connecté
#define DHTTYPE DHT11   // Type de capteur (DHT11, DHT22, etc.)

#define MotorPin1 19    // Broche pour IN+ du moteur
#define MotorPin2 18    // Broche pour IN- du moteur
#define SolarVoltagePin 32 // Broche analogique pour lire la tension des panneaux solaires

DHT dht(DHTPIN, DHTTYPE);

const int TempThreshold = 29;      // Température seuil en °C
const float VoltageThreshold = 5.0; // Tension seuil en volts

void setup() {
  pinMode(MotorPin1, OUTPUT);
  pinMode(MotorPin2, OUTPUT);

  // Configurer PWM pour le contrôle du moteur
  ledcSetup(1, 1200, 8); // Canal 1 : fréquence 1200 Hz, résolution 8 bits
  ledcAttachPin(MotorPin1, 1); // Associer le canal 1 à la broche GPIO19
  ledcSetup(3, 1200, 8); // Canal 3 : fréquence 1200 Hz, résolution 8 bits
  ledcAttachPin(MotorPin2, 3); // Associer le canal 3 à la broche GPIO18

  Serial.begin(9600);
  dht.begin(); // Initialiser le capteur DHT
}

void loop() {
  // Lire les données du capteur DHT11
  float Temperature = dht.readTemperature();
  float Humidity = dht.readHumidity();

  // Vérifier si les lectures sont valides
  if (isnan(Temperature) || isnan(Humidity)) {
    Serial.println("Erreur de lecture du capteur DHT!");
    delay(1000);
    return; // Sortir pour éviter d'utiliser des données incorrectes
  }

  // Lire la tension des panneaux solaires
  int solarRaw = analogRead(SolarVoltagePin);
  float solarVoltage = solarRaw * (3.3 / 1023.0) * 2; // Diviseur de tension 1:2

  // Afficher les informations dans le moniteur série
  Serial.print("Temperature: ");
  Serial.print(Temperature);
  Serial.print(" °C, Humidity: ");
  Serial.print(Humidity);
  Serial.print(" %, Solar Voltage: ");
  Serial.print(solarVoltage);
  Serial.println(" V");

  // Condition pour allumer le ventilateur
  if (Temperature >= TempThreshold && solarVoltage >= VoltageThreshold) {
    // Activer le moteur
    ledcWrite(1, 100); // Duty cycle 100 (moteur tourne)
    ledcWrite(3, 0);
  } else {
    // Désactiver le moteur
    ledcWrite(1, 0); // Duty cycle 0 (moteur arrêté)
    ledcWrite(3, 0);
  }

  delay(1000); // Attente d'1 seconde avant la prochaine lecture
}
