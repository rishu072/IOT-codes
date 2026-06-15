#define rainSensor 7  // Digital pin for rain sensor (D0)
#define buzzer 8      // Buzzer on pin 8

void setup() {
    pinMode(rainSensor, INPUT);  // Sensor as input
    pinMode(buzzer, OUTPUT);     // Buzzer as output
    Serial.begin(9600);
}

void loop() {
    int rainStatus = digitalRead(rainSensor); // Read sensor state

    if (rainStatus == LOW) {  // If rain is detected (D0 goes LOW)
        digitalWrite(buzzer, HIGH);
        Serial.println("Rain Detected!");
    } else {
        digitalWrite(buzzer, LOW);
        Serial.println("No Rain.");
    }
    
    delay(1000); // Wait 1 second before next reading
}