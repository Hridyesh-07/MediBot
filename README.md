# MediBot – Dual Arduino Medicine Reminder System

MediBot is an automated medicine reminder that uses two Arduino UNOs.  
One Arduino handles keypad input, servo motor control, and buzzer alerts to open medicine compartments at scheduled times.  
The second Arduino displays status messages and real-time pulse sensor data on a 16x2 I2C LCD.

---

## Project Overview

- **Arduino 2 (Secondary Board):**  
  Receives status messages from Arduino 1 and shows them on a 16x2 LCD. It continuously reads a pulse sensor on analog pin A0 and displays the pulse value.
- **Arduino 1 (Primary Board):**  
 Controls 8 servos on pins 3-10, accepts user input from a 4x4 keypad, and activates a buzzer on reminders. It runs timers for each servo slot based on user input and communicates status messages over SoftwareSerial to the primary board.
---

## Features

- Precise time-based medicine slots with servo-controlled compartments  
- Keypad interface to program reminders in HHMMSS format  
- Buzzer for audible alerts  
- Real-time display of reminders and pulse sensor data on LCD  
- Modular dual-Arduino design with serial communication  

---

## Hardware Components

- 2 × Arduino UNO boards  
- 8 × Servo motors (pins 3 to 10 on Arduino 2)  
- 4×4 Matrix Keypad connected to Arduino 2  
- Piezo buzzer on pin 2 (Arduino 2)  
- 16×2 I2C LCD connected to Arduino 1  
- Pulse sensor on analog input A0 (Arduino 1)  
- Jumper wires, breadboard/battery pack  

---

## Folder Structure
MediBot/
│── hardware/          # Wiring diagrams, photos, parts list
│── software/
│   ├── src/          # Arduino sketches for both boards (.ino files)
│   └── include/      # Optional header files or libraries
│── docs/             # Documentation, user guides, screenshots
│── README.md         # This project overview

