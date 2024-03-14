// Define pin connections
#define echoPin D2 // Echo pin for HC-SR04 ultrasonic sensor
#define trigPin D1 // Trigger pin for HC-SR04 ultrasonic sensor
#define BUZZER D0 // Buzzer pin
#define Red_Led D8 // Red LED pin
#define Yellow_Led D7 // Yellow LED pin
#define Green_Led D3 // Green LED pin

int TIME, TIME2; // Variables to store duration of echo pulse
int f1 = 0, f2 = 0, f3 = 0; // Flags for LED status (not used in this code snippet)
int distance, distance2; // Variables to store calculated distance

void setup() {
  // Set pin modes
  pinMode(trigPin, OUTPUT); // Set trigger pin as output
  pinMode(echoPin, INPUT); // Set echo pin as input
  pinMode(BUZZER, OUTPUT); // Set buzzer pin as output
  pinMode(Red_Led, OUTPUT); // Set red LED pin as output
  pinMode(Yellow_Led, OUTPUT); // Set yellow LED pin as output
  pinMode(Green_Led, OUTPUT); // Set green LED pin as output

  // Initialize LEDs as OFF
  digitalWrite(Red_Led, LOW); // Turn off red LED
  digitalWrite(Yellow_Led, LOW); // Turn off yellow LED
  digitalWrite(Green_Led, LOW); // Turn off green LED
  
  Serial.begin(9600); // Start serial communication at 9600 bps
}

void loop() {
  // Trigger ultrasonic pulse
  digitalWrite(trigPin, HIGH); // Set trigger pin high
  delayMicroseconds(10); // Wait for 10 microseconds
  digitalWrite(trigPin, LOW); // Set trigger pin low

  // Measure the duration of echo pulse
  TIME = pulseIn(echoPin, HIGH); // Measure the pulse width on echo pin

  // Calculate distance from duration
  distance = TIME * 0.034 / 2; // Calculate distance in cm
  Serial.print("Distance: "); // Print distance to serial monitor
  Serial.print(distance);
  Serial.println(" cm");

  // Control LEDs and buzzer based on distance
  if (distance != 0) { // Check if distance is not zero
    if (distance < 3) { // If distance is less than 3 cm
      // Activate red LED and buzzer
      digitalWrite(Red_Led, HIGH); // Turn on red LED
      digitalWrite(Yellow_Led, LOW); // Turn off yellow LED
      digitalWrite(Green_Led, LOW); // Turn off green LED
      digitalWrite(BUZZER, HIGH); // Turn on buzzer
      delay(500); // Wait for 500 milliseconds
      digitalWrite(BUZZER, LOW); // Turn off buzzer
    } else if ((distance > 2) && (distance < 5)) { // If distance is between 3 and 5 cm
      // Activate yellow LED
      digitalWrite(Red_Led, LOW); // Turn off red LED
      digitalWrite(Yellow_Led, HIGH); // Turn on yellow LED
      digitalWrite(Green_Led, LOW); // Turn off green LED
    } else if ((distance > 5) && (distance < 20)) { // If distance is between 5 and 20 cm
      // Activate green LED
      digitalWrite(Red_Led, LOW); // Turn off red LED
      digitalWrite(Yellow_Led, LOW); // Turn off yellow LED
      digitalWrite(Green_Led, HIGH); // Turn on green LED
    }
  }
}
