

// Blynk configuration for the project
#define BLYNK_TEMPLATE_ID "TMPL6M9_frUE1"    // Unique ID for your Blynk template
#define BLYNK_TEMPLATE_NAME "my university project" // Human-readable name for the template
#define BLYNK_AUTH_TOKEN "jYvuo7KSrkP04a1ZX8xAmW-VH76iUYda" // Authentication token to link your hardware to Blynk

// Include necessary libraries
#include <Wire.h>               // Library for I2C communication (optional for future expansion)
#include <WiFi.h>               // Library for ESP32 to connect to WiFi
#include <WiFiClient.h>         // Library for ESP32 to act as a WiFi client
#include <BlynkSimpleEsp32.h>   // Blynk library for ESP32 to communicate with Blynk servers

// Pin Definitions
#define echopin 18          // Ultrasonic sensor echo pin
#define trigpin 5           // Ultrasonic sensor trigger pin
#define relaypin1 4         // Relay controlling the motor
#define relaypin2 23        // Relay for water leak management
#define waterleak 14        // Water leak sensor pin
#define relaypin3 26        // Relay for the water pump
#define moisture 34         // Moisture sensor pin (analog input)
#define rainSensor 25       // Rain sensor pin
#define relaypin4 19        // Relay for rainwater storage

// Blynk Virtual Pins
#define V0 V0               // Virtual pin for water leak notification
#define V1 V1               // Virtual pin to control relaypin1 manually
#define V2 V2               // Virtual pin to control relaypin3 manually (water pump)
#define tanklevel V3        // Virtual pin to send tank level status to Blynk

// WiFi Credentials
char ssid[] = "john";      // WiFi SSID (Network name)
char pass[] = "123456";      // WiFi password

// Global Variables
long duration, distance;        // Variables for ultrasonic sensor
int moistureValue;              // Variable to store raw moisture sensor value
int rainStatus;                 // Variable to store rain sensor status
int MaxLevel = 10;              // Maximum water level in cm

void setup() {
  Serial.begin(9600);           // Initialize Serial Communication
  
  // Connect to Blynk server
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  
  // Configure all pins
  setupPins();
}

void loop() {
  Blynk.run();                  // Handle communication with Blynk
  checkSensors();               // Check all sensor readings and take actions
  delay(1000);                  // Delay for stability
}

// Function to setup pin configurations
void setupPins() {
  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);

  pinMode(relaypin1, OUTPUT);
  pinMode(relaypin2, OUTPUT);
  pinMode(relaypin3, OUTPUT);
  pinMode(relaypin4, OUTPUT);

  digitalWrite(relaypin1, LOW); // Ensure all relays are initially off
  digitalWrite(relaypin2, LOW);
  digitalWrite(relaypin3, LOW);
  digitalWrite(relaypin4, LOW);

  pinMode(waterleak, INPUT);    // Configure water leak sensor as input
  pinMode(moisture, INPUT);     // Configure moisture sensor as input
  pinMode(rainSensor, INPUT);   // Configure rain sensor as input
}

// Function to check all sensors and take appropriate actions
void checkSensors() {
  checkTankLevel();   // Check water tank level using ultrasonic sensor
  handleRainSensor(); // Handle rain sensor logic
  handleLeakSensor(); // Handle water leak detection
  handleMoisture();   // Handle soil moisture and water pump
}

// Function to check tank level and update Blynk
void checkTankLevel() {
  // Measure distance using ultrasonic sensor
  digitalWrite(trigpin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin, LOW);

  long t = pulseIn(echopin, HIGH); // Measure the pulse duration
  distance = t / 29 / 2;           // Convert duration to distance (cm)

  // Send water tank level to Blynk
  int blynkDistance = (distance - MaxLevel) * -1;
  if (distance <= MaxLevel) {
    Blynk.virtualWrite(tanklevel, blynkDistance);
  } else {
    Blynk.virtualWrite(tanklevel, 0);
  }
}

// Function to handle rain sensor logic
void handleRainSensor() {
  rainStatus = digitalRead(rainSensor); // Read rain sensor status

  if (rainStatus == HIGH) { // If no rain detected
    digitalWrite(relaypin4, HIGH); // Turn off rainwater storage
  } else { // If rain detected
    digitalWrite(relaypin4, LOW); // Activate rainwater storage
    if (distance > 3) { // Check if tank has space
      digitalWrite(relaypin4, HIGH);
    } else {
      digitalWrite(relaypin4, LOW); // Turn off storage if tank is full
    }
  }
  delay(500); // Stabilize relay operations
}

// Function to handle water leak detection
void handleLeakSensor() {
  int leakDetected = digitalRead(waterleak); // Read water leak sensor

  if (leakDetected == LOW) { // If leak detected
    digitalWrite(relaypin2, HIGH); // Redirect water to backup
    Blynk.logEvent("leak_detected", "Leak detected! Turning off main pump.");
  } else { // If no leak detected
    digitalWrite(relaypin2, LOW);
    delay(40000); // Delay for pump stabilization
    digitalWrite(relaypin2, HIGH); // Restart pump after delay
  }
  delay(1000); // Stabilize sensor readings
}

// Function to handle soil moisture and water pump
void handleMoisture() {
  moistureValue = digitalRead(moisture); // Read moisture sensor value

  if (moistureValue >= 1) { // If soil is moist
    Serial.println("Soil moisture is adequate, turning off water pump.");
    digitalWrite(relaypin3, LOW); // Turn off pump
  } else { // If soil is dry
    Serial.println("Soil is dry, turning on water pump.");
    digitalWrite(relaypin3, HIGH); // Turn on pump
  }
}

// Function to control relaypin1 manually through Blynk
BLYNK_WRITE(V1) {
  int pinValue = param.asInt(); // Read value from Blynk
  digitalWrite(relaypin1, pinValue); // Control relaypin1
  Serial.print("Relaypin1 manually set to: ");
  Serial.println(pinValue);
}

