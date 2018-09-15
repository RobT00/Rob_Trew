//Code to test the monostables
//Tests the 4538 (measures pulse length) and intermediate wiring
//**Globals**
//Testing Flags
bool fail = 0;
int tests = 0;
int test_time = 180; //"active" duration of monostable, in milliseconds
//Options are 180ms (HIGH) [goes to seconds block] or 130ms (LOW) [goes to hours,mins block] -> matches design spec
//Setting test_time to anything else will cause the pulse length and level to be recorded
short tolerance = 10; //Value (in ms) for time (+/-) of measured time that is acceptable
//Clock 
int count = 0;
//Pins Out
int input_chip = 3; //Output from arduino, input to chip (4538)
//Pins In
int output_chip = 7; //Input to arduino, output from chip (4538)

//Performing setup for tests
void setup() {
  Serial.begin(9600);
  Serial.print("Beginning Setup\r\n");
  Serial.print("Expected pulse length: ");
  Serial.print(test_time);
  if (test_time == 180) {
    Serial.print("ms, pulse should be HIGH for this duration\n");
  }
  else if (test_time == 130) {
    Serial.print("ms, pulse should be LOW for this duration\n");
  }
  else {
    Serial.print("ms\nUnknown test conditions\n");
  }
  pinMode(input_chip, OUTPUT);
  delay(10);
  out_reset();
  pinMode(output_chip, INPUT);
  Serial.print("Running Tests\r\n");
}

//Looped code for testing
void loop() {
  if (!fail && tests < 3) { //Code in here should only run while not failed and less than 3 tests ran
    delay(test_time + 5); //Allow chip (4538) to be at steady state (undisturbed)
    test();
    out_reset();
    tests++;
  }
  else {test_finish();}
}
//Function to perform testing on chip (4538)
void test() {
  if (test_time == 180) {
    //Expecting HIGH pulse of ~180ms
    if (digitalRead(output_chip) == HIGH) {
      Serial.print("Initial State is HIGH, should be LOW\n");
      fail = 1;
      return;
    }
    test_high();
  }
  else if (test_time == 130) { 
    //Expecting LOW pulse of ~130ms
    if (digitalRead(output_chip) == LOW) {
      Serial.print("Initial State is LOW, should be HIGH\n");
      fail = 1;
      return;
    }
    test_low();
  }
  else {
    Serial.print("Test time entered does not correspond\n");
    Serial.print("Initial state is: ");
    if (digitalRead(output_chip) == LOW) {
      Serial.print("LOW\n");
      test_high();
    }
    else { //Otherwise, if initial state is HIGH, measure LOW pulse length
      Serial.print("HIGH\n");
      test_low();
    }
  }
}
//Function to measure HIGH pulse length
void test_high() {
  int i = 0; //Variable to measure pulse length
  digitalWrite(input_chip, HIGH);
  delay(1);
  if (digitalRead(output_chip) == LOW) {
    Serial.print("Pulse has not switched to HIGH\n");
    fail = 1;
    return;
  }
  i++; //As a delay of 1ms has been called, increment timer by 1(ms)
  while (digitalRead(output_chip) == HIGH) { //While pulse is at expected state, increment count (timer) ever 1ms
    i++;
    delay(1);
  }
  Serial.print("Pulse remained HIGH for ");
  Serial.print(i);
  Serial.print("ms\n");
  //Allow for margin of error (+/- tolerance) for success, can be referenced with measured time if necessary
  if (i - tolerance > test_time || i + tolerance < test_time) {
    Serial.print("Pulse did not remain HIGH for desired duration of: ");
    Serial.print(test_time);
    Serial.print("ms\n");
    fail = 1;
    return;
  } 
}
//Function to measure LOW pulse length
void test_low() {
  int i = 0; //Variable to measure pulse length
  digitalWrite(input_chip, HIGH);
  delay(1);
  if (digitalRead(output_chip) == HIGH) {
    Serial.print("Pulse has not switched to LOW\n");
    fail = 1;
    return;
  }
  i++; //As a delay of 1ms has been called, increment timer by 1(ms)
  while (digitalRead(output_chip) == LOW) { //While pulse is at expected state, increment count (timer) ever 1ms
    i++;
    delay(1);
  }
  Serial.print("Pulse remained LOW for ");
  Serial.print(i);
  Serial.print("ms\n");
  //Allow for margin of error (+/- toleramce) for success, can be referenced with measured time if necessary
  if (i - tolerance > test_time || i + tolerance < test_time) {
    Serial.print("Pulse did not remain LOW for desired duration of: ");
    Serial.print(test_time);
    Serial.print("ms\n");
    fail = 1;
    return;
  }  
}
//A function to set all arduino outputs LOW
void out_reset() {
  digitalWrite(input_chip, LOW);
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
