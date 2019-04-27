/*******************************************
 * function:get the id of RFID key
 * RFID                    SunFounder Uno
 * VCC                        3.3V
 * RST                        2
 * GND                        GND
 * MISO                       3
 * MOSI                       4
 * SCK                        5
 * NSS                        6
 * IRQ                        7
 ****************************************/

#include"rfid1.h"
RFID1 rfid;
uchar serNum[5];
byte misoPins[4] = {12, 8, 6, 5};
bool tagStatus[4] = {false, false, false, false};
uint8_t validTags[4] = {98, 39, 96, 207};
const int relay = 3;


void setup()
{
  Serial.begin(9600);
  delay(100);
  Serial.println("Ready..");
  // Relay
  pinMode(relay, OUTPUT);
  digitalWrite(relay, LOW);
}


void loop()
{
  uchar currentTag;
  //checkRFID(1);
  for(int i = 0; i < sizeof(misoPins); i++){
    
    Serial.print(i);
    currentTag = checkRFID(i);
    /*Serial.print(currentTag);
    Serial.print(" - ");
    Serial.print(validTags[i]);
    Serial.println();*/    
    if(currentTag == validTags[i]){
      tagStatus[i] = true;
      Serial.println(" is correct");
    } else {
      tagStatus[i] = false;
      Serial.println(" is incorrect");      
    }
  }
  if(tagStatus[0] && tagStatus[1] && tagStatus[2] && tagStatus[3]){
    Serial.println("Bingo!");
    digitalWrite(relay, HIGH);
    delay(100);
    exit(0);
  }
}


uint8_t checkRFID(int idx){
  uchar status;
  uchar str[MAX_LEN];
  
  rfid.begin(7, 13, 11, misoPins[idx], 10, 9);
  delay(100);
  rfid.init();
  // Search card, return card types
  status = rfid.request(PICC_REQIDL, str);
  //Serial.print("Checking ");
  //Serial.println(i);
  if (status != MI_OK)
  {
    return;
  }
  //Prevent conflict, return the 4 bytes Serial number of the card
  status = rfid.anticoll(str);
  if (status == MI_OK)
  {
    //Serial.print("The card's number is: ");
    memcpy(serNum, str, 4);
    //rfid.showCardID(serNum);//show the card ID
    //Serial.print(" found on reader #");
    //Serial.println(getCardID(serNum));
  }
  delay(100);
  rfid.halt();
  return getCardID(serNum);
}

uint8_t getCardID(char * id){
  return id[0] + id[1] + id[2] + id[3];
}
