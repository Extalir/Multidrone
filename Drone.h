/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Drone.h
 * Author: str-har-pc
 *
 * Created on 13 de enero de 2017, 12:20
 */

#ifndef DRONE_H
#define DRONE_H

#include "Variables.h"
#include "FuncionesImu.h"
#include "Servidor.h"

class Drone {
public:
    Drone();
    
    bool InitSensors();
    bool InitMPU6050();
    bool InitPIDs();
    bool InitAll();
    
    // Calcular la velocidad vertical.
    void CalAltVel();
    // Calcular la velocidad de navegacion.
    void CalNavVel();
    // Calcular la salida de los PID.
    void CalPIDs();
    // Calcular la posicion de pitch, roll y yaw.
    void UpdateP_R_Y();
    // Pasar el valor pwm a los motores.
    void UpdateMotors();
    
    void Run();
    
    void Loop100hz();
    void Loop30hz();
    void loop20hz();
    
    Drone(const Drone& orig);
    virtual ~Drone();
    
    User_Data userData;
    Gps gps;
    IMU imu;
    Servidor server;
private:
    double timer;
    double dtLoop100hz;
    
    AccGyroRawData accGyroData;
    MagnRawData magData;
    
    ImuData imuData;
    
    Var_PID pids[5];
    
    float unfiltered_gyro_angle[3];
    float prev_angle[3];
};

#endif /* DRONE_H */

