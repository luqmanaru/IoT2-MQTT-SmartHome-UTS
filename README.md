# IoT2-MQTT-SmartHome-UTS

Implementasi sistem smart home dengan komunikasi MQTT untuk monitoring suhu dan kontrol lampu menggunakan NodeMCU ESP8266.

## 📖 Deskripsi
Proyek ini merupakan solusi **smart home** berbasis protokol **MQTT** yang mengimplementasikan dua topik berbeda: monitoring suhu dan kontrol lampu. Sistem ini dirancang untuk lingkungan dengan koneksi terbatas dan menunjukkan bagaimana satu perangkat dapat berfungsi sebagai publisher dan subscriber sekaligus.

## ✨ Fitur Utama
- Monitoring suhu otomatis setiap 5 detik
- Kontrol lampu via pesan MQTT
- Dua topik terpisah untuk fungsi berbeda
- Hemat bandwidth dengan header MQTT minimalis
- Stabil di jaringan lemah/putus-nyambung
- Simulasi dengan LED built-in ESP8266

## 🛠️ Komponen
| Komponen       | Spesifikasi          |
|----------------|----------------------|
| Mikrokontroler | NodeMCU ESP8266      |
| Protokol       | MQTT over TCP        |
| Broker         | test.mosquitto.org   |
| Topik Suhu     | `smartHome/hanif/suhu` |
| Topik Lampu    | `smartHome/hanif/lampu` |
| Payload Suhu   | `Suhu X°C`           |
| Payload Lampu  | `ON` / `OFF`         |

## 🚀 Cara Kerja
```
+-----------+     +--------+     +-----------+
| Publisher | --> | Broker | --> | Subscriber|
| (Suhu)    |     | MQTT   |     | (Lampu)   |
+-----------+     +--------+     +-----------+
       ^                              |
       |                              v
+-----------+                     +-----------+
| ESP8266   | <-- (Kontrol) ----- | Aplikasi  |
| (Sensor)  |                     | HP/Client |
+-----------+                     +-----------+
```

### Langkah-langkah:
1. **ESP8266** terhubung ke WiFi dan broker MQTT.
2. **Publish Data Suhu**: Setiap 5 detik, ESP8266 mengirim data suhu ke topik `smartHome/hanif/suhu`.
3. **Subscribe Kontrol Lampu**: ESP8266 mendengarkan pesan di topik `smartHome/hanif/lampu`.
4. **Kontrol Lampu**: Ketika menerima pesan "ON" atau "OFF", ESP8266 mengubah status LED.
5. **Client Aplikasi**: Dapat subscribe ke topik suhu untuk monitoring dan publish ke topik lampu untuk kontrol.

## ⚙️ Instalasi
1. **Prasyarat**:
   - Arduino IDE dengan ESP8266 board manager
   - Library `PubSubClient` oleh Nick O'Leary
   - Aplikasi MQTT client (MQTT Dash, MQTT Explorer, dll)

2. **Konfigurasi**:
   - Ganti nilai berikut di kode:
     ```cpp
     const char* ssid = "YOUR_WIFI_SSID";
     const char* password = "YOUR_WIFI_PASSWORD";
     ```

3. **Upload**:
   - Hubungkan NodeMCU ke komputer
   - Pilih board "NodeMCU 1.0 (ESP-12E Module)" dan port yang sesuai
   - Upload kode

4. **Testing**:
   - Buka Serial Monitor (baudrate: 115200)
   - Pastikan WiFi dan MQTT terhubung
   - Gunakan MQTT client untuk:
     - Subscribe ke `smartHome/hanif/suhu` untuk melihat data suhu
     - Publish `ON` atau `OFF` ke `smartHome/hanif/lampu` untuk kontrol LED

## 🔍 Analisis Teknis
### Mekanisme Publish-Subscribe
| Komponen   | Fungsi                          | Topik                     |
|------------|---------------------------------|---------------------------|
| Publisher  | Mengirim data suhu              | `smartHome/hanif/suhu`    |
| Subscriber | Menerima data suhu              | `smartHome/hanif/suhu`    |
| Publisher  | Mengirim perintah kontrol lampu | `smartHome/hanif/lampu`   |
| Subscriber | Menerima perintah kontrol lampu | `smartHome/hanif/lampu`   |

### Keunggulan MQTT untuk IoT
1. **Efisiensi Bandwidth**: Header hanya 2 byte, ideal untuk jaringan terbatas
2. **Model Publish-Subscribe**: Satu pesan dapat diterima oleh banyak subscriber
3. **Koneksi Persisten**: Mengurangi overhead koneksi berulang
4. **QoS Levels**: Dukungan untuk kualitas layanan yang dapat disesuaikan
5. **Will Message**: Notifikasi otomatis saat client terputus

## 📊 Hasil Output
### Output Serial Monitor
```
Menghubungkan ke .................
WiFi terhubung
IP address: 192.168.1.100
Menghubungkan MQTT...Terhubung
Publish pesan: Suhu 26°C
Publish pesan: Suhu 27°C
Pesan baru: [smartHome/hanif/lampu] ON
```

### Contoh Pesan MQTT
- **Publish Suhu**: 
  ```
  Topic: smartHome/hanif/suhu
  Payload: Suhu 28°C
  ```
- **Publish Kontrol Lampu**:
  ```
  Topic: smartHome/hanif/lampu
  Payload: ON
  ```

---
**luqmanaru**  
