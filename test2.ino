#include <AFMotor.h>
#include <SoftwareSerial.h>

AF_DCMotor three_motor(3, MOTOR12_8KHZ);
AF_DCMotor left_motor(2, MOTOR12_8KHZ);
AF_DCMotor right_motor(1, MOTOR12_8KHZ);

SoftwareSerial mySerial(11,12);

void setup() {
  
  Serial.begin(9600);
  mySerial.begin(9600);
  // put your setup code here, to run once:
    three_motor.setSpeed(255);
    left_motor.setSpeed(255);
    right_motor.setSpeed(255);
    

}

void loop() {
  // put your main code here, to run repeatedly:
  three_motor.run (FORWARD);
  left_motor.run (FORWARD);
  right_motor.run (FORWARD);
  if (mySerial.available()){
    char serialCommand = mySerial.read();
  }


}
