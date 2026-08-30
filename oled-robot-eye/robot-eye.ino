#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Wire.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

enum EyesState {NORMAL, SCARED};

class MotionSensing{
private:
  const int irPin;
  bool detected;
public:
  MotionSensing(int ir) : irPin(ir), detected(false){}

  void begin(){
    pinMode(irPin, INPUT);
  }

  void update(){
   detected = digitalRead(irPin);
  }

  bool isDetected() const {
    return detected;
  }

};

class OledEyes{
private:
  Adafruit_SSD1306 oled;
  EyesState currentState = NORMAL;
  MotionSensing& sense;

  const int baseW = 30;
  const int baseH = 35;
  const int rad = 8;
  const int eyeGap = 25;

  int currentH = 35;
  int targetX = 0;
  int targetY = 0;
  int currentX = 0;
  int currentY = 0;

  unsigned long lastBlinkTime = 0;
  unsigned long lastLookTime = 0;
  int blinkInterval = 3000;
  int lookInterval = 2000;

  bool isBlinking = false;
  int blinkState = 0;

public:
  OledEyes(MotionSensing& sensed) : oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1), sense(sensed){}

  void begin(){
    Wire.begin(21, 22);
    oled.begin(SSD1306_SWITCHCAPVCC, 0x3c);
    oled.clearDisplay();
    oled.display();

  }

  void drawNormal(){
    oled.clearDisplay();

    int leftCenterX = (SCREEN_WIDTH / 2) - (baseW) - (eyeGap / 2) + currentX;
    int rightCenterX = (SCREEN_WIDTH / 2) + (eyeGap / 2) + currentX;
    int centerY = (SCREEN_HEIGHT / 2) - (currentH / 2) + currentY;

    oled.fillRoundRect(leftCenterX, centerY, baseW, currentH, rad, WHITE);
    oled.fillRoundRect(rightCenterX, centerY, baseW, currentH, rad, WHITE);
    oled.display();

  }

  void drawScared(){
    oled.clearDisplay();

    int scaRad = 20;
    int scaPup = 8;

    int circLeftCenterX = (SCREEN_WIDTH / 2) - (scaRad) - (eyeGap / 2) + currentX;
    int circRightCenterX = (SCREEN_WIDTH / 2) + (scaRad) + (eyeGap / 2) + currentX;
    int centerY = (SCREEN_HEIGHT / 2)+ currentY;

    oled.drawCircle(circLeftCenterX, centerY, scaRad, WHITE);
    oled.fillCircle(circLeftCenterX, centerY, scaPup, WHITE);

    oled.drawCircle(circRightCenterX, centerY, scaRad, WHITE);
    oled.fillCircle(circRightCenterX, centerY, scaPup, WHITE);

    oled.display();
  }

  void update(){
    unsigned long now = millis();

    if (sense.isDetected()){
      currentState = SCARED;
    } else {
      currentState = NORMAL;
    }

    if (currentState == SCARED){
      scaredBehavior();
    } else {
      normalBehavior(now);
    }

    currentX += (targetX - currentX) * 0.3;
    currentY += (targetY - currentY) * 0.3;

    if (currentState != SCARED){
      handleBlink(now);
    } else {
      currentH = 35;
    }

    if (currentState == SCARED){
      drawScared();
    } else {
      drawNormal();
    }
  }
private:
  void normalBehavior(unsigned long now){
    if (now - lastLookTime > lookInterval && !isBlinking){
      lastLookTime = now;
      lookInterval = random(1500,4000);

      targetX = random(-25, 25);
      targetY = random(-15, 15);
    }
  }

  void scaredBehavior(){
    targetX = random(-8, 10);
    targetY = random(-8, 10);
  }

  void handleBlink(unsigned long now){
    if (!isBlinking && (now - lastBlinkTime > blinkInterval)){
      isBlinking = true;
      lastBlinkTime = now;
      blinkInterval = random(2000, 6000);
    }

    if (isBlinking){
      if (blinkState == 0){
        currentH -= 6;
        if (currentH <= 2){
          currentH = 2;
          blinkState = 1;
        }
      } else if (blinkState == 1){
        currentH += 6;
        if (currentH >= baseH){
          currentH = baseH;
          blinkState = 0;
          isBlinking = false;
        }
      }
    }
  }
};

MotionSensing motion(18);
OledEyes eyes(motion);

void setup(){
  motion.begin();
  eyes.begin();
}

void loop(){
  motion.update();
  eyes.update();
  delay(16);
}
