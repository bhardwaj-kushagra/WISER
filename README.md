# WISER: Weather Information Sensor Environmental Reporter

## Overview
WISER (Weather Information Sensor Environmental Reporter) is an ESP8266-based weather monitoring system that gathers environmental data such as temperature, humidity, pollution levels, and light intensity. This project provides real-time monitoring of environmental conditions and alerts users via email and push notifications based on predefined thresholds.

## Project Versions
WISER currently has three versions:
1. Blynk Version: This version uses the Blynk cloud service for remote monitoring and notification.
2. ThingSpeak Version: This version utilizes ThingSpeak for data logging and visualization.
3. Standalone Version: This version operates offline without relying on any cloud services.

Please note that this repository is not fully updated yet. A major update is scheduled for April 2024, which will include modifications to the README and the addition of new versions with enhanced features.

## Features
- Measures temperature and humidity using the DHT11 sensor.
- Detects pollution levels with the MQ7 sensor.
- Monitors light intensity using an LDR sensor.
- Displays data on an OLED screen for local visualization.
- Supports email and push notifications for critical events.
- Provides remote monitoring through cloud services (Blynk or ThingSpeak).
- Operates standalone without requiring internet connectivity (Standalone Version).

## Requirements
- ESP8266 microcontroller (NodeMCU or similar)
- DHT11 sensor
- MQ7 sensor
- LDR sensor
- OLED display
- Internet connectivity for cloud-based versions (Blynk or ThingSpeak)
- Arduino IDE or compatible development environment

## Setup
Please refer to the setup instructions provided in each version's respective README file.

## Usage
Please refer to the usage instructions provided in each version's respective README file.

## Contributions
Contributions to the WISER project are welcome! If you have any suggestions, bug reports, or feature requests, please submit them via GitHub issues or fork the repository and submit a pull request.

## License
This project is licensed under the [MIT License](LICENSE).

## Contact
For any inquiries or assistance regarding the WISER project, feel free to contact the project maintainer:
- Kushagra Sharma
- sharmakushagra02@gmail.com
