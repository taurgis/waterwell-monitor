#include <EEPROM.h>
#include <TaskScheduler.h>

int diameter = 0;
int depth = 0;
int distance = 0;

void calculateRemainingLiters();

Task measure(2000, TASK_FOREVER, &calculateRemainingLiters);
Scheduler runner;

/**

*/
void setup() {
  EEPROM.begin(25);
  Serial.begin(9600); // Open serial monitor at 115200 baud to see ping results.
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
  initializeServer();
  
  runner.init();
  Serial.println("Initialized scheduler");
  
  runner.addTask(measure);

  measure.enable();

  Serial.println("Water Well Monitor initialized.");
}

/**

*/
void loop() {
  handleRequests();
  runner.execute();
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
