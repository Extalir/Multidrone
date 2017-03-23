/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Variables.h
 * Author: str-har-pc
 *
 * Created on 13 de enero de 2017, 12:19
 */

#ifndef VARIABLES_H
#define VARIABLES_H

#include <string>
#include "Barometro/BMP085.h"
#include "Magnometro/HMC5883L.h"
#include "MPU/MPU6050.h"

using namespace std;

#define PITCH 0
#define ROLL 1
#define YAW 2
#define VEL 3 // velocidad de desplazamiento del dron
#define VEL_ALT 4 // velocidad de ascenso y descenso del dron


#define X 0
#define Y 1
#define Z 2

#define GYRO_FACTOR  1 / 32.8
#define RADIANS_TO_DEGREES 57.2958

struct AccGyroRawData {
    short int ax, ay, az;
    short int gx, gy, gz;
};

struct OffSetMpu {
    int accX, accY, accZ;
    int gyroX, gyroY, gyroZ;
};

struct MagnRawData {
    short int mx, my, mz;
};

struct IMU {
    MPU6050 mpu;
    HMC5883L mag;
    BMP085 baro;
};

struct ImuData {
    double angle[3];
    double gyroRate[3];
    double vel;
    double velAlt;
    double altBaro;
    double altUltSensor;
    double altInfSensor;
};

struct MotorsData {
    unsigned short int valPwmMotor[8];

    int minValMotor;
    int maxValMotor;

    int minThrottle;
    int maxThrottle;

    int throttleActual; // aceleracion vertical inicial

    bool armado;
};

struct Var_PID {
    float Kp, Ki, Kd;
    float Iterm, Imax, lastInput, lastDinput;
    float outPut;
    float setPoint;
    float outMax;
    unsigned long lastTime;
};

struct User_Data {
    struct AccGyroRawData accGyroData;
    struct MagnRawData magnRawData;
    struct ImuData imuData;
    struct MotorsData motorsData;
    struct Var_PID varPids[5];
    bool readVar, writeVar;
};

struct DatosGPS {
    double latitud = 0, longitud = 0, altitud = 0, velocidad = 0;
    string fecha = "";
    int numSatelites = 0;
    int estadoGps = 0;
};
#endif /* VARIABLES_H */

