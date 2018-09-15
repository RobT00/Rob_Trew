//Code to test the Minute Marker
//Tests 4094, 4068 and intermediate wiring
//Sends 000_01111110 (bits after '_' is minute marker code)
//**Globals**
int SIZE = 11; //Array size for bitstream
//Testing Flags
bool fail = 0;
int tests = 0;
//Clock
int count = 0;
//Sending bits
int data[] = {0,0,0,0,1,1,1,1,1,1,0}; //Bitstream (contains minute marker)
//Pins Out
int data_pin = 3; //Pin for bitstream into 4094
int clk = 2; //Pin for clock signal into 4094
//Pins In
int and_out = 7; //Corresponds to output of AND Gate

//Performing setup for tests
void setup() {
  Serial.begin(9600);
  Serial.print("Beginning Setup\r\n");
  pinMode(data_pin, OUTPUT);
  pinMode(clk, OUTPUT);
  out_reset();
  pinMode(and_out, INPUT);
  Serial.print("Running Tests\r\n");
}
//Looped code for testing
void loop() {
  if (!fail && tests < 3) { //Code in here should only run while not failed and less than 3 tests ran
    //Run for all bits in array "data"
    for (int i = 0; i < SIZE; i++) {
      if (data[i] == 1) {digitalWrite(data_pin, HIGH);}
      delay(10);
      digitalWrite(clk, HIGH);
      delay(100);
      out_reset();
      if (i > 0 && digitalRead(and_out) == HIGH && (i + 1 != SIZE)) { //Using i+1 as when i = SIZE, exited loop
         Serial.print("Output of AND Gate is HIGH, but have only");
         Serial.print(" read in ");
         Serial.print(i + 1);
         Serial.print("/11 bits\n");
         fail = 1;
         break;
      }
    }
    //Output of AND Gate should be HIGH now
    if (digitalRead(and_out) == LOW && !fail) {
      fail = 1;
      Serial.print("Output of AND Gate is LOW ");
    }
    tests++;
  }
  else {
    test_finish();
  }
}
//A function to set all arduino outputs LOW
void out_reset() {
  digitalWrite(data_pin, LOW);
  digitalWrite(clk, LOW);
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
