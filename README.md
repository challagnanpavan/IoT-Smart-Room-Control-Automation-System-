# 🌡️ IoT Smart Room Controller - ESP32 Automation System  
**Automated climate & lighting control using DHT11, Ultrasonic, and LDR sensors with web interface**  
*"Your Room, Smarter."*  

[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)](https://opensource.org/licenses/MIT)
[![ESP32](https://img.shields.io/badge/Platform-ESP32-blue.svg)](https://www.espressif.com/)
![Project Maintenance](https://img.shields.io/badge/Maintained%3F-Yes-brightgreen.svg)

---

## 📂 Project Files
- **Main Controller**: `smart_room_controller.ino`
- **Web Interface**: `web_controls.html` (embedded in code)
- **Sensor Libraries**: `DHT.h` (Adafruit Unified Sensor Lib required)

---

## 🌟 Key Features
- 🕹️ Dual-mode operation (Auto/Manual)
- 🌡️ Temperature-triggered fan control
- 💡 Light-sensitive lighting with LDR
- 👤 Presence detection via ultrasonic sensor
- 🌐 Web dashboard for remote control
- 🔄 Real-time sensor monitoring

---

## 🛠️ Hardware Architecture
```mermaid
graph TB
    A[DHT11 Sensor] -->|Temp/Humidity| B(ESP32)
    C[Ultrasonic Sensor] -->|Distance| B
    D[LDR Sensor] -->|Ambient Light| B
    B -->|Relay Control| E[Light]
    B -->|Relay Control| F[Fan]
    B -->|WiFi| G[Web Interface]
```

---

## 🚀 Quick Start
1. **Hardware Setup**
   ```python
   Connections:
   DHT11   -> GPIO14
   HC-SR04 -> Trig:GPIO12, Echo:GPIO13
   LDR     -> GPIO33
   Relay1  -> GPIO27 (Light)
   Relay2  -> GPIO26 (Fan)
   ```

2. **Configure WiFi**
   ```cpp
   const char* WiFi_name = "YOUR_SSID";
   const char* WiFi_pass = "YOUR_PASSWORD";
   ```

3. **Upload & Monitor**
   ```bash
   PlatformIO CLI:
   pio run -t upload && pio device monitor
   ```

---

## 🖥️ Web Interface Preview
![Web UI](https://i.imgur.com/JQZ1l0P.png)  
*Accessible at `http://[ESP32-IP]/`*

---

## 🔧 Technical Specifications
| Component       | Function                     | GPIO  |
|-----------------|------------------------------|-------|
| DHT11           | Temperature/Humidity         | 14    |
| HC-SR04         | Presence Detection           | 12,13 |
| LDR             | Ambient Light Sensing        | 33    |
| Relay Module    | Light/Fan Control            | 26,27 |

---

## 💡 Advanced Customization
```cpp
// Auto-mode thresholds (modify as needed)
#define TEMP_THRESHOLD 20.0    // °C
#define DISTANCE_THRESHOLD 10  // cm
```

---

## 🌐 IoT Integration Roadmap
- [ ] MQTT Support for Home Assistant
- [ ] Firebase Realtime Database Logging
- [ ] OTA (Over-the-Air) Updates
- [ ] Energy Consumption Monitoring

---

## 📜 License
MIT © [Your Name]  
*"Making automation human-friendly since 2024"*  

[☕ Support the Project](https://www.buymeacoffee.com/yourprofile)  
[🐛 Report Issues](https://github.com/yourrepo/issues)
```

### Key Enhancements:
1. **Visual Hierarchy**: Emojis + shields.io badges create professional appearance
2. **Mermaid Diagram**: Self-documenting architecture visualization
3. **Responsive Tables**: Clean component mapping
4. **Future Roadmap**: Shows project evolution potential
5. **Dual Badges**: License + maintenance status for credibility

### Suggested Filename:
- **Primary Sketch**: `smart_room_controller.ino` (descriptive yet concise)

### Pro Tips:
1. Add actual web UI screenshot in `/images` folder
2. Include wiring diagram as `wiring.png`
3. Create `platformio.ini` for PlatformIO users
4. Add serial monitor output samples in `/docs`

This presentation combines technical depth with visual appeal to attract collaborators and users!
