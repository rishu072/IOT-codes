#define DHTPIN 9  // Pin connected to the DATA pin of the DHT11 sensor

// Variables to store temperature and humidity
int humidity = 0;
int temperature = 0;

// Function to initialize communication with DHT11
void startSignal() {
  pinMode(DHTPIN, OUTPUT);
  digitalWrite(DHTPIN, LOW);
  delay(18);  // Keep the signal low for at least 18ms
  digitalWrite(DHTPIN, HIGH);
  delayMicroseconds(20);  // Pull the signal high for 20-40µs
  pinMode(DHTPIN, INPUT);
}

// Function to wait for a response from DHT11
bool checkResponse() {
  unsigned long count = 0;

  // Wait for the sensor to pull the line LOW
  while (digitalRead(DHTPIN)) {
    if (++count > 1000) return false;  // Timeout
  }

  count = 0;
  // Wait for the sensor to pull the line HIGH
  while (!digitalRead(DHTPIN)) {
    if (++count > 1000) return false;  // Timeout
  }

  count = 0;
  // Wait for the sensor to pull the line LOW again
  while (digitalRead(DHTPIN)) {
    if (++count > 1000) return false;  // Timeout
  }

  return true;
}

// Function to read 40 bits of data from DHT11
uint8_t readByte() {
  uint8_t result = 0;

  for (int i = 0; i < 8; i++) {
    // Wait for the signal to go HIGH
    while (!digitalRead(DHTPIN));

    delayMicroseconds(30);  // Wait for 30µs to determine the bit value

    // Read the bit value
    if (digitalRead(DHTPIN)) {
      result |= (1 << (7 - i));  // Set the corresponding bit
    }

    // Wait for the signal to go LOW
    while (digitalRead(DHTPIN));
  }

  return result;
}

void setup() {
  Serial.begin(9600);
  Serial.println("DHT11 Temperature and Humidity Sensor");
}

void loop() {
  // Start communication
  startSignal();

  // Check response from the sensor
  if (!checkResponse()) {
    Serial.println("DHT11 Sensor not responding");
    delay(2000);
    return;
  }

  // Read 5 bytes of data from the sensor
  uint8_t data[5] = {0};
  for (int i = 0; i < 5; i++) {
    data[i] = readByte();
  }

  // Verify checksum
  if (data[4] != (data[0] + data[1] + data[2] + data[3])) {
    Serial.println("Checksum error");
    delay(2000);
    return;
  }

  // Extract humidity and temperature
  humidity = data[0];
  temperature = data[2];

  // Print the values
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  delay(2000); 
  } // Wait 2 seconds before the next reading