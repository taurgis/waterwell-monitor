const int trigPin = 2;
const int echoPin = 0;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600); // Open serial monitor at 115200 baud to see ping results.
  Serial.print("test");
}
void loop() {
 
  Serial.print(calculateDistance());
  Serial.println("cm ");
  delay(10000);
}
