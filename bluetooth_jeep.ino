#include <SoftwareSerial.h>
#include <AFMotor.h>
AF_DCMotor three_motor(3, MOTOR12_8KHZ);
AF_DCMotor left_motor(2, MOTOR12_8KHZ);
AF_DCMotor right_motor(1, MOTOR12_8KHZ);

SoftwareSerial mySerial(11,12);

int STAT = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  mySerial.begin(9600);

  three_motor.setSpeed(255);
  left_motor.setSpeed(255);
  right_motor.setSpeed(255);
}

void loop() {

 if(mySerial.available()){
  char statusd = mySerial.read();
  if(statusd == 'a'){
    STAT = 1; 
  }
  if(statusd == 'b'){
    STAT = 2;
  }
  if(statusd == 's'){
    STAT = 3;
  }
  if(statusd == 'r'){
    STAT = 4;
  }
  if(statusd == 'l'){
    STAT = 5;
  }
  if(statusd == 'p'){
    STAT = 6;
  }
  if(statusd == 'd'){
    STAT = 7;
  }
 }
 
 if(STAT == 1){
    left_motor.run (FORWARD);
    right_motor.run (FORWARD);
 }
 if(STAT == 2){
    left_motor.run (BACKWARD);
    right_motor.run (BACKWARD);
 }
 if(STAT == 3){
    left_motor.run (RELEASE);
    right_motor.run (RELEASE);
 }
 if(STAT == 4){
    left_motor.run (BACKWARD);
    right_motor.run (FORWARD);
 }
 if(STAT == 5){
    left_motor.run (FORWARD);
    right_motor.run (BACKWARD);
 }
 if(STAT == 6){
  three_motor.run(FORWARD);
 }
 if(STAT == 7){
  three_motor.run(RELEASE);
 }

  Serial.println(STAT);
 delay(300);
}
