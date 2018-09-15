//To test if an inverter is working
//**Globals**
//Flags
int tests = 0;
bool fail = 0;
//Pins Out
int input_chip = 5; //Output from arduino, input to chip (4069)
//Pins In
int output_chip = 7; //Input to arduino, output from chip (4069) (inverter output)

//Performing setup for tests
void setup() {
  Serial.begin(9600);
  Serial.print("Beginning Setup\r\n");
  pinMode(input_chip, OUTPUT);
  delay(100);
  out_reset();
  pinMode(output_chip, INPUT);
  Serial.print("Running Tests\r\n");
}
//Looped code for testing
void loop() {
  if (!fail && tests < 3) { //Code in here should only run while not failed and less than 3 tests ran
    if (tests == 0 || tests == 2) 
      test_high();
    else //tests == 2
      test_low();

    out_reset();
    tests++;
  }
  else {test_finish();}
}
//Function to test Inverter on HIGH input
void test_high() {
  digitalWrite(input_chip, HIGH);
  delay(10);
  if (digitalRead(output_chip) == HIGH) {
    Serial.print("Input HIGH not inverted to LOW\n");
    fail = 1;
  }
}
//Function to test Inverter on LOW input
void test_low() {
  digitalWrite(input_chip, LOW);
  delay(10);
  if (digitalRead(output_chip) == LOW) {
    Serial.print("Input LOW not inverted to HIGH\n");
    fail = 1;
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
    Serial.print("Make sure to check the wiring In and Out of the Inverter\r\n");
  }
  else {Serial.print("Test success\r\n");}
  Serial.print("Testing ended after: ");
  Serial.print(tests);
  Serial.print("/2 runs\r\n");
  Serial.end();
  for(;;); //Inifinite loop so program stays here
}
