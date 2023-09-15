#include <Arduino.h>
#include <FastBot.h>  // telegram bot library
#include "OTA.h"  // used for OTA updates https://github.com/SensorsIot/ESP32-OTA

#define WIFI_SSID "YOUR WIFI NAME"
#define WIFI_PASS "YOUR WIFI PASSWORD"
#define BOT_TOKEN "YOUR TELEGRAM API TOKEN"  // telegram bot api token
#define CHAT_ID "YOUR TELEGRAM CHAT ID"  // telegram chat id
#define Threshold 50  // how sensitive the touch detection should be, higher == more sensitive

unsigned long long sleep_duration = 2592000000000;    // 30 days
// unsigned long long sleep_duration = 3600000008;    // 1 hour
// unsigned long long sleep_duration = 86400000192; // ~24 hours

FastBot bot(BOT_TOKEN);

RTC_DATA_ATTR int bootCount = 0;  // save boot count in rtc memory
touch_pad_t touchPin;
uint32_t entry;

void connectWiFi();
void send_message();
void callback();
void send_update();

void setup() {
  pinMode(27, INPUT_PULLDOWN);
  if (digitalRead(27) == 0)
  {
    ++bootCount;
    if (bootCount == 1)
      touchAttachInterrupt(T3, callback, Threshold);
    else if (bootCount > 1)
    {
      esp_sleep_wakeup_cause_t wakeup_reason;
      wakeup_reason = esp_sleep_get_wakeup_cause();
      if (wakeup_reason == ESP_SLEEP_WAKEUP_TOUCHPAD)
        send_message();
      else
        send_update();
    }
    esp_sleep_enable_touchpad_wakeup();
    esp_sleep_enable_timer_wakeup(sleep_duration);
    esp_deep_sleep_start();  // go into deep sleep
    }
  else 
  {
    Serial.begin(9600);
    setupOTA("TemplateSketch", WIFI_SSID, WIFI_PASS);
  }
}

void loop()  // will only be called for OTA update 
{
  entry = micros();
  ArduinoOTA.handle();
  TelnetStream.println(micros()-entry);
  TelnetStream.println("Loop");
  delay(1000);
}

void callback()
{
  return ;
}

void send_message(){
  connectWiFi();
  bot.setChatID(CHAT_ID);
  bot.setTextMode(FB_TEXT);    
  bot.sendMessage(F("THE METAL HAS BEEN MOVED! ACT ACCORDINGLY!"));
}

void send_update()
{
  connectWiFi();
  bot.setChatID(CHAT_ID);
  bot.setTextMode(FB_TEXT);    
  bot.sendMessage(F("I am still alive. Have a great day :D"));
}

void connectWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    if (millis() > 30000) 
    {
      esp_sleep_enable_touchpad_wakeup();
      esp_sleep_enable_timer_wakeup(sleep_duration);
      esp_deep_sleep_start();
    }
  }
}
