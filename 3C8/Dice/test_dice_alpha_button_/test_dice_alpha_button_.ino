//**Globals**
//Clock
int count;
//Pins on board -> LEDs 
int a = 2;
int b = 3;
int gnd = 4;
int c = 5;
int nc = 6;
int d = 7;
//Chip Binary Outputs
int q0 = 0; 
int q1 = 0;
int q2 = 0;
int q3 = 0;
int cl_out =2;
//Variables to allow code to be run/stopped by button press
int progress;
int button = 8;
int led = 13;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.print("Beginning setup tests\r\n");
  pinMode(a, OUTPUT);
  digitalWrite(a, HIGH);
  //delay(1000);  
  pinMode(b, OUTPUT);
  digitalWrite(b, HIGH);
  //delay(1000);  
  pinMode(gnd, OUTPUT);
  digitalWrite(gnd, LOW);
  pinMode(c, OUTPUT);
  digitalWrite(c, HIGH);
  //delay(1000);
  pinMode(nc, OUTPUT);
  digitalWrite(nc, LOW);
  pinMode(d, OUTPUT);
  digitalWrite(d, HIGH);
  //delay(1000);
  pins_reset();
  //delay(1000);
  count = set_count();
  Serial.print("Tests complete, count set to: ");
  Serial.print(count);
  Serial.print("\r\n");
  pinMode(cl_out, OUTPUT);
  progress = 0;
  pinMode(button, INPUT_PULLUP);
  pinMode(led, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
//  if (digitalRead(button) == LOW) {
//    //Serial.print("Test\r\n");
//    if (progress == 0) {progress = 255;}
//    else {progress = 0;}
//  }
  check_button();
  if (progress > 0) {//In theory, this code should only run between button presses
    Serial.print("Button Pressed\r\n");
    //while (count <= 7) { //Should not exit -> Logic resets clock/count @7
      //action(count);
      digitalWrite(led, HIGH);
      Serial.print("\r\n**Count: ");
      Serial.print(count);
      Serial.print(" **\r\n");
      digitalWrite(cl_out, HIGH);    
      action();
      check_button();
      //delay(1000); //So we can see each step
      digitalWrite(cl_out, LOW);
      delay(100);
      pins_reset();
    //}
    //Serial.print("ERROR exited loop\r\n");
    //delay(5000);
  }
    else {
    Serial.print("Button not pressed\r\n");
    digitalWrite(cl_out, LOW);
    digitalWrite(led, LOW);
  }
}

//void sim(int count, int &q0, int &q1, int &q2, int &q3) {
void sim_output() { //Simulates the binary output from the chip
  Serial.print("Generating chip output\r\n");
  q0 = 0;
  q1 = 0;
  q2 = 0;
  q3 = 0;
  int temp = count;
  if (temp - 8 >= 0) {
    q3 = 1;
    temp = temp - 8;
  }
  Serial.print(q3);
  if (temp - 4 >= 0) {
    q2 = 1;
    temp = temp - 4; 
  }
  Serial.print(q2);
  if (temp - 2 >= 0) {
    q1 = 1;
    temp = temp - 2;
  }
  Serial.print(q1);
  if (temp == 1) {q0 = 1;}
  Serial.print(q0);
  Serial.print("\r\n");
}

void predict() { //For Serial.print, what action should be show, e.g. "1", "3", "reset", etc.
  if (q0 && !q1 && !q2 && !q3) { //0001
    Serial.print("1 -> C\r\n");
  }
  if (!q0 && q1 && !q2 && !q3) { //0010
    Serial.print("2 -> A\r\n");
  }
  if (q0 && q1 && !q2 && !q3) { //0011
    Serial.print("3 -> A,C\r\n");
  }
  if (!q0 && !q1 && q2 && !q3) { //0100
    Serial.print("4 -> A,B\r\n");
  }
  if (q0 && !q1 && q2 && !q3) { //0101
    Serial.print("5 -> A,B,C\r\n");
  }
  if (!q0 && q1 && q2 && !q3) { //0110
    Serial.print("6 -> A,B,D\r\n");
  }
  if (q0 && q1 && q2 && !q3) { //0111
    Serial.print("Reset\r\n");
  }
}

//void action (int count) {
void action () { //Simulates Logic Gates -> Sets appropriate pins HIGH (Light LEDs)
  //sim(count, q0, q1, q2, q3);
  bool increment = false;
  sim_output();
  Serial.print("Action to be performed: ");
  predict();
  //delay(500);
  if (q2 && q1 && q0) { //Reset -> trigger Preset Enable
    count = set_count();
    return;
  }
  if (q2 || q1) { //A
    digitalWrite(a, HIGH);
    increment = true;
  }
  if (q2) { //B
    digitalWrite(b, HIGH);
    increment = true;
  }
  if (q0) { //C
    digitalWrite(c, HIGH);
    increment = true;
  }
  if (q2 && q1) { //D
    digitalWrite(d, HIGH);
    increment = true;
  }
  if (increment) {count++;}
  else {
    Serial.print("ERROR unknown case");
  }
}

int set_count () { //Simulate Jams
  int p3 = 0; //MSB
  int p2 = 0;
  int p1 = 0;
  int p0 = 1; //LSB
  return ((p0) + (p1 * 2) + (p2 * 4) + (p3 * 8));
}

void pins_reset () { //All lights go off
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
}

void check_button() {
  if (digitalRead(button) == LOW) {
    //Serial.print("Test\r\n");
    if (progress == 0) {progress = 255;}
    else {progress = 0;}
  }  
}

