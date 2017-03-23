/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: str-har-pc
 *
 * Created on 13 de enero de 2017, 12:09
 */

#include <cstdlib>
#include <pigpio.h>
#include <cstdio>
#include "Drone.h"
#include "Gps.h"
#include "Servidor.h"

using namespace std;

Drone drone;

void *Gps_T(void *id) {
    drone.gps.Ejecutar();
    pthread_exit(NULL);
}

void *Servidor_T(void *obj) {
    drone.server.Iniciar();
    drone.server.Ejecutar();
    pthread_exit(NULL);
}

void *Drone_T(void *obj) {
    drone.Run();
    pthread_exit(NULL);
}

int main(int argc, char** argv) {
    pthread_t tDrone;
    pthread_t tServidor;
    pthread_t tGps;

    int vect1[4];
    vect1[0] = 1;
    vect1[1] = 2;
    vect1[2] = 3;
    vect1[3] = 4;

    drone.gps.puertoSerial = "/dev/ttyAMA0";
    drone.server.Configurar(5555);

    SavePIDs(vect1, "pitch");

    if (gpioInitialise() < 0) {
        cout << "pigpio initialisation failed\t" << stderr << "\r\n";
        return 1;
    }

    pthread_create(&tDrone, NULL, Drone_T, (void *) 1);
    pthread_create(&tServidor, NULL, Servidor_T, (void *) 2);
    pthread_create(&tGps, NULL, Gps_T, (void *) 3);

    pthread_join(tDrone, NULL);
    usleep(1000);
    pthread_join(tServidor, NULL);
    usleep(1000);
    pthread_join(tGps, NULL);

    cout << "Terminando programa \r\n";
    gpioTerminate();
    return 0;
}

