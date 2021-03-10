

#include <Adafruit_Fingerprint.h>

// On Leonardo/Micro or others with hardware serial, use those! #0 is green wire, #1 is white
// uncomment this line:
// #define mySerial Serial1

// For UNO and others without hardware serial, we must use software serial...
// pin #2 is IN from sensor (GREEN wire)
// pin #3 is OUT from arduino  (WHITE wire)
// comment these two lines if using hardware serial
SoftwareSerial mySerial(2,3);

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

void setup()  
{
  Serial.begin(9600);
  while (!Serial);  // For Yun/Leo/Micro/Zero/...
  delay(100);
  Serial.println("S1;");

  // set the data rate for the sensor serial port
  finger.begin(57600);
  delay(5);
  if (finger.verifyPassword()) {
    Serial.println("SD1;");
  } else {
    Serial.println("SE1;");
    while (1) { delay(1); }
  }

  finger.getTemplateCount();
  Serial.print("ST:"); Serial.print(finger.templateCount); Serial.println(";");
  Serial.println("SW;");
}

void loop()                     // run over and over again
{
  getFingerprintIDez();
  delay(50);            //don't ned to run this at full speed.
}

uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No finger detected");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK success!

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("FP1;");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("FP2;");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("FP3;");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("FP4;");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("FP5;");
      return p;
    default:
      Serial.println("WTF;");
      return p;
  }
  
  // OK converted!
  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("FM1;");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("WTF2;");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("WTF3;");
    return p;
  } else {
    Serial.println("WTF");
    return p;
  }   
  
  // found a match!
  Serial.print("F:"); Serial.print(finger.fingerID); 
  Serial.print(":"); Serial.print(finger.confidence);
  Serial.println(";");

  return finger.fingerID;
}

// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;
  
  // found a match!
  Serial.print("F:"); Serial.print(finger.fingerID); 
  Serial.print(":"); Serial.print(finger.confidence);
  Serial.println(";");
  return finger.fingerID; 
}
