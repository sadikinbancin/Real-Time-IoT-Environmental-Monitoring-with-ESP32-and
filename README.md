This repository project builds an Internet of Things (IoT) system for real-time environmental monitoring. It utilizes an ESP32 microcontroller to gather data from various sensors and transmit it to a server running the Flask web framework. The server then processes the received data, displays it on a web interface, and employs long polling to ensure continuous updates.

## System Components

1. ESP32 Microcontroller:Acts as the core device, collecting sensor data and transmitting it to the server over a network.
2. Environmental Sensors:
* DHT22 Sensor: Measures temperature and humidity levels in the environment.
* MQ135 Sensor: Monitors air quality by detecting the presence of various gases.
* Flask Server: Receives data from the ESP32, processes it, and presents it in a user-friendly format on a web page. Additionally, it utilizes long polling to maintain real-time data updates on the client side (web browser).

## Project Files

* ESP32 Code (SIC_PROJECT.ino): This Arduino sketch defines the program running on the ESP32. It handles sensor readings, data formatting, and communication with the Flask server through HTTP requests.
* Flask Server Script (main.py): Written in Python, this script manages the server-side functionality. It receives data from the ESP32, stores it for potential analysis, and serves a web page that displays the real-time environmental data.
* Circuit Diagram (circuit_diagram.png): This visual representation illustrates the physical connections between the sensors and the ESP32 microcontroller.

## Setting Up the Project

1. ESP32 Configuration:
 • Upload the SIC_PROJECT_1.ino code to your ESP32 using the Arduino IDE or a compatible development environment.
 • Ensure the WiFi credentials (network name and password) and sensor pin assignments (data pin, DHT sensor pin, and sensor type) are accurately configured within the code.

2. Flask Server Setup:
 • Install the Flask framework using a package manager like `pip` for Python.
 • Run the main.py script on your server platform (e.g., Raspberry Pi or local computer) using Python.

## Accessing Real-Time Data

1. Open a web browser and navigate to the following URL, replacing `[server-ip]` with the actual IP address of your server: `http://[server-ip]:5000/`
2. The web page will display the real-time environmental data (temperature, humidity, and air quality) collected by the sensors. This data will automatically update on the webpage thanks to the long polling mechanism implemented on the server-side.

## Example Usage

1. Start the Flask server by running the main.py script.
2. Power on the ESP32 connected to the sensors.
3. Open a web browser and navigate to the server's IP address as mentioned earlier.
4. Observe the real-time updates for temperature, humidity, and air quality on the web interface.

## diagram circuit 
![alt text](https://github.com/sadikinbancin/Real-Time-IoT-Environmental-Monitoring-with-ESP32-and/blob/main/circuit_diagram.jpg?raw=true)

Double-check that all connections between the environmental sensors (DHT22 and MQ135) and the ESP32 microcontroller are secure. Pay close attention to the power source (VIN pin) to prevent any malfunctions.
