# MediBot User Manual

---

## Introduction

MediBot is a dual-Arduino-based personal medicine reminder system designed to help patients remember to take their medications on time. It uses servo-controlled compartments, buzzer alerts, and an LCD display.

---

## Hardware Overview

- Two Arduino UNO boards  
- 8 servo motors controlling medicine compartments  
- 4x4 keypad for user input  
- Buzzer for audible alerts  
- 16x2 I2C LCD for displaying status and pulse sensor data  
- Pulse sensor for monitoring heart rate  
- Connectors, jumper wires, and power supply  

---

## Getting Started

### Setup

1. Connect all hardware as per the wiring diagrams in the `hardware/` folder.  
2. Power both Arduino boards via USB or battery packs.  
3. Verify that the LCD shows “UNO2 Ready” message.

### Software

1. Upload the Arduino sketches to their respective boards as described in the README.  
2. Ensure required libraries (`Keypad`, `Servo`, `LiquidCrystal_I2C`, `SoftwareSerial`) are installed.

---

## How to Use

### Setting Medicine Reminders

1. On the keypad, press a number between **1** and **8** to select the medicine compartment.  
2. Enter the reminder time in **HHMMSS** format (Hours, Minutes, Seconds).  
3. Press the `#` key to save the time for the selected compartment.  
4. The LCD will display confirmation of the time set.

### Resetting

- Press the `*` key at any time to reset the system and clear all reminders.

### Alerts

- When it is time to take the medicine:  
  - The buzzer will sound.  
  - The corresponding servo motor will open the compartment.  
  - The LCD will show the reminder status.  

---

## Troubleshooting

- If the keypad does not respond, check connections between keypad and Arduino 2.  
- If the LCD is blank, verify I2C connections and power to Arduino 1.  
- Ensure servos are connected to the correct pins and powered adequately.  
- Restart both Arduinos if the system behaves unexpectedly.

---

## Support

For further assistance or to report bugs, please open an issue in the GitHub repository or contact:- [hridyeshb8@gmail.com,sujalpanchal997@gmail.com]

---

Thank you for using MediBot!
