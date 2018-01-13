//define pins
#define trigPin 13
#define echoPin 12
#define led 11
#define led2 10
#define led3 9
#define leda 5
#define leda2 4
#define leda3 3
#define echoPin2 6
#define trigPin2 7


void setup() {
  //setup connection of input and output pins (echo is for inputs only) NOTE: VCC IS + AND GND IS -
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
    pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
    pinMode(leda, OUTPUT);
  pinMode(leda2, OUTPUT);
  pinMode(leda3, OUTPUT);


}

//code for first sensor - multiple support loop function

void firstSensor(){
  long duration1, distance1;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration1 = pulseIn(echoPin, HIGH);
  distance1 = (duration1/2) / 29.1;

if(distance1 < 15  || distance1==0){
  digitalWrite(led,HIGH);
  digitalWrite(led2,LOW);
  digitalWrite(led3,LOW);
}

if(distance1 > 16 && distance1 < 25){
  digitalWrite(led,LOW);
  digitalWrite(led2,HIGH);
  digitalWrite(led3,LOW);
}
if (distance1 > 26){
  digitalWrite(led,LOW);
  digitalWrite(led2,LOW);
  digitalWrite(led3,HIGH);
}
  
}

void secondSensor(){
  long duration2, distance2;
  digitalWrite(trigPin2, LOW);  // Added this line
  delayMicroseconds(20); // Added this line
  digitalWrite(trigPin2, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
  distance2 = (duration2/2) / 29.1;

if(distance2 < 15  || distance2==0){
  digitalWrite(leda,HIGH);
  digitalWrite(leda2,LOW);
  digitalWrite(leda3,LOW);
}

if(distance2 > 16 && distance2 < 25){
  digitalWrite(leda,LOW);
  digitalWrite(leda2,HIGH);
  digitalWrite(leda3,LOW);
}
if (distance2 > 26){
  digitalWrite(leda,LOW);
  digitalWrite(leda2,LOW);
  digitalWrite(leda3,HIGH);
}
  
}
void loop(){
  Serial.println("\n");
  firstSensor();
  Serial.println("\n");
  secondSensor();
}

