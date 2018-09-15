//**Globals**
//Flag
bool fail = 0;
int tests = 0;
//Clock
int count;
//Pins out
int q0 = 13; //LSB
int q1 = 12;
int q2 = 11;
int q3 = 10; //MSB
//int trig_res = 17;
//Pins in
int a = 2;
int b = 3;
int gnd = 4;
int c = 5;
int nc = 6;
int d = 7;
int pe = 9;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.print("Beginning Setup\r\n");
  pinMode(q0, OUTPUT);
  pinMode(q1, OUTPUT);
  pinMode(q2, OUTPUT);
  pinMode(q3, OUTPUT);
  //pinMode(trig_res, OUTPUT);
  digitalWrite(q0, LOW);
  digitalWrite(q1, LOW);
  digitalWrite(q2, LOW);
  digitalWrite(q3, LOW);
  digitalWrite(pe, LOW);
  Serial.print("Checking LEDs\r\n");
  pinMode(a, OUTPUT);
  digitalWrite(a, HIGH);
  pinMode(b, OUTPUT);
  digitalWrite(b, HIGH);
  pinMode(c, OUTPUT);
  digitalWrite(c, HIGH);
  pinMode(d, OUTPUT);
  digitalWrite(d, HIGH);
  delay(5000);
  Serial.print("LED checking complete, hopefully they all work!\r\n");
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  pinMode(a, INPUT);
  pinMode(b, INPUT);
  pinMode(c, INPUT);
  pinMode(d, INPUT);
  pinMode(pe, INPUT);
  count = set_count();
  Serial.print("Count: ");
  Serial.print(count);
  Serial.print("\r\n");
  out_reset();
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if (!fail && tests < 3) { //Code in here should only run while not failed
    for (count; count <= 6; count++) {
      Serial.print("\r\n**Count: ");
      Serial.print(count);
      Serial.print(" **\r\n");
      action();
      delay(1000);
      out_reset();
      if (fail) {break;}
    }
    Serial.print("\r\n**Count: ");
    Serial.print(count);
    Serial.print(" **\r\n");
    action();
    delay(1000);
    out_reset();
    tests++;
  }
  else {test_finish();}
}

void sim_output() { //Simulates the binary output from the chip
  Serial.print("Generating chip output\r\n");
  int temp = count;
  if (temp - 8 >= 0) {
    digitalWrite(q3, HIGH);
    temp = temp - 8;
  }
  if (temp - 4 >= 0) {
    digitalWrite(q2, HIGH);
    temp = temp - 4; 
  }
  if (temp - 2 >= 0) {
    digitalWrite(q1, HIGH);
    temp = temp - 2;
  }
  if (temp == 1) {digitalWrite(q0, HIGH);}
  if(digitalRead(q3) == HIGH) {Serial.print("1");}
  else {Serial.print("0");}
  if(digitalRead(q2) == HIGH) {Serial.print("1");}
  else {Serial.print("0");}
  if(digitalRead(q1) == HIGH) {Serial.print("1");}
  else {Serial.print("0");}
  if(digitalRead(q0) == HIGH) {Serial.print("1");}
  else {Serial.print("0");}      
  Serial.print("\r\n");
}

void predict(int &event) { //For Serial.print, what action should be shown, e.g. "1", "3", "reset", etc.
  event = 0;
  Serial.print("Predicted Output: ");
  if ((digitalRead(q0) == HIGH) && (digitalRead(q1) == LOW) && 
  (digitalRead(q2) == LOW) && (digitalRead(q3) == LOW)) { //0001
    Serial.print("1 -> C\r\n");
    Serial.print("q0 = 1\rq1 = 0\rq2 = 0\rq3 = 0\r\n");
    event = 1;
  }
  else if ((digitalRead(q0) == LOW) && (digitalRead(q1) == HIGH) && 
  (digitalRead(q2) == LOW) && (digitalRead(q3) == LOW)) { //0010
    Serial.print("2 -> A\r\n");
    Serial.print("q0 = 0\rq1 = 1\rq2 = 0\rq3 = 0\r\n");
    event = 2;
  }
  else if ((digitalRead(q0) == HIGH) && (digitalRead(q1) == HIGH) && 
  (digitalRead(q2) == LOW) && (digitalRead(q3) == LOW)) { //0011
    Serial.print("3 -> A,C\r\n");
    Serial.print("q0 = 1\rq1 = 1\rq2 = 0\rq3 = 0\r\n");
    event = 3;
  }
  else if ((digitalRead(q0) == LOW) && (digitalRead(q1) == LOW) && 
  (digitalRead(q2) == HIGH) && (digitalRead(q3) == LOW)) { //0100
    Serial.print("4 -> A,B\r\n");
    Serial.print("q0 = 0\rq1 = 0\rq2 = 1\rq3 = 0\r\n");
    event = 4;
  }
  else if ((digitalRead(q0) == HIGH) && (digitalRead(q1) == LOW) && 
  (digitalRead(q2) == HIGH) && (digitalRead(q3) == LOW)) { //0101
    Serial.print("5 -> A,B,C\r\n");
    Serial.print("q0 = 1\rq1 = 0\rq2 = 1\rq3 = 0\r\n");
    event = 5;
  }
  else if ((digitalRead(q0) == LOW) && (digitalRead(q1) == HIGH) && 
  (digitalRead(q2) == HIGH) && (digitalRead(q3) == LOW)) { //0110
    Serial.print("6 -> A,B,D\r\n");
    Serial.print("q0 = 0\rq1 = 1\rq2 = 1\rq3 = 0\r\n");
    event = 6;
  }
  else if ((digitalRead(q0) == HIGH) && (digitalRead(q1) == HIGH) && 
  (digitalRead(q2) == HIGH) && (digitalRead(q3) == LOW)) { //0111
    Serial.print("Reset\r\n");
    Serial.print("q0 = 1\rq1 = 1\rq2 = 1\rq3 = 0\r\n");
    event = 7;
  }
  else {
    Serial.print("Unknown event: ERROR\r\n");
    fail = 1;
  }
}

