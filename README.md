# *Smart IoT Water Tank System*

## *Overview*  
This project addresses water scarcity and inefficient irrigation in agriculture using a smart IoT-based water tank system. It combines NodeMCU ESP32 with multiple sensors to monitor water levels, detect leaks, store rainwater, and irrigate soil based on moisture levels. The system is remotely controlled via the Blynk app, providing a scalable solution for smart farming.

---

## *Features*  
- *Rainwater Storage:* Collects rainwater using a rain sensor.  
- *Water Level Monitoring:* Real-time water level updates using an ultrasonic sensor.  
- *Leakage Detection:* Redirects water to a backup tank when leaks are detected.  
- *Moisture-Based Irrigation:* Supplies the required water based on soil moisture levels.  
- *Remote Control:* Enables farmers to monitor and operate the system through the Blynk app.  

---

## *System Architecture*  
![System Architecture](Media/system_architecture_diagram.png)

---

## *Technologies Used*  
- *Hardware:*  
  - NodeMCU ESP32  
  - Ultrasonic Sensor  
  - Rain Sensor  
  - Moisture Sensor  
  - Water Leakage Sensor  

- *Software:*  
  - Arduino IDE  
  - Blynk App  

- *Programming Languages:*  
  - C++  

---

## *How It Works*  
1. *Rainwater Detection:* A rain sensor collects and stores rainwater in the tank.  
2. *Water Level Monitoring:* An ultrasonic sensor continuously monitors water levels and displays them in the Blynk app.  
3. *Leak Detection:* If leaks are detected, water is redirected to a backup tank.  
4. *Irrigation Based on Soil Needs:* A moisture sensor ensures precise water delivery to crops.  
5. *Remote Operation:* Farmers can remotely control the system through the Blynk app interface.  

---


## *Repository Structure*  
```plaintext
Smart-Water-Tank-IoT-System/
├── README.md                      
├── Code/
│   ├── main_code.ino              
├── Media/
│   ├── system_architecture_diagram.png  
│   ├── app_interface_screenshot.png     
├── Documentation/
│   ├── Project_Report.pdf         


---

Installation

1. Clone the repository:

git clone https://github.com/yourusername/Smart-Water-Tank-IoT-System.git


2. Install required libraries in the Arduino IDE for NodeMCU ESP32 and sensors.


3. Open main_code.ino in Arduino IDE and upload it to your NodeMCU ESP32.


4. Set up the Blynk app with virtual pins and display widgets as needed.



---

Contributing

Contributions are welcome! To contribute:

1. Fork the repository.


2. Create a new branch:

git checkout -b feature-name


3. Commit changes:

git commit -m "Add feature-name"


4. Push to the branch:

git push origin feature-name


5. Submit a pull request.




---


Contact

For questions, collaboration, or feedback:

Julana Premasekara: https://www.linkedin.com/in/julana-premasekara-0988a1262?utm_source=share&utm_campaign=share_via&utm_content=profile&utm_medium=android_app
