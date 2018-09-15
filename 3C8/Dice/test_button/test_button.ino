int progress;
int button = 8;
int led = 13;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.print("Begin Setup\r\n");
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);
  delay(1000);
  digitalWrite(led, LOW);
  progress = 0;
  pinMode(button, INPUT_PULLUP);
  Serial.print("End Setup\r\n");
}

void loop() {
  // put your main code here, to run repeatedly:
    if (digitalRead(button) == LOW) {
      if (progress == 0) {progress = 255;}
      else {progress = 0;}
  }
  //delay(1000);
  if (progress > 0) {
    Serial.print("Button Pressed\r\n");
    digitalWrite(led, HIGH);
  }
  else {
    Serial.print("Button not pressed\r\n");
    digitalWrite(led, LOW);
  }
}
