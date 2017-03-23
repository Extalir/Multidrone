/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Motores.cpp
 * Author: str-har-pc
 * 
 * Created on 16 de enero de 2017, 12:40
 */

#include "Motores.h"

Motores::Motores() {
    motores.armado = false;
    motores.maxThrottle = 2000;
    motores.minThrottle = 1000;
    motores.maxValMotor = 2300;
    motores.minValMotor = 800;
    motores.throttleActual = motores.minValMotor;
    
    for (int i = 0; i<sizeof ( motores.valPwmMotor); i++)
        motores.valPwmMotor[i] = 0;
    tipoDrone = Quadcoptero_X;
}

bool Motores::Armar() {
    switch (tipoDrone) {
        case Tricoptero:
            numMotores = 3;
            break;
        case Quadcoptero_cruz:
        case Quadcoptero_X:
            numMotores = 4;
            break;
        case Hexacoptero:
        case Hexacoptero_paralelo:
            numMotores = 6;
            break;
    }
    for (int i = 0; i < numMotores; i++) {
        try {
            gpioSetMode(pinMotor[i], PI_OUTPUT);
            time_sleep(0.001);
            gpioServo(pinMotor[i], motores.minValMotor);
        } catch (int ex) {
            cout << "Excepcion No. " << ex << "\r\n";
            cout << "Error al armar motor " << i << " en pin " << pinMotor[i] << "\r\n";
            return -1;
        }
    }
    return 0;
}

bool Motores::Apagar() {
    for (int i = 0; i < numMotores; i++) {
        try {
            gpioServo(pinMotor[i], motores.minValMotor);
        } catch (int ex) {
            cout << "Excepcion No. " << ex << "\r\n";
            cout << "Error al apagar motor " << i << "\r\n";
            return -1;
        }
    }
    return 0;
}

bool Motores::Actualizar() {
    for (int i = 0; i < numMotores; i++) {
        try {
            gpioServo(pinMotor[i], motores.valPwmMotor[i]);
        } catch (int ex) {
            cout << "Excepcion No. " << ex << "\r\n";
            cout << "Error al actualizar motor " << i << "\r\n";
            return -1;
        }
    }
    return 0;
}

Motores::Motores(const Motores& orig) {
}

Motores::~Motores() {
}

