/*
  Showing number 0-9 on a Common Anode 7-segment LED display
  Displays the numbers 0-9 on the display, with one second inbetween.
    A
   ---
F |   | B
  | G |
   ---
E |   | C
  |   |
   ---
    D
  This example code is in the public domain.
 */
 
// Pin 2-8 is connected to the 7 segments of the display.

int pinA = 2;
int pinB = 3;
int pinC = 4;
int pinD = 5;
int pinE = 6;
int pinF = 7;
int pinG = 8;
int D1 = 9;
int D2 = 10;
int D3 = 11;
int D4 = 12;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pins as outputs.
  pinMode(pinA, OUTPUT);     
  pinMode(pinB, OUTPUT);     
  pinMode(pinC, OUTPUT);     
  pinMode(pinD, OUTPUT);     
  pinMode(pinE, OUTPUT);     
  pinMode(pinF, OUTPUT);     
  pinMode(pinG, OUTPUT);   
  pinMode(D1, OUTPUT);  
  pinMode(D2, OUTPUT);  
  pinMode(D3, OUTPUT);  
  pinMode(D4, OUTPUT);  
}

// the loop routine runs over and over again forever:
void loop() {
  display_number(1234);
//  delay(1000);
//  clear();
//  display_number(1, 1);
//  delay(1000);
//  display_number(2, 2);
//  delay(1000);
//  display_number(3, 10);
//  delay(1000);
}

void clear(){
  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, HIGH);
  digitalWrite(D4, HIGH); 
}

void display_number(int number){

  for(int i=0; i < 4; i++){
    switch (i) {
      case 0: 
        digitalWrite(D1, LOW); 
        digitalWrite(D2, HIGH);
        digitalWrite(D3, HIGH);
        digitalWrite(D4, HIGH);
        break;
      case 1: 
        digitalWrite(D2, LOW); 
        digitalWrite(D1, HIGH);
        digitalWrite(D3, HIGH);
        digitalWrite(D4, HIGH);
        break;
      case 2: 
        digitalWrite(D3, LOW);
        digitalWrite(D2, HIGH);
        digitalWrite(D1, HIGH);
        digitalWrite(D4, HIGH);
        break;
      case 3: 
        digitalWrite(D4, LOW);
        digitalWrite(D2, HIGH);
        digitalWrite(D3, HIGH);
        digitalWrite(D1, HIGH);
        break;
    }
    int n = number / pow(10, i);
    Serial.println(n);
    switch (n) {
      case 0:
        digitalWrite(pinA, HIGH);   
        digitalWrite(pinB, HIGH);   
        digitalWrite(pinC, HIGH);   
        digitalWrite(pinD, HIGH);   
        digitalWrite(pinE, HIGH);   
        digitalWrite(pinF, HIGH);   
        digitalWrite(pinG, LOW);  
        break;
      case 1:
        digitalWrite(pinA, LOW);   
        digitalWrite(pinB, HIGH);   
        digitalWrite(pinC, HIGH);   
        digitalWrite(pinD, LOW);   
        digitalWrite(pinE, LOW);   
        digitalWrite(pinF, LOW);   
        digitalWrite(pinG, LOW);  
        break;
      case 2:
        digitalWrite(pinA, HIGH);   
        digitalWrite(pinB, HIGH);   
        digitalWrite(pinC, LOW);   
        digitalWrite(pinD, HIGH);   
        digitalWrite(pinE, HIGH);   
        digitalWrite(pinF, LOW);   
        digitalWrite(pinG, HIGH);  
        break;
      case 3:
        digitalWrite(pinA, HIGH);   
        digitalWrite(pinB, HIGH);   
        digitalWrite(pinC, HIGH);   
        digitalWrite(pinD, HIGH);   
        digitalWrite(pinE, LOW);   
        digitalWrite(pinF, LOW);   
        digitalWrite(pinG, HIGH);  
        break;
      case 4:
        digitalWrite(pinA, LOW);   
        digitalWrite(pinB, LOW);   
        digitalWrite(pinC, HIGH);   
        digitalWrite(pinD, LOW);   
        digitalWrite(pinE, LOW);   
        digitalWrite(pinF, HIGH);   
        digitalWrite(pinG, HIGH);  
        break;
      case 5:
        digitalWrite(pinA, HIGH);   
        digitalWrite(pinB, LOW);   
        digitalWrite(pinC, HIGH);   
        digitalWrite(pinD, HIGH);   
        digitalWrite(pinE, LOW);   
        digitalWrite(pinF, HIGH);   
        digitalWrite(pinG, HIGH);  
        break;
      case 6:
        digitalWrite(pinA, HIGH);   
        digitalWrite(pinB, HIGH);   
        digitalWrite(pinC, LOW);   
        digitalWrite(pinD, HIGH);   
        digitalWrite(pinE, HIGH);   
        digitalWrite(pinF, HIGH);   
        digitalWrite(pinG, HIGH);  
        break;
      case 7:
        digitalWrite(pinA, HIGH);   
        digitalWrite(pinB, HIGH);   
        digitalWrite(pinC, HIGH);   
        digitalWrite(pinD, HIGH);   
        digitalWrite(pinE, LOW);   
        digitalWrite(pinF, LOW);   
        digitalWrite(pinG, LOW);  
        break;
      case 8:
        digitalWrite(pinA, HIGH);   
        digitalWrite(pinB, HIGH);   
        digitalWrite(pinC, HIGH);   
        digitalWrite(pinD, HIGH);   
        digitalWrite(pinE, HIGH);   
        digitalWrite(pinF, HIGH);   
        digitalWrite(pinG, HIGH);  
        break;
      case 9:
        digitalWrite(pinA, HIGH);   
        digitalWrite(pinB, HIGH);   
        digitalWrite(pinC, HIGH);   
        digitalWrite(pinD, HIGH);   
        digitalWrite(pinE, LOW);   
        digitalWrite(pinF, HIGH);   
        digitalWrite(pinG, HIGH);  
        break;
      case 10:
        digitalWrite(pinA, LOW);   
        digitalWrite(pinB, LOW);   
        digitalWrite(pinC, LOW);   
        digitalWrite(pinD, LOW);   
        digitalWrite(pinE, LOW);   
        digitalWrite(pinF, LOW);   
        digitalWrite(pinG, HIGH);  
        break;
    }
  }
}
