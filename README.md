# Solar Tracker System

This is a solar tracker system implemented on an Arduino platform using the SolarTracker.ino sketch. The system aims to maximize solar panel efficiency by continuously adjusting the panel's position to face the sun. The solar tracker utilizes analog photoresistors to detect the intensity of sunlight in different directions and adjusts the position of the solar panel's servomotors accordingly.

## Features

**NB:**A doxygen doc is present inside the SourceCode_doc folder

- Sun Position Detection: The solar tracker can detect the sun's position by rotating the solar panel horizontally until it finds the brightest direction.

- Sun Tracking: Once the sun's direction is detected, the solar tracker continuously adjusts the panel's position to keep the sun at the center using analog photoresistors to maintain an optimal angle.

- Real-time Data Logging: The system logs data such as time, temperature, pressure, rain status, and the angles of the servomotors to an SD card in CSV format.

- LCD Display: The system displays real-time data, including the time, temperature, pressure, and sun/rain status, on an I2C-enabled LCD display.

## Components

The Solar Tracker system utilizes the following components:

- Arduino board (not specified in the code, assumed to be compatible with the libraries used)
- BMP280 sensor for temperature and pressure readings
- DS1302 real-time clock module for timekeeping
- Water sensor for detecting rain
- Analog photoresistors for sun position and intensity detection
- Two servo motors for adjusting the solar panel position
- I2C-enabled LCD display for data visualization
- MicroSD Card Adapter for data logging

## Setup

To set up the Solar Tracker system, follow these steps:

1. Connect all the components according to the pin mappings specified in the code.
2. Upload the SolarTracker.ino sketch to your Arduino board using the Arduino IDE or compatible software.
3. Power on the system and ensure the components are functioning correctly.
4. The system will start by finding the sun's position. Ensure the panel has a clear view of the sun during this calibration phase.
5. Once the sun's position is detected, the solar panel will start tracking the sun continuously.

**NB**: A *fritzing sketch* with wiring instructions is present inside the Wiring folder.

## Note

- The system assumes the presence of analog photoresistors connected to specific analog pins (UP, DX, SX, DW) to detect the intensity of sunlight in different directions.

- The servo motors are used to adjust the solar panel position. The code generates PWM signals to control the servo motors.

- The system logs data to an SD card in CSV format. Ensure that the SD card is correctly formatted and inserted before running the system.

- The LCD display shows real-time data, including the current time, temperature, pressure, and sun/rain status. Ensure the I2C-enabled LCD module is correctly connected to the Arduino.

- The BMP280 sensor is used to read temperature and pressure data.

## Credits

The Solar Tracker system was developed by Culcea Cezar, and it was inspired by various open-source projects and tutorials available in the Arduino community.
