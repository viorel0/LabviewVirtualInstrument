#include <DHT.h>

#define PPM_PIN 33       // Pin connected to MQ-135
#define DHTPIN 4         // Pin connected to DHT11
#define DHTTYPE DHT11    // DHT 11 sensor

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  analogReadResolution(12);
  dht.begin();
}
void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  float RL = 9.89; // 9.89 kohm
  float R0= 4.98;
  int analogValue = analogRead(PPM_PIN);
  float Vout = analogValue * (3.3 / 4095.0);
  float Rs = ((3.3 - Vout) * RL) / Vout;
  // float R0 = Rs / 3.6;

  float ratio = Rs / R0;

  //https://davidegironi.blogspot.com/2014/01/cheap-co2-meter-using-mq135-sensor-with.html
  float ppm = 116.6020682 * pow(ratio, -2.769034857);
  
 
 
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Eroare citire DHT11!");
  } else {

    Serial.print(ppm);
    Serial.print(",");
    Serial.print(temperature);
    Serial.print(",");
    Serial.println(humidity);
  }

  delay(500);
}

