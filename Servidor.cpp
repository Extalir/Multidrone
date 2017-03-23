/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Servidor.cpp
 * Author: str-har-pc
 * 
 * Created on 13 de enero de 2017, 12:21
 */

#include "Servidor.h"

Servidor::Servidor() {
    puerto = 0, ip = "";
    sockfd = 0, newsockfd = 0, clilen = 0;
    clConet = false;
}

Servidor::Servidor(int tPuerto) {
    puerto = tPuerto, ip = "";
    sockfd = 0, newsockfd = 0, clilen = 0;
    clConet = false;
}

Servidor::Servidor(User_Data* _userData, Gps* _gps) {
    userData = _userData;
    gps = _gps;
    puerto = 0;
    ip = "";
    sockfd = 0, newsockfd = 0, clilen = 0;
    clConet = false;
}

void Servidor::Configurar(char* ip, int puerto_t) {
    bzero((char *) &serv_addr.sin_zero, sizeof (serv_addr.sin_zero));
    puerto = puerto_t;
    serv_addr.sin_family = inet_addr(ip);

    serv_addr.sin_port = htons(puerto);
}

void Servidor::Configurar(int tPuerto) {
    bzero((char *) &serv_addr.sin_zero, sizeof (serv_addr.sin_zero));
    cout << "Configuracion servidor\r\n";
    puerto = tPuerto;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(puerto);
}

int Servidor::Iniciar() {
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        cout << "ERROR Abirendo socket \r\n";
        return -1;
    }
    if (serv_addr.sin_port == 0) {
        cout << "ERROR Puerto no configurado \r\n";
        return -1;
    }
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof (serv_addr)) < 0) {
        cout << "ERROR on binding \r\n";
        close(sockfd);
        return -1;
    }
    listen(sockfd, 5);
    return 0;
}

int Servidor::Ejecutar() {
    int data = 0;
    string _buff = "";
    while (1) {
        cout << "Esperando por cliente... \r\n";
        clilen = sizeof (cli_addr);
        if ((newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, (socklen_t*) & clilen)) < 0) {
            cout << "ERROR on accept \r\n";
            return -1;
        }
        cout << "Nuevo comunicacion para cliente \r\n";
        clConet = true;
        while (1) {
            data = LeerLinea(newsockfd, &_buff);
            if (data <= 0) {
                close(newsockfd);
                break;
            }
            cout << "leido: " << _buff << "\r\n";
            ProsComandos(_buff);
            _buff.clear();
        }
        close(newsockfd);
        clConet = false;
    }
}

int Servidor::Leer(int sockfd, char* _buffer) {
    int n = 0;
    while ((n = read(sockfd, _buffer, 1024)) < 0) {
        cout << "Error al leer del cliente \r\n";
        return -1;
    }
    _buffer[n] = '\0';

    return n;
}

int Servidor::LeerLinea(int sockfd, string* _buffer) {
    int n = 0;
    char b[128] = {0};
    while (b[0] != '$') {
        try {
            n = recv(sockfd, b, 128, 0);
            if (n < 0) {
                cout << "Error al leer del cliente \r\n";
                return -1;
            }
            _buffer->append(b);
            if (_buffer->find('$') > 0)
                break;
        } catch (int e) {
            cout << "Error al leer \r\n";
        }
    }
    return n;
}

int Servidor::Enviar(int sockfd, char* _buffer) {
    int n;
    try {
        if ((n = send(sockfd, _buffer, strlen(_buffer), 0)) < 0) {
            cout << "Error al escribir al cliente \r\n";
            return -1;
        }
    } catch (int e) {
        cout << "Error al escribir \r\n";
    }
    //_buffer[n] = '\0';
    return 0;
}

int Servidor::Enviar(string datos) {
    char *temp = &datos[0];
    return Enviar(newsockfd, temp);
}

bool Servidor::CheckConex() {
    return clConet;
}

void Servidor::ObtenerPlanVuelo(PlanVuelo plan) {
}

Servidor::Servidor(const Servidor& orig) {
}

Servidor::~Servidor() {
    close(clilen);
    close(newsockfd);
    close(sockfd);
}

void Servidor::ProsComandos(string buff) {
}