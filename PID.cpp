/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PID.cpp
 * Author: str-har-pc
 * 
 * Created on 13 de enero de 2017, 13:12
 */
#include <pigpio.h>
#include "PID.h"

PID::PID(const PID& orig) {
}

PID::PID(void) {
    Hz = 20;
    filter = 7.9577e-3;
}

bool PID::ResetPID(struct Var_PID* PID) {
    PID->Kp = PID->Ki = PID->Kd = 0;
    PID->Iterm = PID->lastDinput = PID->lastInput = 0;
    PID->lastTime = time_time() * 1000;
    PID->Imax = 0;
    PID->outMax = PID->outPut = 0;
    PID->setPoint = 0;
    return true;
}

void PID::LowResetPID(struct Var_PID* PID) {
    PID->Iterm = PID->lastDinput = PID->lastInput = 0;
    PID->lastTime = time_time() * 1000;
    PID->outPut = 0;
}
// Inicia el PID con los valores que le asignes

bool PID::InitPID(struct Var_PID* PID, float kp, float ki, float kd, float setpoint, float imax, float outmax) {
    if (kp < 0 || ki < 0 || kd < 0 || outmax < 0 || imax < 0)
        return false;
    PID->Kp = kp; // Ganancia Kp
    PID->Ki = ki; // Ganancia Ki
    PID->Kd = kd; // Ganancia Kd
    PID->Imax = imax; // Maximo valor para la integral
    PID->outMax = outmax; // Maximo valor de salida del PID
    PID->setPoint = setpoint; // Valor al que deseas llegar
    return true;
}

// Calcula la salida del PID tomando en cuenta que el input es el: setPoint - la posicion actual = error

void PID::CalculatePID(struct Var_PID* PID, float setpoint, double input) {
    double error;
    double dInput = 0;
    unsigned long now_t = time_time() * 1000;

    double timeChange = (double) (now_t - PID->lastTime); // timeChange = diferencial de tiempo
    timeChange /= 1000; // Ya que son milisegundos pasarlos a segundos

    PID->lastTime = now_t;

    error = setpoint - input;

    if (abs(PID->Ki) > 0) {
        PID->Iterm += (float) (PID->Ki * error * timeChange); // calculo de la parte integral
        if (PID->Iterm > PID->Imax)
            PID->Iterm = PID->Imax; // Condiciones para limitar el valor de la parte integral a un valor maximo
        else if (PID->Iterm < -PID->Imax)
            PID->Iterm = -PID->Imax; // o minimo para evitar sobresaltos si se cambia el valor de la ganancia Ki en pleno funcionamiento
    }

    if (abs(PID->Kd) > 0) {
        dInput = (error - PID->lastInput) / timeChange; // calculo de la parte derivativa
        dInput = PID->lastDinput + (timeChange / (timeChange + filter)) * (dInput - PID->lastDinput); // En mi caso como el movimiento de la posicon es radial agregue esta linea                                                                                            // que es un filtro, si te da fallas omitela
    }

    PID->outPut = (PID->Kp * error) + PID->Iterm + (PID->Kd * dInput); // Calculo de la salida

    if (PID->outPut > PID->outMax)
        PID->outPut = PID->outMax; // Y al igual que la integral limitamos la salida a un valor maximmo
    else if (PID->outPut < -PID->outMax)
        PID->outPut = -PID->outMax; // y minimo.

    PID->lastInput = error;
    PID->lastDinput = dInput;
}

PID::~PID(void) {
}
