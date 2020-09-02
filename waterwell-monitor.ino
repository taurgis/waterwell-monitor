#include <EEPROM.h>

#define SLEEP_INTERVAL_DURATION  10800e6

int diameter = 0;
int depth = 0;
int distance = 0;

/**

*/
void setup() {
  EEPROM.begin(25);
  Serial.begin(9600);
  Serial.println("Initializing Water Well Monitor...");
  pinMode(13, OUTPUT); 
  digitalWrite(13, HIGH);
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
  initializeServer();

  Serial.println("Water Well Monitor initialized.");

  calculateRemainingLiters();
  
  digitalWrite(13, LOW);
  Serial.println("[INFO] Going to sleep for 3 hours...");
  ESP.deepSleep(SLEEP_INTERVAL_DURATION, WAKE_RF_DEFAULT); 
}

String uint64ToString(uint64_t input) {
  String result = "";
  uint8_t base = 10;

  do {
    char c = input % base;
    input /= base;

    if (c < 10)
      c +='0';
    else
      c += 'A' - 10;
    result = c + result;
  } while (input);
  return result;
}

/**

*/
void loop() {

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

  addRowToSheet(currentLiters);
}
