/**
 * VÍ DỤ 4-1a: ĐỌC CẢM BIẾN MÔI TRƯỜNG BMP280 BẰNG ADAFRUIT_BMP280
 */
#include <Arduino.h>

#include <PTITCube.h>
#include <Wire.h>
#include <Adafruit_BMP280.h>

PTIT_CDH cdh;

Adafruit_BMP280 bmp;

void setup() {
    cdh.begin(115200);
    while (!cdh) { delay(10); }

    cdh.println("\n[EXAMPLE] Bắt đầu bài test Cảm biến Môi trường (BMP280)...");
    cdh.println("[Sensor] Initializing Sensors...");
    
    // I2C mặc định trên ESP32: SDA=21, SCL=22
    Wire.begin(21, 22); 
    
    if (!bmp.begin(0x76) && !bmp.begin(0x77)) {
        cdh.println("BMP280 fail");
        while (1) delay(10);
    }
    cdh.println("BMP280 found!");
    
    // Cấu hình thông số lấy mẫu
    bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                    Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                    Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                    Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                    Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
}

void loop() {
    static unsigned long lastPrint = 0;
    if (millis() - lastPrint > 2000) {
        lastPrint = millis();

        float temp = bmp.readTemperature();
        float pres = bmp.readPressure() / 100.0F; // Chuyển sang hPa

        cdh.print("Nhiệt độ (Temperature) : ");
        cdh.print(temp);
        cdh.println(" *C");
        
        cdh.print("Áp suất (Pressure)     : ");
        cdh.print(pres);
        cdh.println(" hPa");
    }
}

