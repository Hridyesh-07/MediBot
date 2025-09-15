#include <Keypad.h>
#include <Servo.h>
#include <SoftwareSerial.h>

#define NUM_SERVOS 8
#define BUZZER_PIN 2

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
SoftwareSerial mySerial(6, 7); // RX, TX (UNO1_TX=D7 → UNO2_RX)

String inputTime = "";
unsigned long setTime[NUM_SERVOS] = {0};
unsigned long startTime[NUM_SERVOS] = {0};
bool timeSet[NUM_SERVOS] = {false};
bool servoRun[NUM_SERVOS] = {false};

int currentServo = -1;
bool pulseMode = false;

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);

  for (int i=0; i<NUM_SERVOS; i++) {
    servos[i].attach(servoPins[i]);
    servos[i].write(0);
  }

  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

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
    }

    else if (key >= '0' && key <= '9' && currentServo != -1 && !timeSet[currentServo]) {
      if (inputTime.length() < 6) {
        inputTime += key;
        sendMsg("Typing: " + inputTime);
      }
    }
