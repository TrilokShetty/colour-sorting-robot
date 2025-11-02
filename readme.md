
# Autonomous Color Sorting Robot

This repository contains the code and documentation for the **Autonomous Color Sorting Robot**, developed as the final project for a Mechatronics course.
It demonstrates the integration of **hardware (Arduino, LDRs, Servos)** and **software** to create a functional electromechanical system capable of identifying and sorting objects by color.

---

## Project Overview

The project combines color sensing, calibration, and actuation to build a complete automated sorting mechanism. It includes both manual and automatic calibration methods to ensure reliable performance under varying lighting conditions.

---

## Folder Structure

| Folder Name           | Description                                                                                                                                     |
| --------------------- | ----------------------------------------------------------------------------------------------------------------------------------------------- |
| **AutoCalibration**   | Code containing logic to automatically adjust sensor thresholds for reliable color detection under varying ambient light.                       |
| **ColourSensing**     | Contains code for colour sensing logic.
| **ManualCalibration** | Code that allows the user to manually set and save the color reference values (thresholds) for the sensors.                                     |
| **Complete**          | The final, fully integrated code combining color sensing, calibration, and the servo motor sorting mechanism. This is the main functional code. |

---

## Key Features

* Automatic and manual calibration modes
* Real-time color detection and sorting
* Integration of sensors and actuators for full system automation

---

## Hardware Used

* Arduino Microcontroller
* Light Dependent Resistors (LDRs)
* RGB LEDs
* Servo Motors

---

## Software

* Arduino IDE
* Custom C++ code (Arduino Library) for sensor processing, calibration, and control logic

