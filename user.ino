#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FS.h>  // Filesystem library for SPIFFS
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

const char* ssid = "Vincas";
const char* password = "Vincas09";
 
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
ESP8266WebServer server(80);

const int pulseMin = 150;  // Minimum pulse length for 0 degree
const int pulseMax = 600;  // Maximum pulse length for 180 degree
const int maxRotations = 10;  // Max number of rotations per servo

int totalRotationsServo1 = 0;
int totalRotationsServo2 = 0;
int totalRotationsServo3 = 0;
int totalRotationsServo4 = 0;
int totalRotationsServo5 = 0;
int totalRotationsServo6 = 0;
int totalRotationsServo7 = 0;
int totalRotationsServo8 = 0;

const int servo1Channel = 0;
const int servo2Channel = 1;
const int servo3Channel = 2;
const int servo4Channel = 3;
const int servo5Channel = 4;
const int servo6Channel = 5;
const int servo7Channel = 6;
const int servo8Channel = 7;

void setup() {
  Serial.begin(115200);

  // Initialize SPIFFS
  if (!SPIFFS.begin()) {
    Serial.println("Failed to mount SPIFFS");
    return;
  }

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.print("ESP8266 IP Address: ");
  Serial.println(WiFi.localIP());

  pwm.begin();
  pwm.setPWMFreq(60);  // Set frequency to 60 Hz for servos

  // Define routes for serving files
  server.on("/", handleRoot);             // Serve index.html
  server.on("/page2.html", handlePage2);  // Serve page2.html
  server.on("/page3.html", handlePage3);  // Serve page3.html
  server.on("/page2.css", handlePage2CSS); // Serve page2.css
  server.on("/coinpay.html", handleCoinPay); // Serve coinpay.html
  server.on("/cashpay.html", handleCashPay); // Serve cashpay.html
  server.on("/dispense.html", handleDispense); // Serve dispense.html
  server.on("/lastpage.html", handleLastPage); // Serve lastpage.html
  server.on("/style.css", handleStyleCSS); // Serve style.css
  server.on("/slsu.png", handleImageSLSU);    // Serve images
  server.on("/celogo.png", handleImageCELogo);
  server.on("/coin.png", handleImagecoin);
  server.on("/cash.png", handleImagecash);
  server.on("/insertbill.jpg", handleImageinsertbill);
  server.on("/insertcoin.gif", handleGIFinsertcoin);
  server.on("/icpeplogo.png", handleImageICPEP);
  server.on("/control", handleControl); // Handle form submission for servo control

  server.begin();
  Serial.println("Server started");
}

void loop() {
  server.handleClient();
}

void handleRoot() {
  File file = SPIFFS.open("/index.html", "r");
  if (!file) {
    server.send(404, "text/plain", "File not found");
    return;
  }
  server.streamFile(file, "text/html");
  file.close();
}

void handlePage2() {
  File file = SPIFFS.open("/page2.html", "r");
  if (!file) {
    server.send(404, "text/plain", "File not found");
    return;
  }
  server.streamFile(file, "text/html");
  file.close();
}

void handlePage3() {
  File file = SPIFFS.open("/page3.html", "r");
  if (!file) {
    server.send(404, "text/plain", "File not found");
    return;
  }
  server.streamFile(file, "text/html");
  file.close();
}

void handleCoinPay() {
  File file = SPIFFS.open("/coinpay.html", "r");
  if (!file) {
    server.send(404, "text/plain", "File not found");
    return;
  }
  server.streamFile(file, "text/html");
  file.close();
}

void handleCashPay() {
  File file = SPIFFS.open("/cashpay.html", "r");
  if (!file) {
    server.send(404, "text/plain", "File not found");
    return;
  }
  server.streamFile(file, "text/html");
  file.close();
}

void handleDispense() {
  File file = SPIFFS.open("/dispense.html", "r");
  if (!file) {
    server.send(404, "text/plain", "File not found");
    return;
  }
  server.streamFile(file, "text/html");
  file.close();
}
void handleLastPage() {
  File file = SPIFFS.open("/lastpage.html", "r");
  if (!file) {
    server.send(404, "text/plain", "File not found");
    return;
  }
  server.streamFile(file, "text/html");
  file.close();
}

void handlePage2CSS() {
  File file = SPIFFS.open("/page2.css", "r");
  if (!file) {
    server.send(404, "text/plain", "File not found");
    return;
  }
  server.streamFile(file, "text/css");
  file.close();
}

void handleStyleCSS() {
  File file = SPIFFS.open("/style.css", "r");
  if (!file) {
    server.send(404, "text/plain", "File not found");
    return;
  }
  server.streamFile(file, "text/css");
  file.close();
}

