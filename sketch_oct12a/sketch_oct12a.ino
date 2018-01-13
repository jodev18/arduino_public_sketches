//Sample using LiquidCrystal library
#include <LiquidCrystal.h>
#include <Stepper.h>
#include <dht.h>

/*******************************************************

This program will test the LCD panel and the buttons
Mark Bramwell, July 2010

********************************************************/

const char* title = "URBAN PLANT";
dht DHT;

#define STEPS 200
Stepper stepper(STEPS,26,28);



String Arsp, Grsp;

// select the pins used on the LCD panel
LiquidCrystal lcd(8,9, 4, 5, 6, 7);

#define DHT22_PIN 22

// define some values used by the panel and buttons
int lcd_key     = 0;
int adc_key_in  = 0;
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

// read the buttons
int read_LCD_buttons()
{
 adc_key_in = analogRead(0);      // read the value from the sensor 
 // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
 // we add approx 50 to those values and check to see if we are close
 if (adc_key_in > 1000) return btnNONE; // We make this the 1st option for speed reasons since it will be the most likely result
 // For V1.1 us this threshold
 if (adc_key_in < 50)   return btnRIGHT;  
 if (adc_key_in < 250)  return btnUP; 
 if (adc_key_in < 450)  return btnDOWN; 
 if (adc_key_in < 650)  return btnLEFT; 
 if (adc_key_in < 850)  return btnSELECT;  

 // For V1.0 comment the other threshold and use the one below:
/*
 if (adc_key_in < 50)   return btnRIGHT;  
 if (adc_key_in < 195)  return btnUP; 
 if (adc_key_in < 380)  return btnDOWN; 
 if (adc_key_in < 555)  return btnLEFT; 
 if (adc_key_in < 790)  return btnSELECT;   
*/


 return btnNONE;  // when all others fail, return this...
}

void setup(){
  
   Serial.begin(115200);
   lcd.begin(16, 2);              // start the library
   lcd.setCursor(0,0);
    // print a simple message
   lcd.print("INITIALIZING...");
   Serial1.begin(115200);
   delay(10000);
   Serial1.println("AT+CMGF=1");
   lcd.print("URBAN PLANT");
}
 
void loop(){
  dispHumidity();
  dispTemp();
  dispWaterLvl();
  dispSoilMoisture();
  serialOut();
  sendSMS();
  lcd.setCursor(0,0);
  lcd.print(title);
  lcd.setCursor(0,1);
  lcd.print("--Waiting--");
  //delay(60000);
}

void serialOut(){
  int chk = DHT.read11(DHT22_PIN);
  switch (chk)
  {
    case DHTLIB_OK:  
    //Serial.print("OK,t"); 
    break;
    case DHTLIB_ERROR_CHECKSUM: 
    Serial.print("Checksum error,t"); 
    break;
    case DHTLIB_ERROR_TIMEOUT: 
    Serial.print("Time out error,t"); 
    break;
    default: 
    Serial.print("Unknown error,t"); 
    break;
  }
  // DISPLAY DATA
  Serial.print("Humidity:");
  Serial.print(DHT.humidity, 1);
  Serial.print(",t");
  Serial.print("Temp: ");
  Serial.println(DHT.temperature, 1);
}

