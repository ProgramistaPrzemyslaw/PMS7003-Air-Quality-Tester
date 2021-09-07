#pragma once
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#include <Adafruit_AHTX0.h>
#include <Adafruit_BusIO_Register.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_I2CRegister.h>
#include <Wire.h>
#include <PMS.h>

int Timer = 0;
int TimeInterval = 0;
float PM1 = 0;
float PM25 = 0;
float PM10 = 0;
float Temperature = 0;
float Humidity = 0;
int sec = millis()/1000;
int minute = sec/60;
int hour = minute/60;

void handleRoot();