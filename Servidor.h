/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Servidor.h
 * Author: str-har-pc
 *
 * Created on 13 de enero de 2017, 12:21
 */

#ifndef SERVIDOR_H
#define SERVIDOR_H

#include <string>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <vector>
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <cstring>


#include "Variables.h"
#include "Gps.h"
#include "PlanVuelo.h"

using namespace std;

class Servidor {
public:
    Servidor();
    Servidor(int tPuerto);
    Servidor(struct User_Data* _userData, Gps* gps);
    Servidor(const Servidor& orig);
    void Configurar(char* ip, int puerto);
    void Configurar(int puerto);
    int Iniciar();
    int Ejecutar();
    int Leer(int sockfd, char* buffer);
    int LeerLinea(int sockfd, string* buffer);
    int Enviar(int sockfd, char* buffer);
    int Enviar(string datos);
    bool CheckConex();
    void ObtenerPlanVuelo(PlanVuelo plan);
    virtual ~Servidor();

    User_Data* userData;
    Gps* gps;
private:
    
    int puerto;
    string ip;
    char buffer[128];
    struct sockaddr_in serv_addr, cli_addr;
    int sockfd, newsockfd, clilen;
    bool clConet;
    void ProsComandos(string buff);
};

#endif /* SERVIDOR_H */

