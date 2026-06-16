#include <WiFi.h>
#include <ESP_Mail_Client.h>
#include <DHT.h>

// ===== WIFI =====
#define WIFI_SSID "***************"
#define WIFI_PASSWORD "***************"

// ===== EMAIL =====
#define SMTP_HOST "smtp.gmail.com"
#define SMTP_PORT 465

#define AUTHOR_EMAIL "***************"
#define AUTHOR_PASSWORD "***************"

#define RECIPIENT_EMAIL "***************"

// ===== SENSOR =====
#define DHTPIN 4
#define DHTTYPE DHT11

// ===== OUTPUTS =====
#define LED_PIN 2
#define BUZZER_PIN 5

DHT dht(DHTPIN, DHTTYPE);

// ===== THRESHOLDS =====
float tempHigh = 30.0;
float tempLow = 18.0;

float humHigh = 60.0;
float humLow = 30.0;

// ===== EMAIL TIMER =====
unsigned long lastEmailTime = 0;

const unsigned long emailInterval = 60000; // 60 seconds

// ===== SMTP SESSION =====
SMTPSession smtp;

// ===== EMAIL FUNCTION =====
void sendEmail(String msg) {

  SMTP_Message message;

  message.sender.name = "ESP32 Alert System";
  message.sender.email = AUTHOR_EMAIL;

  message.subject = "Environment Alert";

  message.addRecipient("User", RECIPIENT_EMAIL);

  message.text.content = msg.c_str();

  ESP_Mail_Session session;

  session.server.host_name = SMTP_HOST;
  session.server.port = SMTP_PORT;

  session.login.email = AUTHOR_EMAIL;
  session.login.password = AUTHOR_PASSWORD;

  session.time.ntp_server = "pool.ntp.org,time.nist.gov";
  session.time.gmt_offset = 5.5;
  session.time.day_light_offset = 0;

  Serial.println("Connecting to SMTP Server...");

  if (!smtp.connect(&session)) {

    Serial.println("SMTP Connection Failed!");
    Serial.println(smtp.errorReason());

    return;
  }

  if (!MailClient.sendMail(&smtp, &message)) {

    Serial.println("Email Sending Failed!");
    Serial.println(smtp.errorReason());
  }

  else {

    Serial.println("Email Sent Successfully!");
  }

  smtp.closeSession();
}

// ===== SETUP =====
void setup() {

  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  digitalWrite(LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  dht.begin();

  delay(2000);

  Serial.println("DHT11 Initialized");

  // ===== WIFI CONNECTION =====

  Serial.println("Connecting to WiFi");

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  int attempts = 0;

  while (WiFi.status() != WL_CONNECTED && attempts < 20) {

    delay(1000);

    Serial.print(".");

    attempts++;
  }

  if (WiFi.status() == WL_CONNECTED) {

    Serial.println("\nWiFi Connected!");

    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  }

  else {

    Serial.println("\nWiFi Connection Failed!");
  }
}

// ===== LOOP =====
void loop() {

  // ===== RECONNECT WIFI =====

  if (WiFi.status() != WL_CONNECTED) {

    Serial.println("WiFi Reconnecting...");

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    delay(5000);

    return;
  }

  // ===== READ SENSOR =====

  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  // ===== SENSOR ERROR CHECK =====

  if (isnan(temp) || isnan(hum)) {

    Serial.println("DHT SENSOR ERROR!");

    delay(2000);

    return;
  }

  // ===== SERIAL MONITOR =====

  Serial.println("\n====== SENSOR DATA ======");

  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.println(" °C");

  Serial.print("Humidity: ");
  Serial.print(hum);
  Serial.println(" %");

  // ===== DANGER CONDITION =====

  bool dangerCondition =
      (temp > tempHigh || temp < tempLow ||
       hum > humHigh || hum < humLow);

  // ===== ALERT ACTIVE =====

  if (dangerCondition) {

    digitalWrite(LED_PIN, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);

    Serial.println("ALERT ON");

    // ===== SEND EMAIL EVERY 30 SECONDS =====

    if (millis() - lastEmailTime >= emailInterval || lastEmailTime == 0) {

      String msg = "WARNING!\n\n";

      msg += "Temperature: ";
      msg += String(temp);
      msg += " °C\n";

      msg += "Humidity: ";
      msg += String(hum);
      msg += " %";

      sendEmail(msg);

      lastEmailTime = millis();

      Serial.println("EMAIL SENT");
    }
  }

  // ===== SAFE CONDITION =====

  else {

    digitalWrite(LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);

    Serial.println("ALERT OFF");
  }

  Serial.println("=========================");

  delay(2000);
}