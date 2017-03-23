/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Motores.h
 * Author: str-har-pc
 *
 * Created on 16 de enero de 2017, 12:40
 */

#ifndef MOTORES_H
#define MOTORES_H

#include <stdint.h>
#include <iostream>
#include "Definiciones.h"
#include "Variables.h"
#include <pigpio.h>

using namespace std;

class Motores {
public:
    uint8_t pinMotor[8] = {17, 27, 22, 10, 9, 11, 0, 5}; // valor PWM para cada uno de los 4 motores
    int tipoDrone;
    uint8_t numMotores;
    MotorsData motores;
    Motores();
    Motores(const Motores& orig);
    bool Armar();
    bool Apagar();
    bool Actualizar();
    virtual ~Motores();
private:

};

#endif /* MOTORES_H */

