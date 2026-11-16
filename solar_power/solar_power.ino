#include <dummy.h>


#include <Adafruit_INA219.h>

#include <Wire.h>
#include <Adafruit_INA219.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

#define DHTPIN 17  // Pin pour le DHT11
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);  // Initialise le capteur DHT11
Adafruit_INA219 ina219;    // Initialise le capteur INA219

void setup() {
  Serial.begin(115200);
  
  // Initialisation INA219
  if (!ina219.begin()) {
    Serial.println("Échec de la détection du capteur INA219");
    while (1) { delay(10); }
  }
  Serial.println("INA219 Solar Power System Monitoring");

  // Initialisation DHT11
  dht.begin();
  Serial.println("DHT11 initialisé.");
  pinMode(2, OUTPUT);
}

void loop() {
  // Lecture des données INA219
  float busVoltage = ina219.getBusVoltage_V();
  float current_mA = ina219.getCurrent_mA();
  float power_mW = busVoltage * (current_mA / 1000);

  Serial.print("Tension du bus : "); Serial.print(busVoltage); Serial.println(" V");
  Serial.print("Courant : "); Serial.print(current_mA); Serial.println(" mA");
  Serial.print("Puissance : "); Serial.print(power_mW); Serial.println(" mW");
  Serial.println("-----------------------------");

  // Lecture des données DHT11
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature(); // Par défaut en °C

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Erreur de lecture du capteur DHT11");
  } else {
    Serial.print("Humidité : "); Serial.print(humidity); Serial.println(" %");
    Serial.print("Température (°C) : "); Serial.print(temperature); Serial.println(" °C");
    Serial.print("Température (°F) : "); Serial.print(Fahrenheit(temperature)); Serial.println(" °F");
    Serial.print("Température (K) : "); Serial.print(Kelvin(temperature)); Serial.println(" K");
    Serial.print("Point de rosée (°C) : "); Serial.println(dewPoint(temperature, humidity));
    Serial.print("Point de rosée rapide (°C) : "); Serial.println(dewPointFast(temperature, humidity));
  }

  delay(2000); // Attente de 2 secondes
}

// Fonctions auxiliaires
double Fahrenheit(double celsius) {
  return 1.8 * celsius + 32;
}

double Kelvin(double celsius) {
  return celsius + 273.15;
}

double dewPoint(double celsius, double humidity) {
  double A0 = 373.15 / (273.15 + celsius);
  double SUM = -7.90298 * (A0 - 1);
  SUM += 5.02808 * log10(A0);
  SUM += -1.3816e-7 * (pow(10, (11.344 * (1 - 1 / A0))) - 1);
  SUM += 8.1328e-3 * (pow(10, (-3.49149 * (A0 - 1))) - 1);
  SUM += log10(1013.246);
  double VP = pow(10, SUM - 3) * humidity;
  double T = log(VP / 0.61078);
  return (241.88 * T) / (17.558 - T);
}

double dewPointFast(double celsius, double humidity) {
  double a = 17.271;
  double b = 237.7;
  double temp = (a * celsius) / (b + celsius) + log(humidity / 100);
  double Td = (b * temp) / (a - temp);
  return Td;
  digitalWrite(2, HIGH);
  delay(1000);
  digitalWrite(2, LOW);
  delay(1000);
}
