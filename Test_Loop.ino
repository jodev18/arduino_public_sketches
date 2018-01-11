void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}
int counter = 0;
void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Test Read Stream");
  Serial.print(counter);
  counter++;
  delay(1000);
}
