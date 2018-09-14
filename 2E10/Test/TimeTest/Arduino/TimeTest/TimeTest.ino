void setup() {
  Serial.begin(9600);
  Serial.print("+++");
  delay(1500);
  Serial.println("ATID 3308, CH C, CN");
  delay(11000);
  while (Serial.read() != -1) {}
}

void loop() {
  // put your main code here, to run repeatedly:

}

void serialEvent() {
  Serial.write("a");
}
