#pragma once
#include <Adafruit_AHTX0.h>
#include <Adafruit_BusIO_Register.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_I2CRegister.h>
#include <Wire.h>
#include <PMS.h>

int Timer = 0;
int TimeInterval = 0;
int PM1 = 0;
int PM25 = 0;
int PM10 = 0;
float Temperature = 0;
float Humidity = 0;