
#include <iostream>
using namespace std;
const int eyeSensorPin = 3;  // Analog pin for eye sensor
const int buzzerPin = 2;      // Buzzer pin
const int vehicleControlPin = 4; // Pin to control vehicle shutdown

const float closedThreshold = 100.0; // Adjust based on your specific eye sensor
const int closedDuration = 3000;     // 3 seconds for initial warning
const int shutdownDuration = 6000;   // 6 seconds before vehicle shutdown

unsigned long eyesClosedStartTime = 0;
bool eyesCurrentlyClosed = false;

void setup() {
  pinMode(eyeSensorPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(vehicleControlPin, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  float sensorValue = analogRead(eyeSensorPin);
  cout<<"sensecr value"<<sensorValue;
  
  if (sensorValue < closedThreshold) {
    // Eyes are closed
    if (!eyesCurrentlyClosed) {
      eyesClosedStartTime = millis();
      eyesCurrentlyClosed = true;
    }
    
    // Check duration of eye closure
    unsigned long currentClosedTime = millis() - eyesClosedStartTime;
    
    if (currentClosedTime >= closedDuration && currentClosedTime < shutdownDuration) {
      // Beep warning after 3 seconds
      tone(buzzerPin, 1000);  // 1kHz tone
    }
    
    if (currentClosedTime >= shutdownDuration) {
      // Shutdown vehicle after 6 seconds
      digitalWrite(vehicleControlPin, HIGH);  // Turn off vehicle
      noTone(buzzerPin);
    }
  } else {
    // Eyes are open
    eyesCurrentlyClosed = false;
    eyesClosedStartTime = 0;
    noTone(buzzerPin);
    digitalWrite(vehicleControlPin, LOW);  // Ensure vehicle remains on
  }
  
  delay(100);  // Small delay to prevent rapid state changes
}