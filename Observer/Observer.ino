#include <Arduino.h>
#include "M5StickCPlus.h"
#include <WiFiClientSecure.h>
/*
When this code write to M5Stick, remove GND pin from M5Stick.
Then Err won't occurred
*/
//LED of M5StickC voltage is opposite to M5Stack
const char* ssid     = "";//<-- WiFi SSID
const char* password = "";//<-- WiFi Password
const char* host     = "notify-api.line.me";
const char* token    = "";//<-- LINENotifyToken
#define DOOR_TIME 12 //hour
#define LED_PIN 10
#define DOOR_PIN 26

boolean line_notify(String msg) {
  WiFiClientSecure client;
  client.setInsecure();
  if(!client.connect(host, 443)) {
    Serial.println("connect error!");
    return false;
  }
  String query = String("message=") + msg;
  String request = String("")
              + "POST /api/notify HTTP/1.1\r\n"
              + "Host: " + host + "\r\n"
              + "Authorization: Bearer " + token + "\r\n"
              + "Content-Length: " + String(query.length()) +  "\r\n"
              + "Content-Type: application/x-www-form-urlencoded\r\n\r\n"
              + query + "\r\n";
  client.print(request);
  return true;
}

int starttime;
int dtime=DOOR_TIME*3600*1000;
int dflag=2;
int deb=30*1000;
void setup() {
    M5.begin();
    M5.Lcd.setRotation(3);
    pinMode(DOOR_PIN, INPUT_PULLUP);
    pinMode(LED_PIN,OUTPUT);
    M5.Lcd.fillScreen(BLACK);
    //wifi
    M5.Lcd.printf("WIFI START:%s ", ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        M5.Lcd.println(".");
    }
    M5.Lcd.print(" - READY");
    starttime=millis();
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setTextSize(3);
    M5.Lcd.println("Standby");
    //For debug
    //dtime=deb;
}

void loop(){
    M5.update();
    if(millis()-starttime>dtime){
        digitalWrite(LED_PIN, LOW);
        String lm=DOOR_TIME+String("時間反応がありませんでした。確認して下さい。");
        line_notify(lm);
        M5.Beep.beep();
        delay(1000);
        M5.Beep.mute();
        starttime=millis();
    }
    if(M5.BtnB.isPressed()) {
        dflag++;
    }
    if(dflag%2==1&&digitalRead(DOOR_PIN)==1){
        digitalWrite(LED_PIN, LOW);
        M5.Lcd.fillScreen(GREEN);
        M5.Lcd.setCursor(10,40);
        M5.Lcd.setTextColor(BLACK);
        M5.Lcd.setTextSize(5);
        M5.Lcd.print("Open");
    }else if(dflag%2==1){
        digitalWrite(LED_PIN, HIGH);
        M5.Lcd.fillScreen(BLACK);
        M5.Lcd.setCursor(10,40);
        M5.Lcd.setTextColor(WHITE);
        M5.Lcd.setTextSize(5);
        M5.Lcd.print("Close");
    }else{
        digitalWrite(LED_PIN, HIGH);
        M5.Lcd.fillScreen(BLACK);
        M5.Lcd.setCursor(10,40);
        M5.Lcd.setTextColor(WHITE);
        M5.Lcd.setTextSize(5);
        M5.Lcd.print(".");
    }
    if(digitalRead(DOOR_PIN)==1){
        starttime=millis();
    }
    if(M5.BtnA.isPressed()) {
        M5.Lcd.fillScreen(BLUE);
        M5.Lcd.setCursor(10,40);
        M5.Lcd.setTextColor(BLACK);
        M5.Lcd.setTextSize(5);
        M5.Lcd.print("Reset");
        starttime=millis();
        digitalWrite(LED_PIN, HIGH);
        delay(1000);
    }
    delay(1000);
}