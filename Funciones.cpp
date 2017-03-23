/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <sys/stat.h>
#include <sys/types.h>

#include "Funciones.h"

vector<string> Split(const string &s, char delim) {
    vector<string> elems;
    int cont = 0;
    char c;
    string data = "";
    while (cont < s.length()) {
        c = s[cont++];
        data += c;
        if (c == '\n' || c == delim || c == 'n') {
            data.erase(data.length() - 1, data.length());
            elems.push_back(data);
            data = "";
        }
    }
    return elems;
}

string ToString(double val) {
    ostringstream ss;
    string out;
    ss << val;
    out = ss.str();
    return out;
}

string ToString(int val) {
    ostringstream ss;
    string out;
    ss << val;
    out = ss.str();
    return out;
}

bool is_number(const string& s) {
    string::const_iterator it = s.begin();
    while (it != s.end() && isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

float filterSmooth(float currentData, float previousData, float smoothFactor) {
    if (smoothFactor != 1.0) //only apply time compensated filter if smoothFactor is applied
    {
        return (previousData * (1.0 - smoothFactor) + (currentData * smoothFactor));
    }
    return currentData; //if smoothFactor == 1.0, do not calculate, just bypass!
}

/*
double StrToDecimal(string strVal, string direc) {
    int posPunto = strVal.find('.', 0);
    double entero = 0, decimales = 0, valor = 0;
    stringstream(strVal.substr(0, posPunto))>>entero;
    stringstream(strVal.substr(posPunto + 1, strVal.size() - 1))>>decimales;
    decimales /= 60;
    valor = (entero / 100) + decimales;
    if (direc == "N" || direc == "E")
        valor *= 1;
    else
        valor *= -1;

    return valor;
}*/

double StrToDecimal(double valor, string direc) {
    double decimales;
    int entero;
    valor /= 100;
    entero = valor;
    decimales = (valor - entero);
    decimales /= 0.6;
    valor = entero + decimales;
    if (direc == "N" || direc == "E")
        valor *= 1;
    else
        valor *= -1;
    return valor;
}

double Radianes(double valor) {
    return (valor * PI) / 180;
}

double Grados(double valor) {
    return (valor * 180) / PI;
}

void SaveOffsetMpu(int * offsets) {
    ofstream myfile;
    string linea;
    string buffLines;
    myfile.open("/root/OffsetsMpu.txt");
    for (int i = 0; i < 6; i++) {
        linea = ToString(offsets[i]) + "\r\n";
        buffLines += linea;
    }
    myfile << buffLines;
    myfile.close();
}

vector<int> LoadOffsetMpu() {
    char buff[128] = "";
    ifstream myfile;
    vector<int> offsetMpu;
    int offset;
    myfile.open("/root/OffsetsMpu.txt");
    if (myfile.is_open()) {
        for (int i = 0; i < 6; i++) {
            try {
                myfile>>buff;
                stringstream(buff)>>offset;
                offsetMpu.push_back(offset);
                cout << buff << "\r\n";
            } catch (exception ex) {
                cout << "Error en linea: " << i << "\r\n";
                myfile.close();
                offsetMpu.clear();
                offsetMpu.push_back(-888888);
                return offsetMpu;
            }
        }
        myfile.close();
        return offsetMpu;
    } else
        cout << "Error al leer archivo OffsetsMpu.txt\r\n";
    offsetMpu.push_back(-999999);
    return offsetMpu;
}

void SavePIDs(int * pids, string ident) {
    ofstream myfile;
    string linea;
    string buffLines;
    string ruta = "/root/PIDs/" + ident + ".txt";
    myfile.open(ruta.c_str());
    
    if (myfile.is_open())
        cout << ruta << " abierta\r\n";
    else {
        cout << ruta << " no se pude abrir\r\n";
        mkdir("/root/PIDs", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        SavePIDs(pids,ident);
        return;
    }

    for (int i = 0; i < sizeof (pids); i++) {
        linea = ToString(pids[i]) + "\r\n";
        buffLines += linea;
    }
    myfile << buffLines;
    myfile.close();
}

vector<int> LoadPIDs(string ident)
{
    char buff[128] = "";
    ifstream myfile;
    vector<int> offsetMpu;
    int offset;
    
    myfile.open("/root/OffsetsMpu.txt");
    
    if (myfile.is_open()) {
        for (int i = 0; i < 6; i++) {
            try {
                myfile>>buff;
                stringstream(buff)>>offset;
                offsetMpu.push_back(offset);
                cout << buff << "\r\n";
            } catch (exception ex) {
                cout << "Error en linea: " << i << "\r\n";
                myfile.close();
                offsetMpu.clear();
                offsetMpu.push_back(-888888);
                return offsetMpu;
            }
        }
        myfile.close();
        return offsetMpu;
    } else
        cout << "Error al leer archivo OffsetsMpu.txt\r\n";
    offsetMpu.push_back(-999999);
    return offsetMpu;
}