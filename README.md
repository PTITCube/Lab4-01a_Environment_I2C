# Lab 4-01a: Đọc Cảm Biến Môi Trường BMP280 Qua I2C (Environment Sensor I2C)

> **Phân hệ:** Sensor & Scientific Payload  
> **Thư viện yêu cầu:** `PTITCube Library v1.1.0`  
> **Nền tảng:** PlatformIO / ESP32-WROOM-32 (OBC)

---

## 📖 1. Mục Tiêu & Mô Tả Bài Thực Hành

Đọc thanh ghi thô cảm biến BMP280 qua bus I2C (địa chỉ 0x76), áp dụng hệ số bù nhiệt/áp và tính toán độ cao khí áp thủy tĩnh.

---

## 🔌 2. Sơ Đồ Chân Phần Cứng (Hardware Pinout)

| Tín hiệu | Chân ESP32 | Mô tả |
| :--- | :--- | :--- |
| I2C SDA | GPIO 21 | Tuyến dữ liệu I2C chung |
| I2C SCL | GPIO 22 | Tuyến xung nhịp I2C chung |
| Buck Control | GPIO 4 | Bật mạch hạ áp cấp nguồn cảm biến (Bắt buộc mức HIGH) |

> [!IMPORTANT]
> Mạch phần cứng CubeSat sử dụng **GPIO 4** để điều khiển mạch hạ áp (Buck Converter) cấp nguồn cho các cảm biến. Mặc định mạch ở mức 0 (ngắt dòng). Do đó, ở các bài thực hành đọc cảm biến I2C thuần, **bắt buộc phải xuất mức 1 (HIGH) ra GPIO 4** trước khi khởi tạo `Wire` để cấp nguồn cho cảm biến hoạt động.

---

## 🛠️ 3. Cấu Hình Phần Mềm & Thư Viện

- **Thư viện cốt lõi:** Thư mục `lib/PTITCube` tích hợp sẵn bộ thư viện phiên bản mới nhất `v1.1.0` với các phân hệ phân lớp:
  - `CDH`: Quản lý luồng xuất nhập dữ liệu `cdh` (Stream inheritance) và hệ thống tệp FAT32 trên thẻ nhớ MicroSD.
  - `EPS`: Quản lý năng lượng, đọc IC MAX17048 qua I2C.
  - `Sensor`: Đọc cụm cảm biến môi trường BMP280, cảm biến quán tính 6-DoF MPU6500, từ kế QMC5883L và định vị GNSS L76X.
  - `COM`: Quản lý module vô tuyến LoRa Ebyte E32 qua giao tiếp UART2.
- **Kênh giám sát Console:**
  - **Công cụ:** `cdh (PTIT_CDH stream - 115200 baud)`
  - **Tốc độ Baud:** `115200 bps`
  - **Lưu ý chuẩn hóa:** Kể từ Lab 3, mọi luồng in debug console được chuẩn hóa qua đối tượng `cdh` (`PTIT_CDH cdh;`) kế thừa trực tiếp từ lớp `Stream`/`Print` của Arduino, thay thế hoàn toàn cho `Serial` thông thường.

---

## 🚀 4. Hướng Dẫn Biên Dịch & Nạp Firmware

Sử dụng **PlatformIO CLI** hoặc giao diện **VSCode / PlatformIO IDE**:

```bash
# 1. Di chuyển vào thư mục dự án
cd Lab4-01a_Environment_I2C

# 2. Biên dịch mã nguồn
pio run

# 3. Nạp firmware vào vi điều khiển vệ tinh
pio run -t upload

# 4. Mở cửa sổ giám sát Serial Monitor
pio device monitor -b 115200
```

---

## 📝 5. Lưu Ý Kỹ Thuật

- Đo áp suất (hPa), nhiệt độ (°C) và ước lượng độ cao khí quyển.
- Không chèn các lệnh in `println()` trang trí dư thừa làm nghẽn bộ đệm UART khi vệ tinh vận hành ở tần số cao.
- Kiểm tra kết nối cáp USB-UART và nguồn pin trước khi thực hiện nạp code.
