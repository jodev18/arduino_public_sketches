//#include<String.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11);

char phone_no[]="PHONE NUMBER";

void setup() {
  
  Serial.begin(115200);
  while (!Serial) {
      ; // wait for serial port to connect. Needed for native USB port only
    }


  Serial.println("Goodnight moon!");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(115200);

  mySerial.println("AT+CMGF=1");

 String reply = mySerial.readString();

  if(reply.length() > 0){
    Serial.println(reply);
  }
  delay(100);

}

void loop()
{

  String data = Serial.readString();

  if(data.length() > 0){
    
    //Serial.println(data);
    
    mySerial.print("AT+CMGS=\"");

    String reply = mySerial.readString();

    if(reply.length() > 0){
      Serial.println(reply);
    }
    
    mySerial.print(phone_no); 
    mySerial.write(0x22);
    mySerial.write(0x0D);  // hex equivalent of Carraige return    
    mySerial.write(0x0A);  // hex equivalent of newline
    delay(2000);
    mySerial.print(data);
    delay(500);
    mySerial.println (char(26));//the ASCII code of the ctrl+z is 26
    
    reply = mySerial.readString();

    if(reply.length() > 0){
      Serial.println(reply);
    }
    delay(3000); //Delay for 3 seconds
  }
}

