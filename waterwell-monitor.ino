
void setup() {
  Serial.begin(9600); // Open serial monitor at 115200 baud to see ping results.
  Serial.println("Initializing Water Well Monitor...");

  initDistanceSensor();
  initializeServer();

  Serial.println("Water Well Monitor initialized.");
}

void loop() {
  handleRequests();
  // Serial.print(calculateDistance());
  // Serial.println("cm ");
}
