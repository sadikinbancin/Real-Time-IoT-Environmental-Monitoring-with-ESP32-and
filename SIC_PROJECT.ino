#include <WiFi.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <HTTPClient.h>

// Konstan untuk WiFi credentials
const char *WIFI_SSID = "Redmi Note 10";
const char *WIFI_PASS = "Mincip789";

// Pin assignments
int sensor_input = 32;
#define DHTPIN 33  // DHT22 sensor pin
#define DHTTYPE DHT22  // DHT sensor type

// Global objects
DHT_Unified dht(DHTPIN, DHTTYPE);
sensors_event_t event;
// Fungsi untuk mendapatkan data suhu
float get_temperature_data() {
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
     return 0.0;  // Return default value on error
  }
  else {
    Serial.print(F("Temperature: "));
    Serial.print(event.temperature);
    Serial.println(F("°C"));
    return event.temperature;
  }  
}

// Fungsi untuk mendapatkan data kelembaban
float get_humidity_data() {
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
    return 0.0;
  }
  else {
    Serial.print(F("Humidity: "));
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));
    return event.relative_humidity;
  }
}

// Fungsi untuk membaca data analog dari air quality sensor
int get_air_quality_data() {
  int analog_data = analogRead(sensor_input);
  Serial.print("Air Quality: ");
  Serial.println(analog_data);
  delay(300);  // Allow sensor to stabilize
  return analog_data;
}

void connect_wifi() {
  // Hubungkan ESP32 ke WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Tampilkan pesan sukses
  Serial.println("");
  Serial.println("WiFi connected!");
  Serial.println("IP address: " + WiFi.localIP().toString());
}

// Fungsi untuk mengirim data ke server web
void send_data_to_web(float temperature, float humidity, int air_quality) {
  // Buat objek HTTPClient
  HTTPClient http;
  
  // Set URL server web
  http.begin("http://192.168.1.10:5000/data"); // Ganti dengan URL endpoint yang benar

  // Buat data yang akan dikirimkan dalam format JSON
  String data = "{"
                "\"temperature\": " + String(temperature) + ","
                "\"humidity\": " + String(humidity) + ","
                "\"air_quality\": " + String(air_quality) +
                "}";

  // Set header untuk HTTP POST
  http.addHeader("Content-Type", "application/json");

  // Kirim permintaan POST
  int httpCode = http.POST(data);

  // Cek status permintaan
  if (httpCode == HTTP_CODE_OK) {
    // Tampilkan pesan sukses
    String payload = http.getString();
    Serial.println("Data berhasil dikirim");
    Serial.println("Response: " + payload);
  } else {
    // Tampilkan pesan kesalahan
    Serial.println("Error: " + String(httpCode));
  }

  // Tutup koneksi
  http.end();
}

void setup() {
  Serial.begin(115200);
  connect_wifi();
  dht.begin();
}

void loop() {
  send_data_to_web(get_temperature_data(), get_humidity_data(), get_air_quality_data());
  delay(5000);
}
