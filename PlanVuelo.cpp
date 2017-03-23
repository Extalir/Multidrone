/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PlanVuelo.cpp
 * Author: str-har-pc
 * 
 * Created on 16 de enero de 2017, 11:29
 */

#include "PlanVuelo.h"

PlanVuelo::PlanVuelo() {
}

PlanVuelo::PlanVuelo(double latitud_t, double longitud_t, double altura_t, double velocidad_t, double espera_t) {
    latitud = latitud_t;
    longitud = longitud_t;
    altura = altura_t;
    velocidad = velocidad_t;
    espera = espera_t;
}

double PlanVuelo::ObtenerAltura() {
    return altura;
}

double PlanVuelo::ObtenerLatitud() {
    return latitud;
}

double PlanVuelo::ObtenerLongitud() {
    return longitud;
}

double PlanVuelo::ObtenerVelocidad() {
    return velocidad;
}

PlanVuelo::PlanVuelo(const PlanVuelo& orig) {
}

PlanVuelo::~PlanVuelo() {
}

