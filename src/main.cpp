/**
 * VÍ DỤ 4-1a: ĐỌC CẢM BIẾN MÔI TRƯỜNG BMP280 BẰNG ADAFRUIT_BMP280
 */
#include <Arduino.h>
#include <PTITCube.h>
#include <Wire.h>
#include <Adafruit_BMP280.h>

PTIT_CDH cdh;
PTIT_EPS eps;
Adafruit_BMP280 bmp;

void setup() {
    cdh.begin();

    // Kích hoạt hạ áp nuôi cảm biến qua thư viện EPS
    eps.setBuckState(true);

    Wire.begin(21, 22);

    if (!bmp.begin(0x76) && !bmp.begin(0x77)) {
        cdh.println("BMP280: Warning: Sensor not detected!");
        return;
    }

    bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,
                    Adafruit_BMP280::SAMPLING_X2,
                    Adafruit_BMP280::SAMPLING_X16,
                    Adafruit_BMP280::FILTER_X16,
                    Adafruit_BMP280::STANDBY_MS_500);
}

void loop() {
    float temp = bmp.readTemperature();
    float pres = bmp.readPressure() / 100.0F; // hPa

    cdh.printf("BMP280: Temp: %.2f C | Press: %.1f hPa\n", temp, pres);
    delay(2000);
}
