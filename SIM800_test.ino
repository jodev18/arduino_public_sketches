/*
  SIM800 Test Send Sketch for Arduino
  
  Initializes GSM Module and sends an SMS to recipient

  * for uSD slot AT commands please see the 
    SIM800 Dev kit Manual.
  
  The circuit:
  *Arduino pin 0 (RX) - GSM Module (TX)
  *Arduino pin 1 (TX) - GSM Module (RX)
  
  Created 2010
  by Meann Zabanal
  Modified 
  by John for GSM Shield testing
*/

char Rx_data[50];
unsigned char Rx_index = 0;
int i = 0;
char msg[160];
int sig;

void setup() {
  Serial.begin(38400);
  Serial1.begin(38400);
  
  initGSM();
  send_msg("", "Text Message");
}

void loop() {
  //none
}

void send_msg(char *number, char *msg)
{
  char at_cmgs_cmd[30] = {'\0'};
  char msg1[160] = {'\0'};
  char ctl_z = 0x1A;

  sprintf(msg1, "%s%c", msg, ctl_z);
  sprintf(at_cmgs_cmd, "AT+CMGS=\"%s\"\r\n",number);
  
  sendGSM(at_cmgs_cmd);
  delay(100);
  delay(100);
  delay(100);
  sendGSM(msg1);
  delay(100);
}

void sendGSM(char *string){
  Serial1.write(string);
  Serial.write(string);
  delay(90);
}

void clearString(char *strArray) {
  int j;
  for (j = 100; j > 0; j--)
    strArray[j] = 0x00;
}

void send_cmd(char *at_cmd, char clr){
  char *stat = '\0';
  while(!stat){
    sendGSM(at_cmd);
    delay(90);
    readSerialString(Rx_data);
    
    stat = strstr(Rx_data, "OK");
  }
  if (clr){
    clearString(Rx_data);
    delay(200);
    stat = '\0';
  }
}

void initGSM(){
  
  //send_cmd("AT\r\n",1);						
//  send_cmd("ATE0\r\n",1); // Turn off automatic echo of the GSM Module	
	
  send_cmd("AT+CMGF=1\r\n",1);			// Set message format to text mode
  //Sucess
  
  Serial.println("Success");
	
  delay(1000);
  delay(1000);
  delay(1000);
}

void readSerialString (char *strArray) {
  
  if(!Serial1.available()) {
    Serial.println("Serial not available");
    return;
  }
  
  while(Serial1.available()) {
    strArray[i] = Serial1.read();
    i++;
  }
}


