#define TRIG_PIN 6
#define ECHO_PIN 5

void setup() {
  Serial.begin(9600);  // Start serial communication at 9600 baud rate
  pinMode(TRIG_PIN, OUTPUT);  // Set the trigger pin as an output
  pinMode(ECHO_PIN, INPUT);   // Set the echo pin as an input
}

void loop() {
  // Send a 10-microsecond pulse to trigger the sensor
  digitalWrite(TRIG_PIN, LOW);  
  delayMicroseconds(2);  // Wait for 2ms
  digitalWrite(TRIG_PIN, HIGH);  
  delayMicroseconds(10);  // Send a 10ms pulse to trigger the sensor
  digitalWrite(TRIG_PIN, LOW);  

  // Measure the time the pulse takes to return to the echo pin
  long duration = pulseIn(ECHO_PIN, HIGH);  // Measure the pulse width in microseconds

  // Calculate the distance (duration in microseconds to cm)
  // Speed of sound is 343m/s (0.0343 cm/µs), so divide the duration by 2 (round trip) and multiply by speed of sound.
  long distance = (duration / 2) * 0.0343;

  // Print the distance to the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println("inch");

  delay(500);  // Wait for 500ms before the next reading
}