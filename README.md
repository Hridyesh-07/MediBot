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
```
MediBot/
│── hardware/          # Wiring diagrams, photos, parts list
│── software/
│   ├── src/          # Arduino sketches for both boards (.ino files)
│   └── include/      # Optional header files or libraries
│── docs/             # Documentation, user guides, screenshots
│── README.md         # This project overview
```
---

## Setup Instructions

1. Clone this repository:  
git clone https://github.com/Hridyesh-07/MediBot
2. Open Arduino IDE and install these libraries if not present:  
- Keypad  
- Servo  
- LiquidCrystal_I2C  
- SoftwareSerial  
3. Upload `arduino_secondary.ino` (in `software/src/`) to Arduino controlling servos/keypad.  
4. Upload `arduino_primary.ino` (in `software/src/`) to Arduino controlling LCD and pulse sensor.  
5. Connect hardware according to the wiring schematic in `hardware/` folder.  
6. Power the Arduinos and test the system.

---

## Usage

- Use keypad on Arduino 2 to select a medicine slot (1-8) and set reminder time (HHMMSS).  
- Press `#` to confirm the timing, or `*` to reset the system.  
- At the programmed time, the buzzer sounds, the servo corresponding to the selected medicine slot opens it, and the LCD on Arduino 1 displays status and pulse information.

---

## Contribution

Contributions, suggestions, and bug reports are welcome. Fork the project and submit pull requests with improvements or fixes.

---

## License

Licensed under the MIT License. See the LICENSE file for details.

---

## Contact

For questions or support, open an issue or contact [hridyeshb8@gmail.com,sujalpanchal997@gmail.com].
