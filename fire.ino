#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

String account_sid = "YOUR_ACCOUNT_SID";
String auth_token = "YOUR_AUTH_TOKEN";
String from_number = "+1234567890";   // Twilio number
String to_number = "+911234567890";   // Your number

int flamePin = 4;
bool alertSent = false;

void sendSMS() {
  HTTPClient http;
  String url = "https://api.twilio.com/2010-04-01/Accounts/" + account_sid + "/Messages.json";

  http.begin(url);
  http.setAuthorization(account_sid.c_str(), auth_token.c_str());
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  String postData = "From=" + from_number +
                    "&To=" + to_number +
                    "&Body=🔥 Fire Detected! Immediate Attention Required!";

  int httpResponseCode = http.POST(postData);
  Serial.print("HTTP Response Code: ");
  Serial.println(httpResponseCode);

  http.end();
}

void setup() {
  Serial.begin(115200);
  pinMode(flamePin, INPUT);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected to WiFi");
}

void loop() {
  int flameState = digitalRead(flamePin);

  if (flameState == LOW && !alertSent) {
    Serial.println("🔥 Flame Detected!");
    sendSMS();
    alertSent = true;
  }

  if (flameState == HIGH) {
    alertSent = false;
  }

  delay(500);
}
