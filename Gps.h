/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Gps.h
 * Author: str-har-pc
 *
 * Created on 13 de enero de 2017, 14:49
 */

#ifndef GPS_H
#define GPS_H

#include <string>
#include <cmath>
#include <vector>
#include "Serial.h"
#include "Variables.h"
#include "Funciones.h"

using namespace std;

class Gps {
public:

    struct Coordenada {
        double latitud;
        double longitud;
        double altura;
        double velocidad;
    };
    char* puertoSerial;

    Gps();
    Gps(const Gps& orig);

    int Conectar(char *_port, int baud);
    int Desconectar();

    int ProscDatos(string datos);
    void Ejecutar();

    double A_Radianes(double val);
    double A_Grados(double val);

    double DistanciaPaP(double lat1, double long1, double lat2, double long2);
    double DireccionPaP(double lat1, double long1, double lat2, double long2);

    double obtenerLatitud();
    double obtenerLongitud();
    double obtenerAltitud();
    string obtenerFecha();

    int obtenerEstadoGps();
    double obtenerVelocidad();
    double obtenerVelocidadLatitud();
    double obtenerVelocidadLongitud();
    int obtenerNumSatelites();

    void VelocidadGPS(double lat1, double long1, double lat2, double long2);

    void ObtenerDatosGPS(struct DatosGPS* gpsDatos);

    virtual ~Gps();
private:
    bool signoLat, signoLong;

    double prevLat = 0, prevLong = 0;
    double prevLatVel = 0, prevLongVel = 0;
    double velLatitud = 0, velLongitud = 0;

    vector<Coordenada> listaCoordenadas;
    struct DatosGPS datosGps;
    Serial serial;
};

#endif /* GPS_H */

