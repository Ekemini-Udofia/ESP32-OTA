# ESP32 OTA Example

This project demonstrates how to set up Over-the-Air (OTA) updates on an ESP32 using the Arduino framework. The code uses FreeRTOS to run the OTA handling task in parallel with the main application.

---

## Features

- **Wi-Fi Connection**: Connects the ESP32 to a specified Wi-Fi network.
- **Over-the-Air Updates**: Allows updating the ESP32 firmware wirelessly.
- **FreeRTOS Task**: Runs the OTA functionality in a separate task, ensuring a responsive system.
- **OTA Callbacks**: Provides feedback during the OTA process, including start, progress, completion, and error handling.

---

## Getting Started

### Prerequisites

- **Hardware**: ESP32 development board.
- **Software**:
  - Arduino IDE or PlatformIO.
  - ESP32 board support installed in the Arduino IDE (via `Boards Manager`).

---

### Wiring

No additional wiring is needed. The ESP32 board connects to Wi-Fi for OTA updates.

---

### Setup Instructions

1. Open the code in your preferred IDE.
2. Update the Wi-Fi credentials in the code:
   ```cpp
   const char* ssid = "your-ssid";
   const char* password = "your-password";
   ```
3. Upload the code to your ESP32 using a USB connection.

---

### OTA Update Steps

1. Once the ESP32 is running, it connects to the specified Wi-Fi network and starts the OTA service.
2. Find the device on your network using its hostname: `ESP32-OTA-Example`.
3. Use the Arduino IDE or any OTA update tool to upload new firmware.

---

## Code Overview

### Wi-Fi Setup
The ESP32 connects to the specified Wi-Fi network in the `setup()` function:
```cpp
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to Wi-Fi...");
}
Serial.println("Connected to Wi-Fi!");
```

### OTA Task
The OTA functionality runs in a FreeRTOS task created in `setup()`:
```cpp
xTaskCreate(otaTask, "OTA Task", 4096, NULL, 1, NULL);
```

The `otaTask` function manages the OTA update process:
- Initializes OTA service.
- Handles OTA events (start, progress, end, and errors).

---

## OTA Feedback
- **Start**: Indicates whether a sketch or filesystem is being updated.
- **Progress**: Displays the percentage of the update completed.
- **End**: Confirms successful completion.
- **Errors**: Prints specific errors such as authentication, connection, or transfer failures.