void action() {
  int event = 0;
  bool temp_fail = 0; //Non global so that all checks performed 
  sim_output();
  predict(event);
  delay(500);
  if (event == 7) {
    if (digitalRead(pe) == LOW) {
      Serial.print("Preset Enable not triggered!\r\n");
      Serial.print("Possible problem with AND3, "
      "inputs q0, q1, q2\r\n"); 
      temp_fail = 1;
    }
    else {count = set_count();}
  }
  else {
    if (event == 6) {
      checks(temp_fail, 1, 1, 0, 1, 0); 
    }
    else if (event == 5) {
      checks(temp_fail, 1, 1, 1, 0, 0);
    }
    else if (event == 4) {
      checks(temp_fail, 1, 1, 0, 0, 0);
    }
    else if (event == 3) {
      checks(temp_fail, 1, 0, 1, 0, 0);
    }
    else if (event == 2) {
      checks(temp_fail, 1, 0, 0, 0, 0);
    }
    else if (event == 1) {
      checks(temp_fail, 0, 0, 1, 0, 0);
    }
    else {
      Serial.print ("Unknown error: event not defined in action()\r\n");
      temp_fail = 1;
    }
  }
  if (temp_fail) {fail = 1;}
}

int set_count () { //Simulate Jams
  int p3 = 0; //MSB
  int p2 = 0;
  int p1 = 0;
  int p0 = 1; //LSB
  return ((p0) + (p1 * 2) + (p2 * 4) + (p3 * 8));
}

void out_reset () { //All output pins LOW
  digitalWrite(q0, LOW);
  digitalWrite(q1, LOW);
  digitalWrite(q2, LOW);
  digitalWrite(q3, LOW);
  digitalWrite(pe, LOW);
}

void test_finish() {
  if (fail) {
    Serial.print("Test failure!\r\n");
    Serial.print("Be sure to check POWER and GROUND too\r\n");
  }
  else {Serial.print("Test success\r\n");}
  Serial.print("Testing ended after: ");
  Serial.print(tests);
  Serial.print("/3 runs\r\n");
  Serial.end();
  for(;;); //Inifinite loop so program stays here
}

//Checks if the readings from the output pins match the prdicted
void checks(bool &temp_fail, int a_pin, int b_pin, int c_pin, int d_pin, int pe_pin) {
  if ((a_pin == 1) && (digitalRead(a) == LOW)) {
    Serial.print("A is LOW. "
    "Possible issue with OR2, inputs q1, q2 -> should be 0, 0\r\n");    
    temp_fail = 1;
  }
  else if ((a_pin == 0) && (digitalRead(a) == HIGH)){
    Serial.print("A is HIGH. "
    "Possible issue with OR2, inputs q1, q2 -> at least one should be 1\r\n");
    temp_fail = 1;
  }
  if ((b_pin == 1) && (digitalRead(b) == LOW)) {
    Serial.print("B is LOW. "
    "Possible issue with connection from q2 -> should be 1\r\n");    
    temp_fail = 1;
  }
  else if ((b_pin == 0) && (digitalRead(b) == HIGH)){
    Serial.print("B is HIGH. "
    "Possible issue with connection from q2 -> should be 0\r\n");
    temp_fail = 1;
  }  
  if ((c_pin == 1) && (digitalRead(c) == LOW)) {
    Serial.print("C is LOW. "
    "Possible issue with connection from q0 -> should be 1");    
    temp_fail = 1;
  }
  else if ((c_pin == 0) && (digitalRead(c) == HIGH)){
    Serial.print("C is HIGH. "
    "Possible issue with connection from q0 -> should be 0\r\n");
    temp_fail = 1;
  }  
  if ((d_pin == 1) && (digitalRead(d) == LOW)) {
    Serial.print("D is LOW. "
    "Possible issue with AND2, inputs q1, q2 -> should both be 1\r\n");  
    temp_fail = 1;
  }
  else if ((d_pin == 0) && (digitalRead(d) == HIGH)){
    Serial.print("D is HIGH. "
    "Possible issue with AND2, inputs q1, q2 -> at least one should be 0\r\n");
    temp_fail = 1;    
  }  
  if ((pe_pin == 1) && (digitalRead(pe) == LOW)) {
    Serial.print("Preset Enable not triggered (is LOW)!\r\n");
    Serial.print("Possible problem with AND3, "
    "inputs q0, q1, q2 -> all should be 1\r\n");    
    temp_fail = 1;
  }
  else if ((pe_pin == 0) && (digitalRead(pe) == HIGH)){
    Serial.print("Preset Enable is HIGH. "
    "Possible issue with AND3, inputs q0, q1, q2 -> "
    "at least one should be 0\r\n"); 
    temp_fail = 1;   
  }  
}

