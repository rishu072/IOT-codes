const int flowSensorPin = 2; // Digital pin to which the sensor is connected 
volatile int flowPulseCount = 0; // Variable to count the pulses 
float flowRate = 0.0; // Variable to store the calculated flow rate 
unsigned long startTime; 

void setup() 
{ 
  Serial.begin(9600); 
  pinMode(flowSensorPin, INPUT); 
  attachInterrupt(digitalPinToInterrupt(flowSensorPin), pulseCounter, FALLING); 
  startTime = millis(); // Record the start time 
} 

void loop() 
{ 
  unsigned long currentTime = millis(); 
  unsigned long elapsedTime = currentTime - startTime; 
  // Calculate flow rate every 1 second 
  if (elapsedTime >= 1000) 
  { 
    detachInterrupt(digitalPinToInterrupt(flowSensorPin)); // Disable interrupts while calculating flow //rate 
    // Calculate flow rate (liters per minute) 
    flowRate = (flowPulseCount / 7.5); // Adjust this value based on your sensor's specifications 
    // Reset pulse count 
    flowPulseCount = 0; 
    // Print the flow rate to the Serial Monitor 
    Serial.print("Flow Rate: "); 
    Serial.print(flowRate); 
    Serial.println(" L/min"); 
    attachInterrupt(digitalPinToInterrupt(flowSensorPin), pulseCounter, FALLING); // Re-enable interrupts 
    startTime = currentTime; // Reset the timer 
  }  
} 

// Interrupt Service Routine (ISR) for counting pulses 
void pulseCounter() 
{ 
  flowPulseCount++;
}