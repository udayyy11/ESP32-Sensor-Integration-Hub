// Define the GPIO pins we are using
#define IR_SENSOR_PIN 22
#define LED_PIN       2   // Changed to D2 (GPIO 2)

void setup() {
  // Initialize Serial Monitor for debugging
  Serial.begin(115200);
  
  // Set the pin modes
  pinMode(IR_SENSOR_PIN, INPUT); // IR sensor pin is an input
  pinMode(LED_PIN, OUTPUT);      // LED pin is an output
  
  // Ensure the LED is off at the start
  digitalWrite(LED_PIN, LOW);
}

void loop() {
  // Read the state of the IR sensor
  int sensorState = digitalRead(IR_SENSOR_PIN);

  // Most IR modules output LOW when an obstacle is detected
  if (sensorState == LOW) {
    // Obstacle detected!
    Serial.println("Obstacle Detected ---> LED ON");
    digitalWrite(LED_PIN, HIGH); // Turn the LED on
  } else {
    // No obstacle
    Serial.println("No Obstacle Detected ---> LED OFF");
    digitalWrite(LED_PIN, LOW); // Turn the LED off
  }

  // Add a small delay to avoid spamming the serial monitor
  delay(100); 
}