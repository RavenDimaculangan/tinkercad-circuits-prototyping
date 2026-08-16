// Libraries used
#include <Servo.h>
#include <LiquidCrystal_I2C.h>

// Class for servo control to manage global cleanly
class ServoControl{
// To make member variables inaccessible from outside its class
private: 
  int _irPin;
  int _servoPin;
  int _servoAngle;
  
  bool _moved = false; // To track servo state
  bool _wasDetected = false; // To track ir reading for edge detection
  
  // Used for non-blocking delay instead of normal delay
  unsigned long _lastUp = 0; 
  const unsigned long _delay;
  
  Servo _myServo;
  
public:
  // Constructor: Initializes pins, movement angle, and hold duration
  ServoControl(int ir, int servo, int angle, int wait)
  :_irPin(ir), _servoPin(servo), _servoAngle(angle), _delay(wait){}
  
  // Hardware initialization
  void init(){
    _myServo.write(0); // To force servo to angle 0 at start
    _myServo.attach(_servoPin); // Attaches servo motor to PWM pin
    pinMode(_irPin, INPUT); // IR pin assignment 
  }
  
  // Block that holds the logic function for servo control
  void update(){
    int IR = digitalRead(_irPin);
    bool isDetected = IR; 
    // FTrig (servo only moves after IR state turns from HIGH to LOW)
    if (!isDetected && _wasDetected){
      _myServo.write(_servoAngle);
      _moved = true;
      _lastUp = millis(); // Records time when servo moved
    }
    // Servo state + non-blocking delay conditioning
    else if(_moved && millis() - _lastUp >= _delay){
      _myServo.write(0);
      _moved = false; // Reset state to prevent continuous write calls
    }
    _wasDetected = isDetected; // Saves current state for next loop
  }
  
  
};

// Class for buzzer control to manage global cleanly
class BuzzerControl{
// To make member variables inaccessible to outside class
private:
  int _buzzerPin;
public:
  // Constructor: Configures buzzer pin
  BuzzerControl(int buzz)
  :_buzzerPin(buzz){}
  // Hardware pin initialization
  void init(){
    pinMode(_buzzerPin, OUTPUT);
  }
  // Function called when Temp > Threshold
  void buzzing(){
    digitalWrite(_buzzerPin, HIGH); // Activate buzzer
  }
  // Function called when Temp < Threshold
  void stopBuzzing(){
    digitalWrite(_buzzerPin, LOW); // Deactivate buzzer
  }
  
};

// Class for temperature sensing and display control
class TempSensing{
// To make member variables inaccessible to outside class
private:
  const float V = 5.0;
  uint8_t _tempPin;
  
  BuzzerControl& _buzzFunc; // To be able to call a function from BuzzerControl class 
  
  int _lastFlat = -999; // To force LCD update once every Temp changes
  bool _wasOverTemp = false; // To track overtemp for edge detection
  
  LiquidCrystal_I2C _myLcd;
  
public:
  // Constructor: Initializes sensor pin, LCD address, and buzzer reference
  TempSensing(int temp, uint8_t lcdAdd, BuzzerControl& buzz)
  :_tempPin(temp), _myLcd(lcdAdd, 16, 2), _buzzFunc(buzz){}
  // Hardware initialization
  void init(){
    pinMode(_tempPin, INPUT);
    
    _myLcd.init();
    _myLcd.backlight();
    _myLcd.setCursor(0, 0);
    _myLcd.print("System is ready.");
    delay(3000); // Quick startup delay (blocking type)
    _myLcd.clear();
  }
  // Block that holds the logic function for Temperature sensing
  void update(){
    // Read raw ADC and calculate degrees Celsius (TMP36 Formula)
    int tempState = analogRead(_tempPin);
    float vTemp = tempState * (V/1023.0);
    float realTemp = (vTemp - 0.500) * 100.0;
    int flat = realTemp;
      
    bool isOverTemp = (flat >= 60); 
    // Rising Trigger, fires ONCE (LOW to HIGH)
    if (isOverTemp && !_wasOverTemp){
      _buzzFunc.buzzing();
      _myLcd.setCursor(0, 1);
      _myLcd.print("ALARM: OVERHEAT!");
    }
    // Falling Trigger, fires ONCE (HIGH to LOW)
    if (!isOverTemp && _wasOverTemp){
      _buzzFunc.stopBuzzing();
      _myLcd.setCursor(0, 1);
      _myLcd.print("TEMP NORMALIZED  ");
    }
    _wasOverTemp = isOverTemp; // Save previous state
    
    // State change display (updates once every temp changes to prevent LCD flickering)
    if (flat != _lastFlat){
      _myLcd.setCursor(0, 0);
      _myLcd.print("Temp:               ");
      _myLcd.setCursor(6, 0);
      _myLcd.print(flat);
      _myLcd.print(" degC");
      _lastFlat = flat; // Save current state for next loop
    }  
  }
};

// Object Instantiations (Assigning unique pins and timing configurations)
BuzzerControl buzzer1(9);
ServoControl servo1(2, 8, 90, 1000);
ServoControl servo2(4, 6, 45, 2000);
ServoControl servo3(7, 5, 100, 2000);
TempSensing sense1(A0, 0x27, buzzer1);

// Initialize hardware for all object instances
void setup(){
  buzzer1.init();
  sense1.init();
  servo1.init();
  servo2.init();
  servo3.init();
  
}
// Execute non-blocking task loops continuously
void loop(){
  servo1.update();
  servo2.update();
  servo3.update();
  sense1.update();
}
