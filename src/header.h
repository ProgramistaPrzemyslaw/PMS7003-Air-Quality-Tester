//#pragma once
#ifndef HeaderGuard
#define HeaderGuard
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#include <string>

#include <Adafruit_AHTX0.h>
#include <Adafruit_BusIO_Register.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_I2CRegister.h>
#include <Wire.h>
#include <PMS.h>
#endif

#define N 4
#define M 48

extern int Timer;
extern int TimeInterval;
extern float PM1;
extern float PM25;
extern float PM10;
extern float Temperature;
extern float Humidity;
extern int sec;
extern int minute;
extern int hour;
extern int sleepPin;
extern int compensation;
extern bool readyToRead;
extern bool readyToChangeTime;
extern float array[N][M];
extern int TimeArray[2][M];
extern float last24hAverage[N];

void handleRoot();
void handleSetTime();
void handleSetGet();

void addToArray(float Temperature, float PM1, float PM25, float PM10);
void calculateAverage();
void arrayToString();
void addToTimeArray(int hour, int minute);

void drawGraphPM10();
void drawGraphPM25();
void drawGraphTemperature();

int compensatedMillis(int hour, int minute);
int getMaxValue(int index);
