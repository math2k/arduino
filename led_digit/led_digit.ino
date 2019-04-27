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

#define RST_PIN         9          // Configurable, see typical pin layout above
#define SS_PIN          10

const int a = 7; //a of 7-segment attach to digital pin 7
const int b = 6; //b of 7-segment attach to digital pin 6
const int c = 5; //c of 7-segment attach to digital pin 5
const int d = 3; //d of 7-segment attach to digital pin 11
const int e = 2; //e of 7-segment attach to digital pin 10
const int f = 4; //f of 7-segment attach to digital pin 8
const int g = 8; //g of 7-segment attach to digital pin 9
const int buzzer = A0;
//const int dp=4;//dp of 7-segment attach to digital pin 4


MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance


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
  mfrc522.PCD_Init();   // Init MFRC522
  digital_off();
}

void loop()
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // Dump debug info about the card; PICC_HaltA() is automatically called
  // mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
  unsigned int hex_num;
  hex_num =  mfrc522.uid.uidByte[0] << 24;
  hex_num += mfrc522.uid.uidByte[1] << 16;
  hex_num += mfrc522.uid.uidByte[2] <<  8;
  hex_num += mfrc522.uid.uidByte[3];

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
