void setup() {
  // put your setup code here, to run once:
  pinMode(A5, INPUT_PULLUP);
  Serial.println("ffs");
}

void loop() {
  // put your main code here, to run repeatedly:
  int val = digitalRead(A5);
  Serial.print(val);
}
