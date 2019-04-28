#include <fDigitsSegtPin.h>

fDigitsSegtPin Display(6, 5, 13, 4, 8, 12, 3, 11, 10, 7,2, 9); //D;12,11,10 ,9

int switchPins[8] = {A0, A1, A2, A3, A4, A5, 0, 1};

void setup() {  
  Serial.begin(9600);   // Initialize serial communications with the PC
  while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  // put your setup code here, to run once:
  Display.begin();
  Display.doPrint_firstZero = 1;
  for(int i=0; i<8; i++){
    pinMode(switchPins[i], INPUT_PULLUP);
  }
}

int validPositions[8] = {1, 0, 1, 1, 0, 1, 0, 0};
int currentPositions[8] = {1, 0, 1, 1, 0, 1, 0, 0};

void loop() {
  bool changed = false;
  for(int i=0; i<8; i++){
    int pos;
    pos = digitalRead(switchPins[i]);
    if(pos != currentPositions[i]) {
      changed = true;
      Serial.print("Changed ");
      Serial.print(pos);
      Serial.print(" - ");
      Serial.print(currentPositions[i]);
      Serial.print(" - ");
      Serial.println(i);
      
    }
    currentPositions[i] = pos;
  }
  bool correct = true;
  for(int i=0; i<8; i++){
      Serial.print(currentPositions[i]);
      Serial.print(" ");
      Serial.print(validPositions[i]);
      Serial.print(" ");
    if(currentPositions[i] != validPositions[i]){
      Serial.print(i);
      Serial.println(" incorrect");
      
      correct = false;
    } else {
      Serial.print(i);
      Serial.println(" correct");
    }
  }
  
  if(changed){
    for(int i=0; i < 900; i++){
      Display.fvPrint(3, 3, 0);
    }
    for(int i=0; i < 900; i++){
      Display.fvPrint(3, 2, 0);
    }
    for(int i=0; i < 900; i++){
      Display.fvPrint(3, 1, 0);
    }
  }
  if(correct){
    for(int i=0; i < 300; i++){
      Display.print(5931);
    }
  } else {
    for(int i=0; i < 300; i++){
      
      digitalWrite(9, 0);//Set digits to write
      digitalWrite(10, 0);
      digitalWrite(11, 0);
      digitalWrite(12, 0);
      
      digitalWrite(8, 1); //Set dash
      digitalWrite(1, 0);
      digitalWrite(2, 0);
      digitalWrite(7, 0);
      digitalWrite(3, 0);
      digitalWrite(4, 0);
      digitalWrite(5, 0);
      digitalWrite(6, 0);
      digitalWrite(13, 0);
    }
  }
  
}
