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
RFID1 rfid;//create a variable type of RFID1

uchar serNum[5];  // array to store your ID

/*
 * IRQ_PIN 12 - 7
 * SCK_PIN 3 - 6
 * MOSI_PIN 13 - 5
 * MISO_PIN 11 - 8
 * NSS_PIN 8 - 4
 * RST_PIN 9 - 3
 */


void setup()
{
  Serial.begin(9600); //initialize the serial
  //rfid.begin(12, 3, 13, 11, 8, 9);  ////rfid.begin(IRQ_PIN,SCK_PIN,MOSI_PIN,MISO_PIN,NSS_PIN,RST_PIN)
  //rfid.begin(7, 13, 11, 12, 10, 9);  ////rfid.begin(IRQ_PIN,SCK_PIN,MOSI_PIN,MISO_PIN,NSS_PIN,RST_PIN)
  delay(100);//delay 1s
  //rfid.init(); //initialize the RFID
  Serial.println("Ready..");
}
void loop()
{
  //checkRFID(1);
  for(int i = 0; i < 4; i++){
    checkRFID(i);
  }
}


void checkRFID(int i){
  if(i==0){
    rfid.begin(7, 13, 11, 12, 10, 9);
  }
  if(i==1){
    rfid.begin(7, 13, 11, 8, 10, 9);
  }
  if(i==2){
    rfid.begin(7, 13, 11, 6, 10, 9);
  }
  if(i==3){
    rfid.begin(7, 13, 11, 5, 10, 9);
  }
  delay(100);
  rfid.init();
  uchar status;
  uchar str[MAX_LEN];
  // Search card, return card types
  status = rfid.request(PICC_REQIDL, str);
  Serial.print("Checking ");
  Serial.println(i);
  if (status != MI_OK)
  {
    return;
  }
  // Show card type
  //rfid.showCardType(str);
  //Prevent conflict, return the 4 bytes Serial number of the card
  status = rfid.anticoll(str);
  if (status == MI_OK)
  {
    Serial.print("The card's number is: ");
    memcpy(serNum, str, 5);
//    Serial.println(());
    //String myString = String((char *) str);
    uint8_t t = uidByte_to_int(serNum);
    //dump_byte_array(serNum, 4);
    //rfid.showCardID(serNum);//show the card ID
    //Serial.print(serNum);
    //Serial.print(" found on reader #");
   Serial.println(get_cardID(serNum));
  }
  delay(100);
  rfid.halt(); //command the card into sleep mode 
}

int uidByte_to_int(byte uidByte[]){
  int hexnum;
  hexnum += uidByte[0] << 24;
  hexnum += uidByte[1] << 16;
  hexnum += uidByte[2] <<  8;
  hexnum += uidByte[3];
  return hexnum;
}

void dump_byte_array(byte * buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}

String get_cardID(char * id)
{
    int IDlen=4;
    String s = "";
    for(int i=0; i<IDlen; i++){
        s += (0x0F & (id[i]>>4), HEX);
        s += (0x0F & id[i],HEX);
    }
    Serial.println(s);
    return s;
}
