//Code to test the wiring of a 7segment display
//Tests 4511 and 7segment display, as well as wiring
//Run from 0 - 9
//**Globals**
//Testing Flags
bool fail = 0;
int tests = 0;
//Clock
int count = 0;
//Pins Out
//Wires as OUTPUT from arduino to chip (4511)
int d_d = 3; //MSB
int d_c = 4;
int d_b = 5;
int d_a = 2; //LSB
//Pins In
//Wires as INPUT to arduino from chip (4511)
int o_f = 13;
int o_g = 12;
int o_a = 11;
int o_b = 10;
int o_c = 9;
int o_d = 8;
int o_e = 7;

//Performing setup for tests
void setup() {
  Serial.begin(9600);
  Serial.print("Beginning Setup\r\n");
  pinMode(d_d, OUTPUT);
  pinMode(d_c, OUTPUT);
  pinMode(d_b, OUTPUT);
  pinMode(d_a, OUTPUT);
  out_reset();
  delay(50);
  pinMode(o_a, INPUT);
  pinMode(o_b, INPUT);
  pinMode(o_c, INPUT);
  pinMode(o_d, INPUT);
  pinMode(o_e, INPUT);
  pinMode(o_f, INPUT);
  pinMode(o_g, INPUT);
  Serial.print("Running Tests\r\n");
}
//Looped code for testing
void loop() {
  if (!fail && tests < 3) { //Code in here should only run while not failed and less than 3 tests ran
    for (count; count <= 9; count++) { //To enable running from 0 to 9
      Serial.print("\r\n**Count: ");
      Serial.print(count);
      Serial.print(" **\r\n");
      action();
      delay(1000);
      out_reset();
      if (fail) {break;}
    }
    count = 0;
    tests++;
  }
  else {test_finish();}
}
//Simulates the binary output from the chip (4511)
void sim_output() { 
  Serial.print("Generating chip (4511) output\r\n");
  int temp = count; //So that we do not affect the variable 'count'
  if (temp - 8 >= 0) {
    digitalWrite(d_d, HIGH);
    temp = temp - 8;
  }
  if (temp - 4 >= 0) {
    digitalWrite(d_c, HIGH);
    temp = temp - 4;
  }
  if (temp - 2 >= 0) {
    digitalWrite(d_b, HIGH);
    temp = temp - 2;
  }
  if (temp == 1) {digitalWrite(d_a, HIGH);}
  //Print out 'count' in binary, based upon outputs set HIGH
  if(digitalRead(d_d) == HIGH) {Serial.print("1");}
  else {Serial.print("0");}
  if(digitalRead(d_c) == HIGH) {Serial.print("1");}
  else {Serial.print("0");}
  if(digitalRead(d_b) == HIGH) {Serial.print("1");}
  else {Serial.print("0");}
  if(digitalRead(d_a) == HIGH) {Serial.print("1");}
  else {Serial.print("0");}      
  Serial.print("\r\n");
}
//A function to set all arduino outputs LOW
void out_reset() { 
  digitalWrite(d_d, LOW);
  digitalWrite(d_c, LOW);
  digitalWrite(d_b, LOW);
  digitalWrite(d_a, LOW);
}
//A function to run the testing, calls helper functions
void action() {
  int event = 0; //Variable for what the 'event' is, for evaluation purposes
  bool temp_fail = 0; //Non global so that all checks performed 
  sim_output();
  predict(event);
  delay(500);
  switch (event) { //Case statement based upon 'event' to check circuitry
    case 9:
       checks(temp_fail, 1, 1, 1, 0, 0, 1, 1);
       break;
    case 8:
       checks(temp_fail, 1, 1, 1, 1, 1, 1, 1);
       break;
     case 7:
       checks(temp_fail, 1, 1, 1, 0, 0, 0, 0);
       break;
     case 6:
       checks(temp_fail, 0, 0, 1, 1, 1, 1, 1);
       break;
     case 5:
       checks(temp_fail, 1, 0, 1, 1, 0, 1, 1);
       break;
    case 4:
       checks(temp_fail, 0, 1, 1, 0, 0, 1, 1);
       break;
     case 3:
       checks(temp_fail, 1, 1, 1, 1, 0, 0, 1);
       break;
     case 2:
       checks(temp_fail, 1, 1, 0, 1, 1, 0, 1);
       break;
     case 1:
       checks(temp_fail, 0, 1, 1, 0, 0, 0, 0);
       break;
     case 0:
        checks(temp_fail, 1, 1, 1, 1, 1, 1, 0);
        break;
     default:
        Serial.print ("Unknown error: event not defined in action()\r\n");
        temp_fail = 1;
  }
  if (temp_fail) {fail = 1;}
}
//A function to tell the user what the arduino outputs are read as, assigns the 'event' based on this
void predict(int &event) {
  event = 0;
  Serial.print("Predicted Output: ");
  if ((digitalRead(d_d) == LOW) && (digitalRead(d_c) == LOW) && 
  (digitalRead(d_b) == LOW) && (digitalRead(d_a) == LOW)) { //0000 -> 0
    Serial.print("0\r\n");
    Serial.print("d_d = 0\rd_c = 0\rd_b = 0\rd_a = 0\r\n");
    event = 0;
  }
  else if ((digitalRead(d_d) == LOW) && (digitalRead(d_c) == LOW) && 
  (digitalRead(d_b) == LOW) && (digitalRead(d_a) == HIGH)) { //0001 -> 1
    Serial.print("1\r\n");
    Serial.print("d_d = 0\rd_c = 0\rd_b = 0\rd_a = 1\r\n");
    event = 1;
  }
  else if ((digitalRead(d_d) == LOW) && (digitalRead(d_c) == LOW) && 
  (digitalRead(d_b) == HIGH) && (digitalRead(d_a) == LOW)) { //0010 -> 2
    Serial.print("2\r\n");
    Serial.print("d_d = 0\rd_c = 0\rd_b = 1\rd_a = 0\r\n");
    event = 2;
  }
  else if ((digitalRead(d_d) == LOW) && (digitalRead(d_c) == LOW) && 
  (digitalRead(d_b) == HIGH) && (digitalRead(d_a) == HIGH)) { //0011 -> 3
    Serial.print("3\r\n");
    Serial.print("q0 = 0\rq1 = 0\rq2 = 1\rq3 = 1\r\n");
    event = 3;
  }
  else if ((digitalRead(d_d) == LOW) && (digitalRead(d_c) == HIGH) && 
  (digitalRead(d_b) == LOW) && (digitalRead(d_a) == LOW)) { //0100 -> 4
    Serial.print("4\r\n");
    Serial.print("d_d = 0\rd_c = 1\rd_b = 0\rd_a = 0\r\n");
    event = 4;
  }
  else if ((digitalRead(d_d) == LOW) && (digitalRead(d_c) == HIGH) && 
  (digitalRead(d_b) == LOW) && (digitalRead(d_a) == HIGH)) { //0101 -> 5
    Serial.print("5\r\n");
    Serial.print("d_d = 0\rd_c = 1\rd_b = 0\rd_a = 1\r\n");
    event = 5;
  }
  else if ((digitalRead(d_d) == LOW) && (digitalRead(d_c) == HIGH) && 
  (digitalRead(d_b) == HIGH) && (digitalRead(d_a) == LOW)) { //0110 -> 6
    Serial.print("6\r\n");
    Serial.print("d_d = 0\rd_c = 1\rd_b = 1\rd_a = 0\r\n");
    event = 6;
  }
  else if ((digitalRead(d_d) == LOW) && (digitalRead(d_c) == HIGH) && 
  (digitalRead(d_b) == HIGH) && (digitalRead(d_a) == HIGH)) { //0111 -> 7
    Serial.print("7\r\n");
    Serial.print("d_d = 0\rd_c = 1\rd_b = 1\rd_a = 1\r\n");
    event = 7;
  }
  else if ((digitalRead(d_d) == HIGH) && (digitalRead(d_c) == LOW) && 
  (digitalRead(d_b) == LOW) && (digitalRead(d_a) == LOW)) { //1000 -> 8
    Serial.print("8\r\n");
    Serial.print("d_d = 1\rd_c = 0\rd_b = 0\rd_a = 0\r\n");
    event = 8;
  }
  else if ((digitalRead(d_d) == HIGH) && (digitalRead(d_c) == LOW) && 
  (digitalRead(d_b) == LOW) && (digitalRead(d_a) == HIGH )) { //1001 -> 9
    Serial.print("9\r\n");
    Serial.print("d_d = 1\rd_c = 0\rd_b = 0\rd_a = 1\r\n");
    event = 9;
  }
  else {
    Serial.print("Unknown event: ERROR\r\n");
    fail = 1;
  }
}
//Checks if the readings from the output pins match the prdicted values
void checks(bool &temp_fail, int a_pin, int b_pin, int c_pin, int d_pin, int e_pin, int f_pin, int g_pin) {
  if ((a_pin == 1) && (digitalRead(o_a) == LOW)) {
    Serial.print("A is LOW. "
    "Pin 13 -> should be 1\r\n");    
    temp_fail = 1;
  }
  else if ((a_pin == 0) && (digitalRead(o_a) == HIGH)){
    Serial.print("A is HIGH. "
    "Pin 13 -> should be 0\r\n");
    temp_fail = 1;
  }
  if ((b_pin == 1) && (digitalRead(o_b) == LOW)) { 
    Serial.print("B is LOW. "
    "Pin 12 -> should be 1\r\n");    
    temp_fail = 1;
  }
  else if ((b_pin == 0) && (digitalRead(o_b) == HIGH)){
    Serial.print("B is HIGH. "
    "Pin 12 -> should be 0\r\n");
    temp_fail = 1;
  }  
  if ((c_pin == 1) && (digitalRead(o_c) == LOW)) {
    Serial.print("C is LOW. "
    "Pin 11 -> should be 1\r\n");    
    temp_fail = 1;
  }
  else if ((c_pin == 0) && (digitalRead(o_c) == HIGH)){
    Serial.print("C is HIGH. "
    "Pin 11 -> should be 0\r\n");
    temp_fail = 1;
  }  
  if ((d_pin == 1) && (digitalRead(o_d) == LOW)) {
    Serial.print("D is LOW. "
    "Pin 10 -> should be 1\r\n");  
    temp_fail = 1;
  }
  else if ((d_pin == 0) && (digitalRead(o_d) == HIGH)){
    Serial.print("D is HIGH. "
    "Pin 10 -> should be 0\r\n");
    temp_fail = 1;    
  }
  if ((e_pin == 1) && (digitalRead(o_e) == LOW)) {
    Serial.print("E is LOW. "
    "Pin 9 -> should be 1\r\n");  
    temp_fail = 1;
  }
  else if ((e_pin == 0) && (digitalRead(o_e) == HIGH)){
    Serial.print("E is HIGH. "
    "Pin 9 -> should be 0\r\n");
    temp_fail = 1;    
  }
  if ((f_pin == 1) && (digitalRead(o_f) == LOW)) { 
    Serial.print("F is LOW. "
    "Pin 15 -> should be 1\r\n");  
    temp_fail = 1;
  }
  else if ((f_pin == 0) && (digitalRead(o_f) == HIGH)){ 
    Serial.print("F is HIGH. "
    "Pin 15 -> should be 0\r\n");
    temp_fail = 1;    
  }
  if ((g_pin == 1) && (digitalRead(o_g) == LOW)) {
    Serial.print("G is LOW. "
    "Pin 14 -> should be 1\r\n"); 
    temp_fail = 1;
  }
  else if ((g_pin == 0) && (digitalRead(o_g) == HIGH)){ 
    Serial.print("G is HIGH. "
    "Pin 14 -> should be 0\r\n");
    temp_fail = 1;    
  }    
}
//When either the test has failed or all tests have ran, this function is called, effectively ending testing
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
