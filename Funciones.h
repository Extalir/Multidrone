/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Funciones.h
 * Author: str-har-pc
 *
 * Created on 16 de enero de 2017, 12:32
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

#define PI 3.14159265359

vector<string> Split(const string &s, char delim);

string ToString(double val);
string ToString(int val);

bool is_number(const string& s);

float filterSmooth(float currentData, float previousData, float smoothFactor);
//double StrToDecimal(string strVal, string direc);
double StrToDecimal(double valor, string direc);

double Radianes(double valor);
double Grados(double valor);

vector<int> LoadOffsetMpu();
void SaveOffsetMpu(int * offsets);

void SavePIDs(int * pids, string ident);
vector<int> LoadPIDs(string ident);

#endif /* FUNCIONES_H */