void sendSMS(){
    //Serial1.println();
    Serial1.print("AT+CMGS=\""); // send the SMS number
    Serial1.print("09260633178");
    Serial1.println("\"");
    delay(1000);
    Serial1.print("STATS:\n"); // SMS body
    Serial1.print("Humidity: ");
    Serial1.print(DHT.humidity,1);
    Serial1.print("% \n Temperature:");
    Serial1.print(DHT.temperature,1);
    Serial1.print("\n Water Level: ");

    int waterLvl = analogRead(A8);
    
   if(waterLvl >= 700){
      Serial1.print("EMPTY");
    }
    else if(waterLvl <= 500 && waterLvl >= 400){
      Serial1.print("|||");
    }
    else if(waterLvl <= 380 && waterLvl >= 360){
      Serial1.print("||||||");
    }
    else if(waterLvl <= 360 && waterLvl >= 320){
      Serial1.print("||||||||");
    }
    else{
      Serial1.print("|||||||||");
    }

    
    Serial1.print("\n Moisture: ");
    
  int moistLvl = analogRead(A9);

    if(moistLvl >= 500){
      Serial1.print("DRY");
      }
    else if(moistLvl <= 400 && moistLvl >= 350){
      Serial1.print("|||");
    }
    else if(moistLvl <= 350 && moistLvl >= 300){
      Serial1.print("||||||");
    }
    else if(moistLvl <= 300 && moistLvl >= 200){
      Serial1.print("|||||||||");
    }
    else{
      Serial1.print("||||||||||");
    }

    Serial1.print("\n\nPlant Monitoring");
 
    delay(500);
 
    Serial1.write(0x1A);
    Serial1.write(0x0D);
    Serial1.write(0x0A);

    if(Serial1.available())
  {
    Grsp = Serial1.readString();
    Serial.println(Grsp);
  }
}

void dispHumidity(){
  
 lcd.setCursor(0,0);
 lcd.print(title);
 lcd.setCursor(0,1);
 lcd.print("Humidity: ");
 lcd.print(DHT.humidity,1);
 lcd.print("%");
 delay(1500);
 lcd.clear();
}

void dispTemp(){
 lcd.setCursor(0,0);
 lcd.print(title);
 lcd.setCursor(0,1);
 lcd.print("Temp.:");
 lcd.print(DHT.temperature,1);
 lcd.print((char)0xDF);
 lcd.print("C");
 delay(1500);
 lcd.clear();
}

void startPump(){
   stepper.step(STEPS);
}

void stopPump(){
  digitalWrite(22,LOW);
  digitalWrite(24,LOW);
}

void dispWaterLvl(){
 int waterLvl = analogRead(A8);
  
 lcd.setCursor(0,0);
 lcd.print(title);
 lcd.setCursor(0,1);
 lcd.print("Water: ");
 //lcd.print(waterLvl);

 if(waterLvl >= 700){
    lcd.print("EMPTY");
  }
  else if(waterLvl <= 500 && waterLvl >= 400){
    lcd.print("|||");
  }
  else if(waterLvl <= 380 && waterLvl >= 360){
    lcd.print("||||||");
  }
  else if(waterLvl <= 360 && waterLvl >= 320){
    lcd.print("|||||||||");
  }
  else{
    lcd.print("---");
  }
 //lcd.print((char)0xDF);
 //lcd.print("C");
 delay(1500);
 lcd.clear();
}

void dispSoilMoisture(){

  int moistLvl = analogRead(A9);
  
  lcd.setCursor(0,0);
 lcd.print(title);
 lcd.setCursor(0,1);
 lcd.print("Moist: ");
 //lcd.print(moistLvl);

  if(moistLvl >= 500){
    lcd.print("DRY");
    
    while(moistLvl >= 500){

      moistLvl = analogRead(A9);
      
      stepper.step(STEPS);
      delay(500);
    }
     stopMotor();
  }
  else if(moistLvl <= 400 && moistLvl >= 350){
    lcd.print("|||");
  }
  else if(moistLvl <= 350 && moistLvl >= 300){
    lcd.print("||||||");
  }
  else if(moistLvl <= 300 && moistLvl >= 200){
    lcd.print("|||||||||");
  }
  else{
    lcd.print("----");
  }

  Serial.print(moistLvl);
 
 //lcd.print((char)0xDF);
 //lcd.print("C");
 delay(1500);
 lcd.clear();
}

//Stops motor from running.
void stopMotor(){
  digitalWrite(26,LOW);
  digitalWrite(28,LOW);
}

