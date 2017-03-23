/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BMP085.h
 * Author: str-har-pc
 *
 * Created on 11 de marzo de 2016, 02:58 PM
 */

#ifndef BMP085_H
#define BMP085_H

#include <stdint.h>
#include <string.h>
#include <pigpio.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include "../I2C/I2Cdev.h"
#include "../Funciones.h"

#define BMP085_I2C_ADDRESS 0x77

#define TEMPERATURE 0
#define PRESSURE 1
#define OVER_SAMPLING_SETTING 1 // use to be 3

using namespace std;

class BMP085 {
public:
    BMP085();
    BMP085(const BMP085& orig);

    void initializeBaro();
    const float getRelativeBaroAltitude();
    float getBaroGroundAltitude();
    float getBaroAltitude();
    void measureGroundBaro();
    void measureBaro();

    I2Cdev i2cBMP085;

    virtual ~BMP085();
private:

    unsigned long vehicleState;

    float baroAltitude;
    float baroRawAltitude;
    float baroGroundAltitude;
    float baroSmoothFactor;

    uint8_t overSamplingSetting;
    int16_t ac1 , ac2 , ac3;
    uint16_t ac4 , ac5 , ac6;
    int16_t b1, b2, mb, mc, md;
    int32_t pressure;
    int32_t rawPressure, rawTemperature;
    uint8_t pressureCount;
    float pressureFactor;
    bool isReadPressure;
    float rawPressureSum;
    uint8_t rawPressureSumCount;

    void requestRawPressure();
    long readRawPressure();
    void requestRawTemperature();
    unsigned int readRawTemperature();
    void measureBaroSum();
    void evaluateBaroAltitude();

    uint8_t buff[24];
};

#endif /* BMP085_H */