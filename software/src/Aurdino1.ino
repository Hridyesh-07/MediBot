#include <Keypad.h>
#include <Servo.h>
#include <SoftwareSerial.h>
#include <PulseSensorPlayground.h>

#define NUM_SERVOS 8
#define BUZZER_PIN 2
#define PULSE_PIN A0   // Pulse sensor pin

// Servo setup
Servo servos[NUM_SERVOS];
int servoPins[NUM_SERVOS] = {3, 4, 5, 6, 7, 8, 9, 10};

// Keypad setup
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {11, 12, 13, A1};
byte colPins[COLS] = {A2, A3, A4, A5};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Serial comm to UNO2
SoftwareSerial mySerial(6, 7); // RX, TX

// Pulse sensor
PulseSensorPlayground pulseSensor;
int Threshold = 550; // Default threshold (adjust if needed)

String inputTime = "";
unsigned long setTime[NUM_SERVOS] = {0};
unsigned long startTime[NUM_SERVOS] = {0};
bool timeSet[NUM_SERVOS] = {false};
bool servoRun[NUM_SERVOS] = {false};

int currentServo = -1;
bool pulseMode = false;

unsigned long lastPulseSend = 0;

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);

  // Attach servos
  for (int i=0; i<NUM_SERVOS; i++) {
    servos[i].attach(servoPins[i]);
    servos[i].write(0);
  }

  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  // Pulse sensor setup
  pulseSensor.analogInput(PULSE_PIN);
  pulseSensor.setThreshold(Threshold);
  if (pulseSensor.begin()) {
    Serial.println("Pulse sensor ready.");
  }

  sendMsg("RESET");
  sendMsg("Select: 1-8 Servo, A Pulse");
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    if (key == '*') { resetSystem(); }

    else if ((key >= '1' && key <= '8') && currentServo == -1 && !pulseMode) {
      currentServo = key - '1';
      inputTime = "";
      sendMsg("SERVO " + String(currentServo+1) + " SELECT");
      sendMsg("Enter HHMMSS then #");
    }

    else if (key == 'A' && currentServo == -1 && !pulseMode) {
      pulseMode = true;
      sendMsg("PULSE MODE ON");
      Serial.println("PULSE MODE ON");
    }

    else if (key >= '0' && key <= '9' && currentServo != -1 && !timeSet[currentServo]) {
      if (inputTime.length() < 6) {
        inputTime += key;
        sendMsg("Typing: " + inputTime);
      }
    }

    else if (key == '#' && currentServo != -1 && !timeSet[currentServo]) {
      if (inputTime.length() == 6) {
        int hh = inputTime.substring(0,2).toInt();
        int mm = inputTime.substring(2,4).toInt();
        int ss = inputTime.substring(4,6).toInt();

        setTime[currentServo] = ((unsigned long)hh * 3600UL +
                                 (unsigned long)mm * 60UL +
                                 (unsigned long)ss) * 1000UL;

        startTime[currentServo] = millis();
        timeSet[currentServo] = true;
        servoRun[currentServo] = false;

        sendMsg("SERVO " + String(currentServo+1) + " SET " +
                String(hh)+"h "+String(mm)+"m "+String(ss)+"s");
      } else {
        sendMsg("ERROR: Need 6 digits");
      }
      currentServo = -1;
    }
  }

  // Servo execution
  for (int i=0; i<NUM_SERVOS; i++) {
    if (timeSet[i] && !servoRun[i] && (millis() - startTime[i] >= setTime[i])) {
      digitalWrite(BUZZER_PIN, HIGH);
      servos[i].write(90);
      sendMsg("SERVO " + String(i+1) + " RUN");
      Serial.println("SERVO " + String(i+1) + " RUN");
      delay(2000);
      servos[i].write(0);
      servoRun[i] = true;
      digitalWrite(BUZZER_PIN, LOW);
      sendMsg("SERVO " + String(i+1) + " DONE");
      Serial.println("SERVO " + String(i+1) + " DONE");
    }
  }

  // Pulse sensor BPM (every second)
  if (pulseMode && millis() - lastPulseSend > 1000) {
    int myBPM = pulseSensor.getBeatsPerMinute();

    if (myBPM > 0) {   // Only send valid BPM
      String msg = "Pulse BPM:" + String(myBPM);
      sendMsg(msg);       // UNO2 LCD पर
      Serial.println(msg); // UNO1 Serial Monitor पर
    }

    lastPulseSend = millis();
  }
}

void resetSystem() {
  inputTime = "";
  currentServo = -1;
  pulseMode = false;
  for (int i=0; i<NUM_SERVOS; i++) {
    timeSet[i] = false;
    servoRun[i] = false;
    servos[i].write(0);
  }
  sendMsg("RESET");
  sendMsg("Select: 1-8 Servo, A Pulse");
  Serial.println("RESET done");
}

void sendMsg(String msg) {
  mySerial.println(msg);
  Serial.println("-> UNO2: " + msg);
}
