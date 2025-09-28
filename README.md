# ESP32 Sensor Integration Hub

A personal collection and comprehensive resource of Arduino code examples for interfacing a wide variety of sensors with the ESP32 microcontroller.

## Overview

This repository is a toolkit for anyone working with the ESP32. It aims to provide clear, reliable, and easy-to-use examples for a diverse range of sensors—from simple digital inputs to more complex I2C devices. Each project is self-contained in its own directory, making it simple to find what you need and get your hardware up and running quickly.

Whether you're a student learning about electronics, a hobbyist building a new gadget, or a developer prototyping an IoT solution, you'll find useful code and guidance here.

## Sensor Examples

As new sensors are integrated, they will be added to this list.

| Sensor                       | Type              | Description                               | Folder Link                                       |
| :--------------------------- | :---------------- | :---------------------------------------- | :------------------------------------------------ |
| IR Obstacle Avoidance Sensor | Digital           | Detects the presence of nearby objects.   | [Go to Project](./01-IR-Obstacle-Sensor/)         |
| DHT11 / DHT22                | Digital (One-Wire) | Measures temperature and humidity.        | `(Coming Soon)`                                   |

## Repository Structure

This repository is organized into individual directories for each sensor. Inside each directory, you will find:
- A dedicated `README.md` with specific wiring diagrams and instructions.
- The `.ino` Arduino sketch file.
- A list of required libraries, if any.

## Getting Started

1.  **Clone the repository:**
    ```bash
    git clone [your-repository-url]
    ```
2.  **Prerequisites:**
    -   [Arduino IDE](https://www.arduino.cc/en/software) installed.
    -   ESP32 board support installed in the Arduino IDE.
3.  **Navigate** to the directory of the sensor you are interested in.
4.  **Follow** the instructions in that directory's `README.md` file to wire your circuit and upload the code.

## Contribution

This is currently a personal project, but suggestions and ideas for new sensors to add are always welcome! Feel free to open an issue to suggest a sensor you'd like to see an example for.
