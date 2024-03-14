#include "DHT.h"  // Include the DHT sensor library
// Define pin numbers and sensor type
#define DHTPIN 3   // Pin connected to the DHT sensor
#define LED 6      // Pin connected to the LED
#define fan 4      // Pin connected to the fan
#define DHTTYPE DHT11  // Type of DHT sensor used
DHT dht(DHTPIN, DHTTYPE); // creating DHT Objects
float hum, tempp;  // Declare variables to store humidity and temperature 
void setup() {
  Serial.begin(9600); // Start serial communication at 9600 baud rate
  Serial.print("Connecting to ");
  pinMode(fan, OUTPUT); // Set fan pin as an output
  pinMode(LED, OUTPUT); // Set LED pin as an output
  digitalWrite(fan, HIGH); // Turn on the fan initially
  dht.begin(); // Initialize the DHT sensor
}
void loop() {
  // Read temperature and humidity from the DHT sensor
  tempp = dht.readTemperature(); 
  hum = dht.readHumidity();
  // Print temperature and humidity readings to the serial monitor
  Serial.print("temp: ");
  Serial.println(tempp);
  Serial.print("hum: ");
  Serial.println(hum);
  // Control the fan based on temperature and humidity thresholds
  if ((tempp >= 27) || (hum > 45)) {
    digitalWrite(fan, LOW); // Turn off the fan if temperature is high or humidity is above threshold
  } else {
    digitalWrite(fan, HIGH); // Otherwise, keep the fan on
  }
  // Control the LED based on temperature threshold
  if (tempp <= 25) {
    digitalWrite(LED, HIGH); // Turn on the LED if temperature is low
  } else {
    digitalWrite(LED, LOW); // Otherwise, turn off the LED
  }
}
