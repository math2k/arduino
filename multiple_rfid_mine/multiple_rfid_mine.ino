/*
13 -> RFID SCK
12 -> RFID MISO
11 -> RFID MOSI
10 -> RFID NSS
9 ->  RFID RST

(avec resistance entre chaque)
8 ->  7LED - 1
7 ->  7LED - 4
6 ->  7LED - 5
5 ->  7LED - 9 
4 ->  7LED - 2  
3 ->  7LED - 7
2 ->  7LED - 6
1 -> 
0 -> 

1 2 3 4 5

   7LED

6 7 8 9 0


3.3v -> RFID VCC
GND -> RFID GND
GND -> 7LED - 8
GND -> buzzer (-)
A0 -> buzzer (+)


*/
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         2          // Configurable, see typical pin layout above
#define SS_1_PIN        6
#define SS_2_PIN .      7

#define NR_OF_READERS      1
byte ssPins[] = {2, 7};

//byte validTagsArray[][4] = {
  //{0xC3, 0xE4, 0x4E, 0xD3},
  //{0x12, 0x23, 0x53, 0xD3}
  //{0x83, 0xE1, 0xC1, 0x02},
  //{0x59, 0xEC, 0xC5, 0x56}
//};

//int validTags[] = { 49410, 50518 };
int validTags[] = { 20179, 21459 };

const int a = 7; //a of 7-segment attach to digital pin 7
const int b = 6; //b of 7-segment attach to digital pin 6
const int c = 5; //c of 7-segment attach to digital pin 5
const int d = 3; //d of 7-segment attach to digital pin 11
const int e = 2; //e of 7-segment attach to digital pin 10
const int f = 4; //f of 7-segment attach to digital pin 8
const int g = 8; //g of 7-segment attach to digital pin 9
const int buzzer = A0;
const int relay = 3;
//const int dp=4;//dp of 7-segment attach to digital pin 4


MFRC522 mfrc522[NR_OF_READERS];  // Create MFRC522 instance


void setup()
{
  // Initialize 7-led pins
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(buzzer, OUTPUT); // buzzer
  Serial.begin(9600);   // Initialize serial communications with the PC
  while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();      // Init SPI bus
  for (uint8_t reader = 0; reader < sizeof(ssPins); reader++) {
    mfrc522[reader].PCD_Init(ssPins[reader], RST_PIN);
    Serial.print(F("Reader "));
    Serial.print(reader);
    Serial.print(F(": "));
    mfrc522[reader].PCD_DumpVersionToSerial();
  }
  digital_off();
  // Relay
  pinMode(relay, OUTPUT);
  digitalWrite(relay, LOW);
}

int uidByte_to_int(byte uidByte[]){
  int hexnum;
  hexnum += uidByte[0] << 24;
  hexnum += uidByte[1] << 16;
  hexnum += uidByte[2] <<  8;
  hexnum += uidByte[3];
  return hexnum;
}


