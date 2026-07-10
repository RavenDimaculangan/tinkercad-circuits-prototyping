// Library for LCD I2C
#include <LiquidCrystal_I2C.h>

// Define pins
#define bttn1Pin 2 // Set bttn1Pin to Pin 2.
#define bttn2Pin 3 // Set bttn2Pin to pin 3.
const int L1Up = 11; // Set L1Up to Pin 11.
const int L2Down = 12; // Set L2Down to Pin 12.
int segments[] = {4, 5, 6, 7, 8, 9, 10}; // Set segments A-G to Pins 4-10.

// Initialize LCD 
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Define volatiles to tell the compiler that the value can change at anytime quickly.
volatile bool bttn1UpFlag = false;    // Flag for bttn1Pin press.
volatile bool bttn2DownFlag = false;  // Flag for bttn2Pin press.

volatile int count = 0;  // Initial value for count.

// Logic for common Anode 7seg.
byte digitPattern[10][7] = {
  {0, 0, 0, 0, 0, 0, 1}, // 0
  {1, 0, 0, 1, 1, 1, 1}, // 1
  {0, 0, 1, 0, 0, 1, 0}, // 2
  {0, 0, 0, 0, 1, 1, 0}, // 3
  {1, 0, 0, 1, 1, 0, 0}, // 4
  {0, 1, 0, 0, 1, 0, 0}, // 5
  {0, 1, 0, 0, 0, 0, 0}, // 6
  {0, 0, 0, 1, 1, 1, 1}, // 7
  {0, 0, 0, 0, 0, 0, 0}, // 8
  {0, 0, 0, 0, 1, 0, 0}  // 9
};

void setup() {
  // Initialize LCD
  lcd.init();
  lcd.backlight(); // Turn on the backlight
  
  // Set bttn1Pin and bttn2Pin as inputs and L1Up and L2DOwn as outputs.
  pinMode(bttn1Pin, INPUT_PULLUP);
  pinMode(bttn2Pin, INPUT_PULLUP);
  pinMode(L1Up, OUTPUT);
  pinMode(L2Down, OUTPUT);


  // Set segments A-G as outputs
  for (int i = 0; i < 7; i++) {
    pinMode(segments[i], OUTPUT);
  }


  // Set all LEDs to OFF state
  digitalWrite(L1Up, LOW);
  digitalWrite(L2Down, LOW);


  // Display initial value "0" on the 7-segment display
  display(count);


  // attachInterrupt for bttn1Pin.
  attachInterrupt(digitalPinToInterrupt(bttn1Pin), countUp, RISING); /* Interrupting using Pin2. Third argument could be RISING, FALLING, CHANGE, and LOW. 
                                                                        RISING just fits well that's why it is used. */



  // Setup Timer0 for SW2 detection (Decrease count)
  noInterrupts();          // Disable all interrupts
  TCCR0A = 0;              
  TCCR0B = 0;              
  TCNT0 = 0;               
  OCR0A = 124;             // To set the compare match value for Timer0 in CTC mode.
  TCCR0A |= (1 << WGM01);  // To enable CTC mode (Clear Timer on Compare Match).
  TCCR0B |= (1 << CS02);   // Set prescaler to 256.
  TIMSK0 |= (1 << OCIE0A); // Enable Timer0 compare match interrupt.
  
  interrupts();            // Enable all interrupts again
}


void loop() {
  
  updateDisplay(); // Calles function for displaying states on LCD.
  // Check if bttn1Pin was pressed.
  if (bttn1UpFlag) {
    bttn1UpFlag = false;  // Reset flag after detecting press
    digitalWrite(L1Up, HIGH); // To Turn L1Up ON.
    digitalWrite(L2Down, LOW); // To turn L2Down OFF.
    count = (count + 1) % 10; // Increase count from 0-9 and back to 0 when count>9.
    display(count); // Update 7-segment display
    delay(300);  
  }


  // Check if bttn2Pin was pressed.
  if (bttn2DownFlag) {
    bttn2DownFlag = false;  // For reseting the flag after press detection.
    digitalWrite(L1Up, LOW);  // To Turn L1Up OFF.
    digitalWrite(L2Down, HIGH); // To turn L2Down ON.
    count = (count == 0) ? 0 : (count - 1); // Decrease count if count>0 and keeps it at 0 when count==0.
    display(count); // Update 7-segment display.
    delay(300); 
  }
}


// Function to call on attachInterrupt.
void countUp() {
  bttn1UpFlag = true; // To set flag bttn1UpFlag as true.
}


// Timer0 for btt2Down (compare).
ISR(TIMER0_COMPA_vect) {
  static bool lastButtonState = HIGH; // Initially set to not pressed.
  bool currentButtonState = digitalRead(bttn2Pin); // Reads the current state of bttn2Pin.


  // To detect button press. 
  if (lastButtonState == HIGH && currentButtonState == LOW) {
    bttn2DownFlag = true;  // Register button press as true.
  }


  lastButtonState = currentButtonState;  // To update the last button state as current.
}


// Function to call for displaying number on 7seg display.
void display(int digit) {
  for (int i = 0; i < 7; i++) {
    digitalWrite(segments[i], digitPattern[digit][i]); // To check values inside arrays segments and digitPattern.
  }
}

void updateDisplay(){

  // To display status of the switches and LEDs
  lcd.setCursor(0, 0); // Set cursor to the first column, first row
  lcd.print("S1: ");
  if(digitalRead(bttn1Pin) == HIGH){
    lcd.print("ON ");
  }else{
    lcd.print("OFF ");
  }
  lcd.print("S2: ");
  if(digitalRead(bttn2Pin) == HIGH){
    lcd.print("ON ");
  }else{
    lcd.print("OFF ");
  }
  
  lcd.setCursor(0, 1); // Set cursor to the first column, second row
  lcd.print("Lu: ");
  if(digitalRead(L1Up) == HIGH){
    lcd.print("ON ");
  }else{
    lcd.print("OFF ");
  }
  lcd.print("Ld: ");
  if(digitalRead(L2Down) == HIGH){
    lcd.print("ON ");
  }else{
    lcd.print("OFF ");
  }
}