#include <WiFi.h>
#include <HTTPClient.h>

#define WIFI_SSID "Wokwi-GUEST"
#define WIFI_PASSWORD ""

const String BASE_URL = "https://c9fc188c-bb7c-4f43-b537-dfd0da0b84e0-00-38t5gyss0hm8p.spock.replit.dev";

const int buzzerPin = 19;
const int ledPins[] = {15, 2, 0, 4};
const int botaoPins[] = {16, 17, 5, 18};

bool ledAtivo[4] = {false, false, false, false};
unsigned long lastDebounceTime[4] = {0, 0, 0, 0};
const unsigned long debounceDelay = 50;

void setup() {
  Serial.begin(115200);

  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW);

  for (int i = 0; i < 4; i++) {
    pinMode(botaoPins[i], INPUT_PULLUP);
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Conectando ao Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("\nWi-Fi conectado!");
}

void loop() {
  for (int i = 0; i < 4; i++) {
    if (digitalRead(botaoPins[i]) == LOW && !ledAtivo[i]) {
      if (millis() - lastDebounceTime[i] > debounceDelay) {
        digitalWrite(ledPins[i], HIGH);
        ledAtivo[i] = true;
        lastDebounceTime[i] = millis();

        Serial.printf("Botão %d pressionado. LED ligado.\n", i);

        HTTPClient http;
        String url = BASE_URL + "/solicitar/onibus" + String(i + 1);
        http.begin(url);
        http.POST("");
        http.end();
      }
    }
  }

  for (int i = 0; i < 4; i++) {
    if (ledAtivo[i]) {
      HTTPClient http;
      String url = BASE_URL + "/chegou/onibus" + String(i + 1);
      http.begin(url);
      int httpCode = http.GET();

      if (httpCode == 200) {
        String payload = http.getString();
        if (payload.indexOf("true") != -1) {
          digitalWrite(ledPins[i], LOW);
          ledAtivo[i] = false;

          tone(buzzerPin, 1000);
          delay(700);
          noTone(buzzerPin);

          Serial.printf("\u00d4nibus %d chegou. LED apagado.\n", i);

          HTTPClient httpReset;
          String resetUrl = BASE_URL + "/resetar/onibus" + String(i + 1);
          httpReset.begin(resetUrl);
          httpReset.POST("");
          httpReset.end();
        }
      }
      http.end();
    }
  }

  delay(500);
}
