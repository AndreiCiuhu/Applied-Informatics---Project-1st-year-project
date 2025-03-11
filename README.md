# Proiect ESP32 - Comunicare prin Bluetooth și Wi-Fi

## Descriere (Română)
Acest proiect permite unui microcontroller ESP32 să comunice cu o aplicație mobilă preconfigurată folosind Bluetooth Classic și Wi-Fi. ESP32 scanează rețelele Wi-Fi din apropiere, trimite lista către aplicație și, după conectarea la o rețea aleasă, preia date JSON dintr-un API și le transmite aplicației.

### Funcționalități principale
- Conectare prin Bluetooth Classic la aplicație
- Scanarea și transmiterea listelor de rețele Wi-Fi
- Conectarea la o rețea Wi-Fi aleasă prin aplicație
- Preluarea și transmiterea de obiecte JSON dintr-un API

### Tehnologii utilizate
- **ESP32** (Bluetooth Classic & Wi-Fi)
- **PlatformIO** pentru dezvoltare
- **Arduino Framework**
- **ArduinoJson** pentru manipularea datelor JSON
- **HTTPClient** pentru solicitări API

### Instalare și rulare
1. Instalează [PlatformIO](https://platformio.org/)
2. Clonează repository-ul:
   ```sh
   git clone https://github.com/user/proiect-esp32.git
   ```
3. Deschide proiectul în VS Code cu PlatformIO
4. Conectează ESP32 și flash-uiește codul pe dispozitiv
5. Rulează și conectează-te prin aplicația mobilă

---

## ESP32 Project - Bluetooth and Wi-Fi Communication

### Description (English)
This project enables an ESP32 microcontroller to communicate with a preconfigured mobile app using Bluetooth Classic and Wi-Fi. The ESP32 scans nearby Wi-Fi networks, sends the list to the app, and after connecting to a selected network, it retrieves JSON data from an API and transmits it to the app.

### Main Features
- Connects to the app via Bluetooth Classic
- Scans and transmits Wi-Fi network lists
- Connects to a Wi-Fi network chosen via the app
- Fetches and sends JSON objects from an API

### Technologies Used
- **ESP32** (Bluetooth Classic & Wi-Fi)
- **PlatformIO** for development
- **Arduino Framework**
- **ArduinoJson** for JSON data handling
- **HTTPClient** for API requests

### Installation and Running
1. Install [PlatformIO](https://platformio.org/)
2. Clone the repository:
   ```sh
   git clone https://github.com/user/proiect-esp32.git
   ```
3. Open the project in VS Code with PlatformIO
4. Connect the ESP32 and flash the code onto the device
5. Run and connect via the mobile app

