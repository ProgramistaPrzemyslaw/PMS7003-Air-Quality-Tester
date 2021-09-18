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

#define N 4
#define M 48

int Timer = 0;
int TimeInterval = 45000;
float PM1 = 0;
float PM25 = 0;
float PM10 = 0;
float Temperature = 0;
float Humidity = 0;
int setHour = 0;
int setMinute = 0;
int sec = 0;
int minute = 0;
int hour = 0;
int sleepPin = 12;
bool readyToRead = false;
float array[N][M];
float last24hAverage[N];


void addToArray(float Temperature, float PM1, float PM25, float PM10);
void handleRoot();
void calculateAverage();
void arrayToString();

void drawGraph();