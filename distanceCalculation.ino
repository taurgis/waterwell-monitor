const int trigPin = 14;
const int echoPin = 12;

long duration;
int distanceCm;

/**
 * Initializes the pins for the range sensor.
 */
void initDistanceSensor() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

/**
 * Calculates the distance to the target in CM.
 * 
 * @returns {int} - The distance in CM.
 */
int calculateDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distanceCm = duration * 0.036 / 2;

  return distanceCm;
}
