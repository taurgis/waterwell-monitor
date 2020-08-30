#include <EEPROM.h>

int diameter = 0;
int depth = 0;
int distance = 0;

/**

*/
void setup() {
  EEPROM.begin(25);
  Serial.begin(9600);
  Serial.println("Initializing Water Well Monitor...");

  diameter = EEPROM.read(1);
  depth = EEPROM.read(2);
  distance = EEPROM.read(3);

  Serial.println("");
  Serial.println("Loading data:");
  Serial.println(diameter);
  Serial.println(depth);
  Serial.println(distance);
  Serial.println("");

  initDistanceSensor();
  // initializeServer();

  Serial.println("Water Well Monitor initialized.");
}

/**

*/
void loop() {
  calculateRemainingLiters();
  delay(2000);
}

void calculateRemainingLiters() {
  int distanceMeasured = calculateDistance();
  int maxLiters = (PI * pow(diameter, 2) * depth)  / 1000;
  int currentLiters = (PI * pow(diameter, 2) * ((depth + distance) - distanceMeasured)) / 1000;
  
  Serial.println("");
  Serial.print("Measured ");
  Serial.print(distanceMeasured);
  Serial.print(" cm. The well has a volume of ");
  Serial.print(maxLiters);
  Serial.print(" liters and now has ");
  Serial.print(currentLiters);
  Serial.print(" liters left");
  Serial.println("");
}
