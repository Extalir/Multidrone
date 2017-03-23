/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Serial.cpp
 * Author: str-har-pc
 * 
 * Created on 16 de enero de 2017, 11:14
 */

#include <vector>

#include "Serial.h"

Serial::Serial() {
    uart0_filestream = -1;
    //*port=0;
    baud = 0;
    contError = 0;
}

int Serial::Setup(char* _port, int _baud) {
    switch (_baud) {
        case 1200:
            baud = B1200;
            break;
        case 2400:
            baud = B2400;
            break;
        case 4800:
            baud = B4800;
            break;
        case 9600:
            baud = B9600;
            break;
        case 19200:
            baud = B19200;
            break;
        case 38400:
            baud = B38400;
            break;
        case 57600:
            baud = B57600;
            break;
        case 115200:
            baud = B115200;
            break;
        case 230400:
            baud = B230400;
            break;
    }
    port = _port;

    //OPEN THE UART
    //The flags (defined in fcntl.h):
    //	Access modes (use 1 of these):
    //		O_RDONLY - Open for reading only.
    //		O_RDWR - Open for reading and writing.
    //		O_WRONLY - Open for writing only.
    //
    //	O_NDELAY / O_NONBLOCK (same function) - Enables nonblocking mode. When set read requests on the file can return immediately with a failure status
    //											if there is no input immediately available (instead of blocking). Likewise, write requests can also return
    //											immediately with a failure status if the output can't be written immediately.
    //
    //	O_NOCTTY - When set and path identifies a terminal device, open() shall not cause the terminal device to become the controlling terminal for the process.
    //uart0_filestream = open(port, O_RDWR | O_NOCTTY | O_NDELAY);		//Open in non blocking read/write mode
    uart0_filestream = open(port, O_RDWR | O_NOCTTY);
    if (uart0_filestream == -1) {
        //ERROR - CAN'T OPEN SERIAL PORT
        cout << "Error - Unable to open UART.  Ensure it is not in use by another application \r\n";
        close(uart0_filestream);
        return -1;
    }

    //CONFIGURE THE UART
    //The flags (defined in /usr/include/termios.h - see http://pubs.opengroup.org/onlinepubs/007908799/xsh/termios.h.html):
    //	Baud rate:- B1200, B2400, B4800, B9600, B19200, B38400, B57600, B115200, B230400, B460800, B500000, B576000, B921600, B1000000, B1152000, B1500000, B2000000, B2500000, B3000000, B3500000, B4000000
    //	CSIZE:- CS5, CS6, CS7, CS8
    //	CLOCAL - Ignore modem status lines
    //	CREAD - Enable receiver
    //	IGNPAR = Ignore characters with parity errors
    //	ICRNL - Map CR to NL on input (Use for ASCII comms where you want to auto correct end of line characters - don't use for bianry comms!)
    //	PARENB - Parity enable
    //	PARODD - Odd parity (else even)
    struct termios options;
    tcgetattr(uart0_filestream, &options);
    options.c_cflag = _baud | CS8 | CLOCAL | CREAD | CRTSCTS; //<Set baud rate
    options.c_iflag = IGNPAR;
    options.c_oflag = 0;
    options.c_lflag = 0;
    tcflush(uart0_filestream, TCIFLUSH);
    tcsetattr(uart0_filestream, TCSANOW, &options);

    contError = 0;
    return 0;
}

int Serial::Send(unsigned char* p_tx_buffer) {
    unsigned char tx_buffer[20];

    p_tx_buffer = &tx_buffer[0];

    if (uart0_filestream != -1) {
        int count = write(uart0_filestream, &tx_buffer[0], (p_tx_buffer - &tx_buffer[0])); //Filestream, bytes to write, number of bytes to write
        if (count < 0) {
            cout << "UART TX error\r\n";
            return -1;
        }
    }
    return 0;
}



string Serial::Recive() {
    string buff = "";
    char cC[2];
    int dataAvailable = 0;
    //timeStart=millis();
    if (uart0_filestream != -1) {
        if (ioctl(uart0_filestream, FIONREAD, &dataAvailable) > -1 && dataAvailable > 16) {
            // Read up to 255 characters from the port if they are there
            for (int i = 0; i < dataAvailable; i++) {
                int rx_length = read(uart0_filestream, (void *) cC, 1);
                if (rx_length > 0) {
                    buff += cC[0];
                    if (cC[0] == '\n') {
                        contError = 0;
                        return buff;
                    }
                }
            }
        }
    }
    contError++;
    return "$ERROR%\r\n";
}


int Serial::Close() {
    try {
        close(uart0_filestream);
    } catch (int ex) {
        cout << "Error No. " << ex << " al cerrar puerto serial \r\n";
        return -1;
    }
    return 0;
}

Serial::Serial(const Serial& orig) {
}

Serial::~Serial() {
    close(uart0_filestream);
}

