/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Serial.h
 * Author: str-har-pc
 *
 * Created on 16 de enero de 2017, 11:14
 */

#ifndef SERIAL_H
#define SERIAL_H

#include <unistd.h>   //Used for UART
#include <fcntl.h>   //Used for UART
#include <termios.h> 
#include <string>
#include <iostream>
#include <sys/ioctl.h>
using namespace std;

class Serial {
public:
    Serial();
    Serial(const Serial& orig);
    int Setup(char *_port, int _baud);
    int Send(unsigned char *p_tx_buffer);
    int Send(string tx_buffer);
    string Recive();
    int Close();
    virtual ~Serial();
    int contError;
private:
    int uart0_filestream = -1;
    char *port;
    int baud;
};

#endif /* SERIAL_H */

