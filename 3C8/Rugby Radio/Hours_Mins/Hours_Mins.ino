//Tests Hours and Minutes Block
//Code to test the wiring of The Hours and Minutes Displays
//Tests 4094s, by extension 4511 and 7segment displays (as well as wiring)
//Test Times 00:00, 12:34, 21:56 
//**Globals**
//Testing Flags
bool fail = 0;
int tests = 0;
//Clock
int count = 0;
//Pins Out
int data = 1; //Bitstream (i.e. from Rugby Signal)
int clk = 2; //Pin for clock signal into 4094
int enable = 3; //To trigger Strobe (Pin 1 on 4094) for output to displays
//Pins In
int h0 = 5; //Corresponds to label on Board, LSB of Tens of hours 
int h1 = 6; //Corresponds to label on Board, MSB of Tens of hours

//Performing setup for tests
void setup() {
  Serial.begin(9600);
  Serial.print("Beginning Setup\r\n");
  pinMode(data, OUTPUT);
  pinMode(data, LOW);
  pinMode(clk, OUTPUT);
  pinMode(enable, OUTPUT);
  digitalWrite(enable, HIGH);
  out_reset();
  pinMode(h0, INPUT);
  pinMode(h1, INPUT);
  Serial.print("Running Tests\r\n");
}
//Looped code for testing
void loop() {
  if (!fail && tests < 3) { //Code in here should only run while not failed and less than 3 tests ran
    action();
    delay(100);
    out_reset();
    tests++;
  }
  else {test_finish();}
}
//Main function for testing, calls helper functions
void action() {
  int event = 0; //Variable for what the 'event' is, for evaluation purposes
  bool temp_fail = 0; //Non global so that all checks performed 
  switch (tests) { //Case statement based upon 'tests' (i.e. which test we are on)
    case 0:
      zero();
      break;
    case 1:
      one();
      break;
    case 2:
      two();
      break;
    default:
      Serial.print ("Unknown error: event not defined in action()\r\n");
      fail = 1;
      return;
  }
  predict(event);
  delay(500);
  switch (event) { //Case statement based upon 'event' to check circuitry (event should match tests)
    case 0:
       checks(temp_fail, 0, 0);
       break;
    case 1:
       checks(temp_fail, 1, 0);
       break;
     case 2:
       checks(temp_fail, 0, 1);
       break;
     default:
        Serial.print ("Unknown error: event not defined in action()\r\n");
        temp_fail = 1;
  }
  if (temp_fail) {fail = 1;}
}
//Bitstream to set time to 00:00
void zero() {
  int arr[24] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  sim_output(arr);
}
//Bitstream to set time to 12:34
void one() { 
  int arr[24] = {0,0,0,1,0,0,1,0,0,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0};
  sim_output(arr);
}
//Bitstream to set time to 21:56
void two() { 
  int arr[24] = {0,0,1,0,0,0,0,1,1,0,1,0,1,1,0,0,0,0,0,0,0,0,0,0};
  sim_output(arr);
}
//A function to set the bitstream to the banks of 4094s (i.e. Rugby Signal)
void sim_output(int arr[]) {
    for (count = 0; count < 24; count++) {
    Serial.print("\r\n**Count: ");
    Serial.print(count);
    Serial.print(" **\r\n");
    if (arr[count]) {digitalWrite(data, HIGH);}
    delay(100);
    out_reset();
  }
  digitalWrite(enable, HIGH);
}
//A function to tell the user what the arduino outputs are read as, assigns the 'event' based on this
void predict(int &event) {
  event = 0;
  Serial.print("Predicted Output: ");
  if ((digitalRead(h0) == LOW) && (digitalRead(h1) == LOW)) { //00:00 -> 0
    Serial.print("00:00\r\n");
    event = 0;
  }
  else if ((digitalRead(h0) == HIGH) && (digitalRead(h1) == LOW)) { //12:34 -> 1
    Serial.print("12:34\r\n");
    event = 1;
  }
  else if ((digitalRead(h0) == LOW) && (digitalRead(h1) == HIGH)) { //21:56 -> 2
    Serial.print("21:56\r\n");
    event = 2;
  }
  else {
    Serial.print("Unknown event: ERROR\r\n");
    fail = 1;
  }
}
//Checks if the readings from the output pins match the prdicted values
void checks(bool &temp_fail, int h0_p, int h1_p) {
  if ((h0_p) && (digitalRead(h0) == LOW)) {
    Serial.print("h0 is LOW, should be HIGH -> 1\r\n");    
    temp_fail = 1;
  }
  else if (!(h0_p) && (digitalRead(h0) == HIGH)){
    Serial.print("h0 is HIGH, should be LOW -> 0\r\n");
    temp_fail = 1;
  }
  if ((h1_p) && (digitalRead(h1) == LOW)) { 
    Serial.print("h1 is LOW, should be HIGH -> 2\r\n");    
    temp_fail = 1;
  }
  else if (!(h1_p) && (digitalRead(h1) == LOW)){
    Serial.print("h1 is HIGH -> should be 0\r\n");
    temp_fail = 1;
  }      
}
//A function to set all arduino outputs LOW
void out_reset() {
  digitalWrite(clk, LOW);
  digitalWrite(data, LOW);
  digitalWrite(enable, LOW);
}
//When either the test has failed or all tests have ran, this function is called, effectively ending testing
void test_finish() {
  if (fail) {
    Serial.print("Test failure!\r\n");
    Serial.print("Be sure to check POWER and GROUND too\r\n");
    Serial.print("Check if the clock signal is being read in correctly\r\n");
    Serial.print("Check if strobe is being triggered correctly\r\n");
  }
  else {Serial.print("Test success\r\n");}
  Serial.print("Testing ended after: ");
  Serial.print(tests);
  Serial.print("/3 runs\r\n");
  Serial.end();
  for(;;); //Inifinite loop so program stays here
}
