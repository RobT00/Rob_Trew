//Tests the Seconds Block
//Code to test displays for seconds
//Test for 4029s, 4511s, 7segment displays and wiring
//Run from 0 - 60 (59)
//**Globals**
//Testing Flags
bool fail = 0;
int tests = 0;
//Clock 
int count = 0;
int tens = 0; // i.e. if time should be 0x, 1x, 2x, etc.
//Pins Out
int clk = 2; //Clock signal into first 4029 (units)
int preset = 5; //Pulse to trigger preset enable (reset) of 4029s
//Pins In
int carry = 15; //Carry out between 4029s

//Performing setup for tests
void setup() {
  Serial.begin(9600);
  Serial.print("Beginning Setup\r\n");
  pinMode(clk, OUTPUT);
  pinMode(preset, OUTPUT);
  digitalWrite(preset, HIGH);
  delay(100);
  out_reset();
  pinMode(carry, INPUT);
  Serial.print("Running Tests\r\n");
}
//Looped code for testing
void loop() {
  if (!fail && tests < 3) { //Code in here should only run while not failed and less than 3 tests ran
    for (tens = 0; tens <= 6; tens++) {
      for (count = 0; count <= 9; count++) {
        Serial.print("\r\n**Count: ");
        Serial.print(count);
        Serial.print(" **\r\n");
        action();
        delay(1000);
        out_reset();
        if (fail) {break;}
      }
    }
    tests++;
  }
  else {test_finish();}
}
//Main function for testing, calls helper functions
void action() {
  int event = 0; //Variable for what the 'event' is, for evaluation purposes
  bool temp_fail = 0; //Non global so that all checks performed 
  next_state();
  predict(event);
  delay(500);
  switch (event) { //Case statment to choose arguments for checking output, based upon 'event'
    case 2:
       checks(temp_fail, 1, 1, 0);
       break;
    case 1:
       checks(temp_fail, 1, 0, 1);
       break;
     case 0:
       checks(temp_fail, 1, 0, 0);
       break;
     default:
        Serial.print ("Unknown error: event not defined in action()\r\n");
        temp_fail = 1;
  }
  if (temp_fail) {fail = 1;}
}
//Checks if the readings from the output pins match the prdicted values
void checks (bool &temp_fail, int clock_p, int preset_p, int carry_p) {
  if (preset_p && digitalRead(preset) == LOW) {
    Serial.print("Preset Enable not triggered\r\n");
    temp_fail = 1; 
  }
  else if (!preset_p && digitalRead(preset) == HIGH) {
    Serial.print ("Preset Enable triggered early\r\n");
    temp_fail = 1;
  }
  if (clock_p && digitalRead(clk) == LOW) {
    Serial.print ("Clock not HIGH\r\n");
    temp_fail = 1;
  }
  if (carry_p && digitalRead(carry == HIGH)) { //Carry out is active LOW
    Serial.print("Carry out should be LOW (Active LOW)\r\n");
    temp_fail = 1;
  }
  else if (!carry_p && digitalRead(carry) == LOW) {
    Serial.print("Carry out should be HIGH (Active LOW)\r\n");
    temp_fail = 1;
  }
}
//A function to tell the user what the arduino outputs are read as, assigns the 'event' based on this
void predict(int &event) {
  event = 0;
  if (digitalRead(clk) == HIGH) { //clk should be HIGH, as 4029 increments count on rising edge
    Serial.print("Predicted Output: ");
    if (tens < 6) {
      switch (count) {
        //cases 0 - 8 are handled in the same manner
        case 0: 
        case 1: 
        case 2: 
        case 3: 
        case 4: 
        case 5: 
        case 6: 
        case 7: 
        case 8:
          Serial.print((tens * 10) + count);
          Serial.print("\r\n");
          event = 0;
          break;
        case 9:
          Serial.print((tens * 10) + count);
          Serial.print("\r\n");
          event = 1;
          break;
        default:
          Serial.print("Unknown event: ERROR\r\n");
          fail = 1;
        }
    }
      else if (digitalRead(preset) == HIGH) {
        Serial.print((tens * 10) + count);
        Serial.print("\r\n");
        event = 2;
      }
      else {
        Serial.print("Unknown event: ERROR\r\n");
        fail = 1;        
      }
  }
  else {
    Serial.print("Unknown event: ERROR\r\n");
    fail = 1;
  }
}
//Function to increment 4029 count and trigger reset (if necessary)
void next_state() {
  Serial.print("Generating chip output\r\n");
  digitalWrite(clk, HIGH);
  if (tens == 6 && count == 0) {digitalWrite(preset, HIGH);}
}
//A function to set all arduino outputs LOW
void out_reset() {
  digitalWrite(clk, LOW);
  digitalWrite(preset, LOW);
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

