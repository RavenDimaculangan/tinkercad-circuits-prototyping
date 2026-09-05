#include <Wire.h>
#include <SPI.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <WebServer.h> 
#include <WiFi.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

const char* ssid = "Wokwi-GUEST"; //BIDA_2A3D (my wifi name)
const char* password = "";

//Machine Status monitoring
class St_Monitoring{
private:
  const int machineStart; //Simulated switch for machine start
  bool machineState;

  unsigned long totalOnTimeMs = 0;
  unsigned long totalOffTimeMs = 0;
  unsigned long lastUpdateMs = 0;

public:
  St_Monitoring(int machine) : machineStart(machine), machineState(false){}

  void begin(){
    pinMode(machineStart, INPUT);
    lastUpdateMs = millis();
  }

  void machineOn(){
    unsigned long now = millis();
    unsigned long elapsedTime = now - lastUpdateMs;
    lastUpdateMs = now;
    
    machineState = digitalRead(machineStart);

    if (machineState){
      totalOnTimeMs += elapsedTime;
    } else {
      totalOffTimeMs += elapsedTime;
    }

  }
  bool isMachineOn() const{
    return machineState;
  }

  unsigned long getSeconds() const {
    return (totalOnTimeMs / 1000) % 60;
  }
  unsigned long getMinutes() const {
    return (totalOnTimeMs / 60000) % 60;
  }
  unsigned long getHours() const {
    return totalOnTimeMs / 3600000;
  }

  String getFormattedUpdateTime() const {
    char buffer[12];
    snprintf(buffer, sizeof(buffer), "%02lu:%02lu:%02lu", getHours(), getMinutes(), getSeconds());
    return String(buffer);
  }

};

class Ct_Monitoring{
private:
  int crimpPin; //Simulated push button for crimping
  int crimpCount = 0;
  bool lastBtnState = LOW;

  St_Monitoring& mntor;

public:
  Ct_Monitoring(int crimp, St_Monitoring& monitor) : crimpPin(crimp), mntor(monitor){}


  void begin(){
    pinMode(crimpPin, INPUT);
  }

  void startCount(){
    if (mntor.isMachineOn()){
      bool currentBtnState = digitalRead(crimpPin);
      if (lastBtnState == HIGH && currentBtnState == LOW){
        crimpCount++;
      }
      lastBtnState = currentBtnState;
    }
  }
  int getCount() const{
    return crimpCount;
  }
};

class OledDisplay{
private:
  Adafruit_SSD1306 oled;
  St_Monitoring& mntor;
  Ct_Monitoring& cwntr;
  unsigned long lastDisplayUpdate = 0;

public:
  OledDisplay(St_Monitoring& m, Ct_Monitoring& c) : oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1), mntor(m), cwntr(c){}

  void begin(){
    Wire.begin(21, 22);
    oled.begin(SSD1306_SWITCHCAPVCC, 0x3c);
    oled.clearDisplay();
    oled.display();
  }

  void update(){
    if (millis() - lastDisplayUpdate >= 250){
      lastDisplayUpdate = millis();
      oledChars();
    }
  }

private:
  void oledChars(){
    oled.clearDisplay();
    oled.setTextSize(1);
    oled.setTextColor(WHITE);

    oled.setCursor(0, 0);
    oled.println("LINE 1: CRIMP STATION");
    oled.drawLine(0, 10, 128, 10, WHITE);

    oled.setCursor(0, 18);
    oled.print("STATUS: ");
    if(mntor.isMachineOn()){
      oled.println("RUNNING");
    } else {
      oled.println("STOPPED");
    }

    oled.setCursor(0, 32);
    oled.print("ON TIME: ");
    oled.println(mntor.getFormattedUpdateTime());

    oled.setCursor(0, 46);
    oled.print("CYCLES: ");
    oled.println(cwntr.getCount());
    oled.print(" pcs");

    oled.display();
  }
};
//webServer
class WebDashboard{
private:
  WebServer myServer;
  St_Monitoring& mntor;
  Ct_Monitoring& cwntr;

public:
  WebDashboard(St_Monitoring& m, Ct_Monitoring& c) : myServer(80), mntor(m), cwntr(c){}

  void begin(){
    myServer.on("/", [this]() { handleRoot(); });
    myServer.begin();
    Serial.println("HTTP WebServer Started.");
  }

  void startServer(){
    myServer.handleClient();
  }

private:
  void handleRoot(){
    String html = "<!DOCTYPE html><html><head>";
    html += "<meta http-equiv='refresh' content='2'>";
    html += "<title> RAE SCADA NODE</title>";

    html += "<style>";
    html += "body { font-family: Arial, sans-serif; background: #121212; color: #fff; text-align: center; margin-top: 40px; }";
    html += ".card { background: #1e1e1e; display: inline-block; padding: 20px; margin: 10px; border-radius: 10px; min-width: 180px; box-shadow: 0 4px 8px rgba(0,0,0,0.3); }";
    html += ".status-run { color: #4caf50; font-weight: bold; }";
    html += ".status-stop { color: #f44336; font-weight: bold; }";
    html += "</style></head><body>";

    html += "<h1>RAE - Micro-SCADA Node</h1>";
    html += "<h3>Line 1: Wire Crimp Station</h3>";

    html += "<div class='card'><h3>Status</h3><h2>";
    if (mntor.isMachineOn()){
      html += "<span class='status-run'>RUNNING</span>";
    } else {
      html += "<span class='status-stop'>STOPPED</span>";
    }
    html += "</h2></div>";

    html += "<div class='card'><h3>Active Run Time</h3><h2>";
    html += String(mntor.getFormattedUpdateTime());
    html += "</h2></div>";

    html += "<div class='card'><h3>Total Output</h3><h2>";
    html += String(cwntr.getCount());
    html += " pcs</h2></div>";

    html += "</body></html>";

    myServer.send(200, "text/html", html);
  }

};

St_Monitoring machine(16);
Ct_Monitoring counter(33, machine);
OledDisplay display(machine, counter);
WebDashboard dashboard(machine, counter);

void setup(){
  Serial.begin(115200);

  machine.begin();
  counter.begin();
  display.begin();


  WiFi.begin(ssid, password);
  Serial.print("connecting to WiFi");

  while (WiFi.status() !=  WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi.");
  Serial.print("IP Address: "); Serial.println(WiFi.localIP());

  dashboard.begin();
}

void loop(){
  machine.machineOn();
  counter.startCount();
  display.update();
  dashboard.startServer();
  delay(1);
}
