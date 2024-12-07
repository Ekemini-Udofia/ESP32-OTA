#include <WiFi.h>
#include <ArduinoOTA.h>

// Wi-Fi credentials
const char* ssid = "ekeminiudofia";
const char* password = "ekeminietuk";

// FreeRTOS task for OTA updates
void otaTask(void* parameter) {
    ArduinoOTA.setHostname("ESP32-OTA-Example");
    
    // Setup OTA callbacks
    ArduinoOTA.onStart([]() {
        String type = ArduinoOTA.getCommand() == U_FLASH ? "sketch" : "filesystem";
        Serial.println("Start updating " + type);
    });

    ArduinoOTA.onEnd([]() {
        Serial.println("\nEnd");
    });

    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
        Serial.printf("Progress: %u%%\r", (progress * 100) / total);
    });

    ArduinoOTA.onError([](ota_error_t error) {
        Serial.printf("Error[%u]: ", error);
        if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
        else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
        else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
        else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
        else if (error == OTA_END_ERROR) Serial.println("End Failed");
    });

    ArduinoOTA.begin();

    // Main loop for OTA task
    for (;;) {
        ArduinoOTA.handle();
        vTaskDelay(10 / portTICK_PERIOD_MS); // Avoid blocking other tasks
    }
}

void setup() {
    Serial.begin(115200);

    // Connect to Wi-Fi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to Wi-Fi...");
    }
    Serial.println("Connected to Wi-Fi!");

    // Create the OTA task
    xTaskCreate(otaTask, "OTA Task", 4096, NULL, 1, NULL);
}

void loop() {
    // Your main application code
    Serial.println("Running main loop...");
    delay(2000);
}
