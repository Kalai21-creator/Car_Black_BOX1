# Car Black Box Project Using PIC18F4580

## Overview
The Car Black Box is a vehicle monitoring and data logging system developed using the PIC18F4580 microcontroller. It tracks and records key vehicle parameters such as speed and location, enabling accident investigations and maintenance planning. The system also features a Matrix Digital Keypad (MKP) for gear shift control and collision detection.

---

## Objectives
- Record vehicle data, including speed and location.
- Provide gear shift control using the MKP.
- Detect collision events and disable gear shifting post-collision.

---

## Key Features
### 1. Microcontroller
- **PIC18F4580:** Handles sensor data processing, gear shift logic, and dashboard interface.

### 2. Matrix Digital Keypad (MKP)
- **MKP1:** Increase gear (up to a maximum limit).
- **MKP2:** Decrease gear (down to a minimum limit).
- **MKP3:** Detect collision and disable gear shifting post-event.
- **MKP4:** Trigger events or processes.
- **MKP5:** Return to the menu or main screen.

### 3. Sensors
- **Speed Sensor:** Monitors the vehicle’s speed.
- **GPS Sensor:** Tracks the vehicle's location.
- **Collision Detection Sensor:** Detects crash events.

### 4. Data Logging
- Logs speed, time, and events to memory.
- Data accessible via the user interface.

### 5. User Interface
- Displays current gear, speed, and system status.

### 6. Collision Detection
- Disables further gear shifting after a crash.

---

## System Design
### Block Diagram
- Interfaces MKP, sensors, and memory with the PIC18F4580 microcontroller.

### Procedures
1. **Microcontroller Integration:**
   - Controls and processes input from MKP and sensors.
2. **MKP Functionality:**
   - Gear control and collision handling.
3. **Data Logging:**
   - Stores critical data for future analysis.
4. **User Interface:**
   - Provides a simple dashboard for managing vehicle data.

### Architecture of PIC18F4580
- **CPU:** Executes control logic.
- **Memory:** Flash and EEPROM for program and data storage.
- **I/O Ports:** Interface with MKP and sensors.
- **Communication:** UART/USB for data access.
- **Peripheral Modules:** Timers, ADCs, and I/O control.

---

## Advantages
- **Real-time Data Logging:** Continuously tracks vehicle parameters.
- **Manual Gear Control:** MKP provides simple gear adjustments.
- **Collision Detection:** Disables gear shifting post-collision.
- **User-Friendly Interface:** Simple and accessible dashboard.

## Disadvantages
- **Limited Gear Control Post-Collision:** Gear shifting is disabled after a collision.
- **Power Consumption:** Continuous operation may consume more power.

---

## Dashboard Features
- **View Log:** Displays recorded data.
- **Download Log:** Export logs to an external device.
- **Set Time:** Configure the system clock for accurate logging.
- **Clear Log:** Erase stored data.
- **Control Parameters:**
  - MKP1: Increase gear.
  - MKP2: Decrease gear.
  - MKP3: Collision detection.
  - MKP4: Trigger event.
  - MKP5: Return to menu.

---

## Testing
- **Gear Shift Functionality:** Ensure proper gear control.
- **Collision Detection:** Verify gear shifting is disabled upon collision.

---

## Future Scope
- **Smart Integration with Car ECU:** Seamless interaction with existing car control units.
- **Expanded Sensor Array:** Monitor additional parameters such as tire pressure and fuel consumption.
- **Mobile Application Integration:** View and download logs via a smartphone app.
- **Artificial Intelligence:** Predict potential issues based on vehicle data.

---

## Conclusion
The Car Black Box project using the PIC18F4580 microcontroller and Matrix Digital Keypad provides a reliable solution for vehicle monitoring and data logging. Its integration of gear control, collision detection, and data storage adds value for both real-time tracking and accident analysis. Future enhancements can further improve its functionality and integration with modern vehicle technologies.

