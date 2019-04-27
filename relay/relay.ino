int IN_PIN = 3;
void setup() {
  pinMode(IN_PIN, OUTPUT);
  digitalWrite(IN_PIN, LOW);
  Serial.begin(9600);
  delay(1000);
  Serial.println("Enter 1 to turn on lamp, 0 to turn off"); 
}
void loop() {
   while (Serial.available()) {
    char inChar = (char)Serial.read();
    if (inChar == '1') {
      digitalWrite(IN_PIN, HIGH);
      Serial.println("Lamp is On!");
    }else if(inChar == '0'){
      digitalWrite(IN_PIN, LOW);
      Serial.println("Lamp is Off!");
    }else{
      Serial.println("Invalid input!");
    }
  }
}
