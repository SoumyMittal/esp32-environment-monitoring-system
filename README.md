# 🌡️ ESP32 Environment Monitoring System

## Overview

The ESP32 Environment Monitoring System is an IoT-based environmental monitoring solution designed to continuously track temperature and humidity conditions in real time.

The system utilizes an **ESP32 microcontroller** and a **DHT11 temperature-humidity sensor** to collect environmental data. When abnormal conditions are detected, the system automatically triggers multiple alert mechanisms, including LED indicators, buzzer notifications, and email alerts.

The project demonstrates the integration of embedded systems, IoT communication, sensor interfacing, and automated monitoring for smart environmental management applications.

---

## Features

* Real-time temperature monitoring
* Real-time humidity monitoring
* ESP32-based IoT architecture
* Wi-Fi connectivity
* Automatic Wi-Fi reconnection
* Threshold-based anomaly detection
* Automated email notifications
* LED alert indication
* Buzzer alert system
* Sensor failure detection and handling
* Continuous environmental monitoring

---

## Hardware Components

| Component                 | Description                          |
| ------------------------- | ------------------------------------ |
| ESP32                     | Main microcontroller                 |
| DHT11 Sensor              | Temperature and humidity measurement |
| LED                       | Visual alert indicator               |
| Buzzer                    | Audible alert system                 |
| Breadboard & Jumper Wires | Circuit connections                  |

---

## System Workflow

1. ESP32 connects to the configured Wi-Fi network.
2. DHT11 sensor continuously measures temperature and humidity.
3. Sensor readings are processed and validated.
4. Values are compared against predefined threshold limits.
5. If abnormal conditions are detected:

   * LED indicator is activated.
   * Buzzer alarm is triggered.
   * Email notification is sent automatically.
6. The monitoring cycle repeats continuously.
7. If Wi-Fi disconnects, the ESP32 automatically attempts reconnection.

---

## Project Structure

```text
esp32-environment-monitoring-system/
│
├── abc.ino
├── README.md
│
├── images/
│   ├── circuit_diagram.png
│   ├── hardware_setup.jpg
│   └── working_demo.jpg
│
└── docs/
    └── project_report.pdf
```

---

## Technologies Used

### Hardware

* ESP32
* DHT11 Sensor
* LED
* Buzzer

### Software

* Arduino IDE
* Embedded C/C++
* ESP32 Wi-Fi Library
* DHT Sensor Library
* SMTP Email Library

---

## Alert Mechanism

The system supports multiple notification methods:

### Visual Alerts

* LED indicator activation

### Audible Alerts

* Buzzer alarm notification

### Remote Alerts

* Automated email notifications through SMTP

This ensures that environmental anomalies can be detected both locally and remotely.

---

## Applications

* Smart Home Monitoring
* Server Room Monitoring
* Laboratory Environment Monitoring
* Greenhouse Monitoring
* Industrial Safety Systems
* IoT-Based Environmental Control

---

## Installation

### 1. Clone the Repository

```bash
git clone https://github.com/SoumyMittal/esp32-environment-monitoring-system.git
```

### 2. Open the Project

Open the `.ino` file using Arduino IDE.

### 3. Install Required Libraries

Install the following libraries:

* DHT Sensor Library
* ESP Mail Client Library
* WiFi Library (ESP32)

### 4. Configure Credentials

Replace the placeholder values:

```cpp
#define WIFI_SSID "YOUR_WIFI_SSID"
#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"

#define AUTHOR_EMAIL "YOUR_EMAIL"
#define AUTHOR_PASSWORD "YOUR_APP_PASSWORD"
```

### 5. Upload to ESP32

* Select the ESP32 board.
* Choose the correct COM port.
* Upload the code.

---

## Future Improvements

* MQTT integration
* Cloud dashboard support
* Mobile application notifications
* Data logging and visualization
* ThingSpeak/Blynk integration
* Multiple sensor support
* Predictive environmental analytics

---

## Learning Outcomes

This project provided hands-on experience with:

* Embedded Systems Programming
* ESP32 Development
* Sensor Interfacing
* IoT Communication
* Wi-Fi Networking
* Automated Alert Systems
* Environmental Monitoring Applications

---

## Author

**Soumy Mittal**

B.Tech Artificial Intelligence & Data Science
Amrita Vishwa Vidyapeetham

### Interests

* Artificial Intelligence
* Machine Learning
* Embedded Systems & IoT
* Computer Vision
* Scientific Computing
* Data-Driven Engineering

---

## License

This project is licensed under the MIT License.