int tags_status[sizeof(ssPins)] = { };
void loop()
{

  for (uint8_t reader = 0; reader < sizeof(ssPins); reader++) {
    delay(100);
    // Look for new cards
    if (mfrc522[reader].PICC_IsNewCardPresent() && mfrc522[reader].PICC_ReadCardSerial()) {
      Serial.print(F("Reader "));
      Serial.print(reader);

      // Show some details of the PICC (that is: the tag/card)
      Serial.print(F(": Card UID:"));
      dump_byte_array(mfrc522[reader].uid.uidByte, mfrc522[reader].uid.size);
      Serial.println();
      unsigned int current_tag;
      current_tag = uidByte_to_int(mfrc522[reader].uid.uidByte);
      Serial.print("Current tag: ");
      Serial.print(current_tag);
      if (current_tag == validTags[reader]){
        Serial.print(reader);
        Serial.print(" - OK!");
        Serial.println();
        tags_status[reader] = 1;
      }
    }
    if(tags_status[0] && tags_status[1]){
      Serial.println("Bingo!");
      digitalWrite(relay, HIGH);
      delay(100);
      exit(0);
    }
   /* bool all_tags_correct = 0;
    for(uint8_t i = 0; i < sizeof(ssPins); i++){
      if(tags_status[i]){
        Serial.print(i);
        Serial.println(" is correct");
        all_tags_correct = all_tags_correct && tags_status;
      }
    }
    if(all_tags_correct){
      Serial.println("All correct!");
      exit(0);
    }*/
  }
    

  // Dump debug info about the card; PICC_HaltA() is automatically called
  // mfrc522.PICC_DumpToSerial(&(mfrc522.uid));

/*
  if (mfrc522.uid.uidByte[0] == 0x83 &&
      mfrc522.uid.uidByte[1] == 0xe1 &&
      mfrc522.uid.uidByte[2] == 0xc1 &&
      mfrc522.uid.uidByte[3] == 0x02) {
    Serial.println("Good");
    beep(60,1);
    delay(100);
    beep(60,1);
    delay(100);
    beep(60,1);
    for (int i = 0; i < 10; i++) {
      animate();
      digital_1();//diaplay 1 to the 7-segment
      delay(1000);//wait for a second
      digital_2();//diaplay 2 to the 7-segment
      delay(1000); //wait for a second
      digital_3();//diaplay 3 to the 7-segment
      delay(1000); //wait for a second
      digital_4();//diaplay 4 to the 7-segment
      delay(1000); //wait for a second
      //    digital_5();//diaplay 5 to the 7-segment
      //    delay(1000); //wait for a second
      //    digital_6();//diaplay 6 to the 7-segment
      //    delay(1000); //wait for a second
      //    digital_7();//diaplay 7 to the 7-segment
      //    delay(1000); //wait for a second
      //    digital_8();//diaplay 8 to the 7-segment
      //    delay(1000); //wait for a second
      //    digital_9();//diaplay 8 to the 7-segment
      //    delay(1000); //wait for a second
    }
  }
  else {
    Serial.println("Not good");
    beep(140,4);
  }
  */

}

void beep(int l,int d)
{
  for (int i = 0; i < l; i++)
  {
    digitalWrite(buzzer, HIGH);
    delay(d);//wait for 1ms
    digitalWrite(buzzer, LOW);
    delay(d);//wait for 1ms
  }
}

void animate(void)
{
  digitalWrite(a, HIGH);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
  delay(100);
  digitalWrite(a, LOW);
  digitalWrite(b, HIGH);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
  delay(100);
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, HIGH);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
  delay(100);
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, HIGH);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
  delay(100);
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, HIGH);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
  delay(100);
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, HIGH);
  digitalWrite(g, LOW);
  delay(100);
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
  delay(100);
  for (int i = 0; i < 5; i++) {
    digitalWrite(a, HIGH);
    digitalWrite(b, HIGH);
    digitalWrite(c, HIGH);
    digitalWrite(d, HIGH);
    digitalWrite(e, HIGH);
    digitalWrite(f, HIGH);
    digitalWrite(g, HIGH);
    delay(100);
    digitalWrite(a, LOW);
    digitalWrite(b, LOW);
    digitalWrite(c, LOW);
    digitalWrite(d, LOW);
    digitalWrite(e, LOW);
    digitalWrite(f, LOW);
    digitalWrite(g, LOW);
    delay(100);
  }
}

void digital_1(void)
{
  digitalWrite(a, LOW);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
}
void digital_2(void)
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, LOW);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, LOW);
  digitalWrite(g, HIGH);
}
void digital_3(void)
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, HIGH);
}
void digital_4(void)
{
  digitalWrite(a, LOW);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}
void digital_5(void)
{
  digitalWrite(a, HIGH);
  digitalWrite(b, LOW);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, LOW);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}
void digital_6(void)
{
  digitalWrite(a, HIGH);
  digitalWrite(b, LOW);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}
void digital_7(void)
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
}
void digital_8(void)
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}
void digital_9(void)
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, LOW);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}
void digital_off(void)
{
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
}

void dump_byte_array(byte * buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}
