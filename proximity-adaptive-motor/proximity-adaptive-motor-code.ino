 // Libraries needed
#include <Wire.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // LCD_I2C address
Servo myservo; // Servo object

const int servoPin = 11; // Pin number for Servo signal

// Pin numbers for Ultrasonic sensor
const int trigPin = 9;
const int echoPin = 10;

const int IrOut = 2; // Pin number for IR proximity sensor

// Pin number for Motor driver
const int in1 = 3;  
const int in2 = 4; 
const int ena = 5;

// Initialize states
int motorSpeed = 0;
int sensorState = 0;

void setup(){
  Serial.begin(9600); // Begin serial monitor at baud 9600
  Serial.print("System Ready."); // Print on serial monitor

  myservo.attach(servoPin); // To link Servo signal pin with the object "myservo"

  lcd.init(); // Initialize lcd (begin)
  lcd.backlight(); // Turn on lcd backlight 
  lcd.print("System Ready."); // Print on lcd once
  delay(3000); // 3seconds delay
  lcd.clear(); // Clear lcd for the loop prints

  // Pin Modes
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(ena, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(IrOut, INPUT);


}

void loop(){
  
  sensorState = digitalRead(IrOut);
  
  Motor();
  IR();

  

  delay(100); // Small delay


}

void IR(){
  
  lcd.setCursor(0,1);
  lcd.print("Item:                       ");
  
  
  if(sensorState == 1){
    
    lcd.setCursor(6,1);
    lcd.println("Tall.");
    
    myservo.write(45);
    delay(3000);
    myservo.write(0);
    
    
    
  } else {
    lcd.setCursor(6,1);
    lcd.print("Short.");
    
    myservo.write(0);
    
  }
}

void Motor(){
  
  long duration, distance; 
  
  // To start trig on sending pulses
  digitalWrite(trigPin, LOW); // Off Trigger at start for 2 us (to avoid error on echo)
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); // On for 10 us
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);// Off again

  
  duration = pulseIn(echoPin, HIGH); // Read the pulse duration from Echo

  distance = duration * 0.0344 / 2; /*Convert time (duration) to distance 
                                      (343 m/s = 34,300 cm/s = 0.0343 cm/us * duration (us) 
                                       so that us will be cancelled then divide by 2
                                       because it goes and back)*/ 
  
  // Print on serial monitor
  
  Serial.print("Distance: "); Serial.print(distance);
  Serial.println(" cm");
 
   
  lcd.setCursor(0,0); // Set cursor on lcd column 0, row 0
  lcd.print("Distance:                         "); // Print on lcd
  lcd.setCursor(10,0); // Set cursor on lcd column 10, row 0 (based on "Distance" characters)
  lcd.print(distance); // Print the detected distance on lcd
  lcd.print(" cm"); // Unit of the distance in cm
  
  if(distance <= 20){ 
    // Motor is off when object's distance detected by Ultrasonic is <=20 cm
    analogWrite(ena, 0); 
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);

  } else if(distance > 20 && distance <= 100){
    // Motor speed is mapped for smooth speed transition/regulation based on object's distance detected by Ultrasonic
    motorSpeed = map(distance, 20, 100, 55, 255);
    analogWrite(ena, motorSpeed);
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);

  } else {
    // Motor at full speed when Ultrasonic detects no object within its set range
    analogWrite(ena, 255);
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  }
}
