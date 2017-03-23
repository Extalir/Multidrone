/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Drone.cpp
 * Author: str-har-pc
 * 
 * Created on 13 de enero de 2017, 12:20
 */

#include "Drone.h"

Drone::Drone() {
    //userData.varPids = pids;
    userData.readVar = false;
    userData.writeVar = false;
    server = Servidor(&userData, &gps);
}

bool Drone::InitMPU6050() {
    vector<int> offsets;
    imu.mpu.initialize();
    imu.mpu.setFullScaleAccelRange(MPU6050_ACCEL_FS_4);
    imu.mpu.setFullScaleGyroRange(MPU6050_GYRO_FS_1000);
    imu.mpu.setDLPFMode(MPU6050_DLPF_BW_5);

    offsets = LoadOffsetMpu();
    if (offsets[0] == -888888 || offsets[0] == -999999) {
        cout << "error al leer offsets\r\n";
        if (server.CheckConex())
            server.Enviar("$Error_offset");
        return -1;
    } else {
        imu.mpu.setXGyroOffset(offsets[0]);
        imu.mpu.setYGyroOffset(offsets[1]);
        imu.mpu.setZGyroOffset(offsets[2]);
        imu.mpu.setXAccelOffset(offsets[3]);
        imu.mpu.setYAccelOffset(offsets[4]);
        imu.mpu.setZAccelOffset(offsets[5]);
    }
    return 0;
}

bool Drone::InitSensors() {
    InitMPU6050();
    double t1 = time_time();
    if (imu.mpu.testConnection())
        cout << "Configurado mpu6050\r\n";
    else {
        cout << "Error el configurar mpu6050\r\n";
        return false;
    }
    imu.mag.initialize();
    if (imu.mag.testConnection())
        cout << "Configurado magnometro\r\n";
    else {
        cout << "Error el configurar magnometro\r\n";
        return false;
    }
    imu.baro.initializeBaro();
    cout << "Configurado barometro\r\n";
    return true;
}

bool Drone::InitAll() {
    InitSensors();
    //init motores
    //init pids
    //init otros
    timer = time_time()*1000000;
}

void Drone::UpdateP_R_Y() {
    imu.mpu.getMotion6(&accGyroData.ax, &accGyroData.ay, &accGyroData.az, &accGyroData.gx, &accGyroData.gy, &accGyroData.gz);

    // Remove offsets and scale gyro data
    float gyroRate_X = accGyroData.gx * GYRO_FACTOR;
    float gyroRate_Y = accGyroData.gy * GYRO_FACTOR;
    float gyroRate_Z = accGyroData.gz * GYRO_FACTOR;

    imuData.gyroRate[ROLL] = gyroRate_X;
    imuData.gyroRate[PITCH] = gyroRate_Y * -1;
    imuData.gyroRate[YAW] = gyroRate_Z * -1;

    float accel_angle_y = atan(-1 * accGyroData.ax / sqrt(pow(accGyroData.ay, 2) + pow(accGyroData.az, 2))) * RADIANS_TO_DEGREES;
    float accel_angle_x = atan(accGyroData.ay / sqrt(pow(accGyroData.ax, 2) + pow(accGyroData.az, 2))) * RADIANS_TO_DEGREES;
    float accel_angle_z = 0;

    double dt = ((time_time()*1000000) - timer) / 1000000;
    //Serial.print("::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::");
    //Serial.println(dt * 1000);
    cout << dt << "\r\n";
    timer = time_time()*1000000;

    float gyro_angle_x = gyroRate_X * dt + prev_angle[ROLL];
    float gyro_angle_y = gyroRate_Y * dt + prev_angle[PITCH];
    //float gyro_angle_z = gyroRate_Z * dt + prev_angle[YAW];

    // Compute the drifting gyro angles
    unfiltered_gyro_angle[X] = gyroRate_X * dt + unfiltered_gyro_angle[X];
    unfiltered_gyro_angle[Y] = gyroRate_Y * dt + unfiltered_gyro_angle[Y];
    unfiltered_gyro_angle[Z] = gyroRate_Z * dt + unfiltered_gyro_angle[Z];

    // Apply the complementary filter to figure out the change in angle - choice of alpha is
    // estimated now.  Alpha depends on the sampling rate...
    const float alpha = 0.96;
    prev_angle[ROLL] = alpha * gyro_angle_x + (1.0 - alpha) * accel_angle_x;
    prev_angle[PITCH] = alpha * gyro_angle_y + (1.0 - alpha) * accel_angle_y;
    //prev_angle[YAW] = gyro_angle_z;  //Accelerometer doesn't give z-angle

    imuData.angle[ROLL] = prev_angle[ROLL];
    imuData.angle[PITCH] = prev_angle[PITCH] * -1;

    imu.mag.getHeading(&magData.mx, &magData.my, &magData.mz);

    float rollAngle = Radianes(imuData.angle[ROLL]);
    float pitchAngle = Radianes(imuData.angle[PITCH]);
    //float rollAngle = angle[ROLL] * DEG_TO_RAD;
    //float pitchAngle = angle[PITCH] * DEG_TO_RAD;

    float Bfy = magData.mz * sin(rollAngle) - magData.my * cos(rollAngle);
    float Bfx = magData.mx * cos(pitchAngle) + magData.my * sin(pitchAngle) * sin(rollAngle) + magData.mz * sin(pitchAngle) * cos(rollAngle);
    imuData.angle[YAW] = Grados(atan2(-Bfy, Bfx));
    imuData.angle[YAW] = filterSmooth(imuData.angle[YAW], prev_angle[YAW], 0.04);
    prev_angle[YAW] = imuData.angle[YAW];

    if (userData.readVar == false) {
        userData.writeVar = true;
        userData.accGyroData = accGyroData;
        userData.imuData = imuData;
        userData.magnRawData = magData;
        userData.writeVar = false;
    }
    cout << "Pitch:" << userData.imuData.angle[PITCH] << "\r\n";
    cout << "Roll:" << userData.imuData.angle[ROLL] << "\r\n";
    cout << "YAW:" << userData.imuData.angle[YAW] << "\r\n";
}

void Drone::Run() {
    dtLoop100hz = time_time()*1000;
    InitAll();
    while (1) {
        if ((time_time()*1000) - dtLoop100hz >= 10) {
            dtLoop100hz = time_time()*1000;
            Loop100hz();
        } else {
            usleep(250);
        }
    }
}

void Drone::Loop100hz() {
    UpdateP_R_Y();
}


void Drone::CalPIDs()
{
    
}
Drone::Drone(const Drone& orig) {
}

Drone::~Drone() {
}

