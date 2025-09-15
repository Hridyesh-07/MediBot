#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

#define PULSE_PIN A0

LiquidCrystal_I2C lcd(0x27, 16, 2); // check address
SoftwareSerial mySerial(6, 7); // RX, TX (UNO2_RX=6 ← UNO1_TX=7)

String serialData = "";
unsigned long lastPulse = 0;

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("UNO2 Ready");
  delay(2000);
  lcd.clear();
}

void loop() {
  while (mySerial.available()) {
    char c = mySerial.read();
    if (c == '\n') {
      displayMsg(serialData);
      serialData = "";
    } else {
      serialData += c;
    }
  }

if (millis() - lastPulse > 500) {
    int pulseValue = analogRead(PULSE_PIN);
    lcd.setCursor(0,1);
    lcd.print("Pulse:");
    lcd.print(pulseValue);
    lcd.print("   ");
    Serial.print("Pulse: ");
    Serial.println(pulseValue);
    lastPulse = millis();
  }
}

void displayMsg(String msg) {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(msg.substring(0,16));
  lcd.setCursor(0,1);
  if (msg.length() > 16) lcd.print(msg.substring(16));
  Serial.println("LCD: " + msg);
}