void handleImageSLSU() {
  File file = SPIFFS.open("/slsu.png", "r");
  if (!file) {
    server.send(404, "text/plain", "Image not found");
    return;
  }
  server.streamFile(file, "image/png");
  file.close();
}
void handleGIFinsertcoin() {
  File file = SPIFFS.open("/insertcoin.gif", "r");
  if (!file) {
    server.send(404, "text/plain", "Image not found");
    return;
  }
  server.streamFile(file, "image/gif");
  file.close();
}

void handleImageinsertbill() {
  File file = SPIFFS.open("/insertbill.jpg", "r");
  if (!file) {
    server.send(404, "text/plain", "Image not found");
    return;
  }
  server.streamFile(file, "image/jpg");
  file.close();
}



void handleImageCELogo() {
  File file = SPIFFS.open("/celogo.png", "r");
  if (!file) {
    server.send(404, "text/plain", "Image not found");
    return;
  }
  server.streamFile(file, "image/png");
  file.close();
}

void handleImagecoin() {
  File file = SPIFFS.open("/coin.png", "r");
  if (!file) {
    server.send(404, "text/plain", "Image not found");
    return;
  }
  server.streamFile(file, "image/png");
  file.close();
}

void handleImagecash() {
  File file = SPIFFS.open("/cash.png", "r");
  if (!file) {
    server.send(404, "text/plain", "Image not found");
    return;
  }
  server.streamFile(file, "image/png");
  file.close();
}

void handleImageICPEP() {
  File file = SPIFFS.open("/icpeplogo.png", "r");
  if (!file) {
    server.send(404, "text/plain", "Image not found");
    return;
  }
  server.streamFile(file, "image/png");
  file.close();
}

// Handle servo control via web form
void handleControl() {
  if (server.hasArg("rotations") && server.hasArg("layout") && server.hasArg("program")) {
    int inputRotations = server.arg("rotations").toInt();
    String layoutChoice = server.arg("layout");
    String selectedProgram = server.arg("program"); // Capture program selection

    Serial.print("Total rotations requested: ");
    Serial.println(inputRotations);
    Serial.print("Selected layout: ");
    Serial.println(layoutChoice);
    Serial.print("Selected program: ");
    Serial.println(selectedProgram);

    // Process the request and allocate rotations
    allocateRotations(inputRotations, layoutChoice == "lined");
    
     // Redirect to page3.html after processing
    server.sendHeader("Location", "/page3.html");  // Set the redirect header
    server.send(303);  // 303 See Other response for redirection
  } else {
    server.send(400, "text/html", "Invalid Request. Please enter all fields.");
  }
}


// Allocate rotations based on the layout
void allocateRotations(int inputRotations, bool isLinedLayout) {
  int remainingRotations = inputRotations;
  int currentServo = 0;

  int* totalRotations[4];
  int servoChannels[4];

  // Handle "lined layout" using servos 1 to 4
  if (isLinedLayout) {
    totalRotations[0] = &totalRotationsServo1;
    totalRotations[1] = &totalRotationsServo2;
    totalRotations[2] = &totalRotationsServo3;
    totalRotations[3] = &totalRotationsServo4;
    servoChannels[0] = servo1Channel;
    servoChannels[1] = servo2Channel;
    servoChannels[2] = servo3Channel;
    servoChannels[3] = servo4Channel;
  }
  // Handle "unlined layout" using servos 5 to 8
  else {
    totalRotations[0] = &totalRotationsServo5;
    totalRotations[1] = &totalRotationsServo6;
    totalRotations[2] = &totalRotationsServo7;
    totalRotations[3] = &totalRotationsServo8;
    servoChannels[0] = servo5Channel;
    servoChannels[1] = servo6Channel;
    servoChannels[2] = servo7Channel;
    servoChannels[3] = servo8Channel;
  }

  // Rotation logic
  while (remainingRotations > 0) {
    int availableRotations = maxRotations - *totalRotations[currentServo];

    if (availableRotations > 0) {
      int rotationsToExecute = min(remainingRotations, availableRotations);

      for (int i = 0; i < rotationsToExecute; i++) {
        moveServo(servoChannels[currentServo], 0);
        delay(2000);
        yield();  // Give control back to prevent watchdog timer reset
        moveServo(servoChannels[currentServo], 90);
        Serial.print("Servo ");
        Serial.print(currentServo + 1);
        Serial.println(" rotating...");
        delay(2000);
        yield();  // Prevent watchdog reset
        (*totalRotations[currentServo])++;
      }

      remainingRotations -= rotationsToExecute;
    }

    // Move to the next servo and loop back after 4 servos
    currentServo = (currentServo + 1) % 4;
  }
}

// Move servo to a specific angle
void moveServo(int channel, int angle) {
  int pulseLength = map(angle, 0, 180, pulseMin, pulseMax); 
  pwm.setPWM(channel, 0, pulseLength); 
  Serial.print("Moving servo on channel: ");
  Serial.print(channel);
  Serial.print(" to angle: ");
  Serial.println(angle);
}
