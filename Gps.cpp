/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Gps.cpp
 * Author: str-har-pc
 * 
 * Created on 13 de enero de 2017, 14:49
 */

#include "Gps.h"

Gps::Gps() {
    datosGps.estadoGps = 1;
    puertoSerial = "";
}

void Gps::Ejecutar() {
    string datos = "";
    vector<string> * fifoLines;
    int cont = 0;
    while (1) {
        datos = "";
        if (serial.contError >= 10) {
            serial.Close();
            serial.Setup(puertoSerial, B38400);
            cout << "Reinicio de serial \r\n";
        }
        datos = serial.Recive();
        //cout << ">>" << datos;
        if ((datos.find("$GPGGA") >= 0) || (datos.find("$GPVTG") >= 0)) {
            ProscDatos(datos);
        }
        usleep(200000);
    }
}

int Gps::Conectar(char *puerto, int baud) {
    return serial.Setup(puerto, baud);
}

int Gps::Desconectar() {
    return serial.Close();
}

int Gps::ProscDatos(string datos) {
    vector<string> listDatos = Split(datos, ',');
    double tempVal = 0;
    /*for (int i = 0; i < listDatos.size(); i++)
        cout << listDatos[i] << ", ";
    cout << "\r\n";*/
    int pos = datos.find("$GPGGA");
    if (pos >= 0) {
        try {
            if (listDatos[0] == "$GPGGA" && listDatos[6] == "1" || listDatos[6] == "2") {
                static Coordenada punto;
                datosGps.fecha = listDatos[1];
                cout << "fecha: " << datosGps.fecha << "\r\n";
                
                cout.precision(10);
                stringstream(listDatos[2])>>tempVal;
                datosGps.latitud = StrToDecimal(tempVal, listDatos[3]);
                cout << "latitud: " << datosGps.latitud << "\r\n";

                stringstream(listDatos[4])>>tempVal;
                datosGps.longitud = StrToDecimal(tempVal, listDatos[5]);
                cout << "longitud: " << datosGps.longitud << "\r\n";

                stringstream(listDatos[7])>>datosGps.numSatelites;
                cout << "numSatelites: " << datosGps.numSatelites << "\r\n";
                stringstream(listDatos[9])>>datosGps.altitud;
                cout << "altitud: " << datosGps.altitud << "\r\n";

                punto.latitud = datosGps.latitud;
                punto.longitud = datosGps.longitud;
                punto.altura = datosGps.altitud;
                punto.velocidad = datosGps.velocidad;

                if (prevLat == 0 && prevLong == 0) {
                    prevLat = datosGps.latitud;
                    prevLong = datosGps.longitud;
                    listaCoordenadas.push_back(punto);
                } else {
                    if (abs(DistanciaPaP(prevLat, prevLong, datosGps.latitud, datosGps.longitud)) > 1) {
                        prevLat = datosGps.latitud;
                        prevLong = datosGps.longitud;
                        listaCoordenadas.push_back(punto);
                    }
                }
                if (prevLatVel == 0 && prevLongVel == 0) {
                    prevLatVel = datosGps.latitud;
                    prevLongVel = datosGps.longitud;
                }

                // calcular la velocidad en el desplazamiento de la latitud y de la longitud en m/s.
                VelocidadGPS(prevLatVel, prevLongVel, datosGps.latitud, datosGps.longitud);
                prevLatVel = datosGps.latitud;
                prevLongVel = datosGps.longitud;

                datosGps.estadoGps = 3;
            } else if (listDatos[0] == "$GPGGA" && listDatos[6] == "0") {
                datosGps.estadoGps = 2;
            } else if (listDatos [0] == "$GPVTG" && datosGps.estadoGps == 3 && listDatos [5] != "") {
                stringstream(listDatos[5])>>datosGps.velocidad;
            }
        } catch (exception ex) {
            cout << ex.what() << "\r\n";

        }
    }
}

void Gps::VelocidadGPS(double lat1, double long1, double lat2, double long2) {
    double distLat = lat1 - lat2;
    double distLong = long1 - long2;

    double dt = 0;
    //dt = timerVel.Elapsed.TotalMilliseconds;
    //dt /= 1000;

    //timerVel.Restart ();

    distLat *= 111310;
    distLong *= 111310;

    velLatitud = distLat / dt;
    velLongitud = distLong / dt;
}

double Gps::DistanciaPaP(double lat1, double long1, double lat2, double long2) {

    double delta = Radianes(long1 - long2);
    double sdlong = sin(delta);
    double cdlong = cos(delta);
    lat1 = Radianes(lat1);
    lat2 = Radianes(lat2);
    double slat1 = sin(lat1);
    double clat1 = cos(lat1);
    double slat2 = sin(lat2);
    double clat2 = cos(lat2);

    delta = (clat1 * slat2) - (slat1 * clat2 * cdlong);
    delta *= delta;
    delta += ((clat2 * sdlong) * (clat2 * sdlong));
    delta = sqrt(delta);
    double denom = (slat1 * slat2) + (clat1 * clat2 * cdlong);
    delta = atan2(delta, denom);
    delta *= 6372795;
    //Console.WriteLine ("Distancia punto a punto:" + delta);
    return delta;
}

double Gps::DireccionPaP(double lat1, double long1, double lat2, double long2) {
    double dlon = Radianes(long2 - long1);
    lat1 = Radianes(lat1);
    lat2 = Radianes(lat2);
    double a1 = sin(dlon) * cos(lat2);
    double a2 = sin(lat1) * cos(lat2) * cos(dlon);
    a2 = cos(lat1) * sin(lat2) - a2;
    a2 = atan2(a1, a2);
    if (a2 < 0.0) {
        a2 += (PI * 2);
    }
    return Grados(a2);
}

double Gps::obtenerAltitud() {
    return datosGps.altitud;
}

double Gps::obtenerLatitud() {
    return datosGps.latitud;
}

double Gps::obtenerLongitud() {
    return datosGps.longitud;
}

string Gps::obtenerFecha() {
    return datosGps.fecha;
}

double Gps::obtenerVelocidad() {
    return datosGps.velocidad;
}

double Gps::obtenerVelocidadLatitud() {
    return velLatitud;
}

double Gps::obtenerVelocidadLongitud() {
    return velLongitud;
}

int Gps::obtenerEstadoGps() {
}

int Gps::obtenerNumSatelites() {
}

Gps::Gps(const Gps& orig) {
}

Gps::~Gps() {
}

