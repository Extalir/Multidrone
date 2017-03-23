/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Funciones.h
 * Author: str-har-pc
 *
 * Created on 16 de enero de 2017, 12:26
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

vector<string> Split(const string &s, char delim) ;
string ToString(double val);
string ToString(int val);
bool is_number(const string& s);
float filterSmooth(float currentData, float previousData, float smoothFactor);
double StrToDecimal(string strVal, string direc);

#endif /* FUNCIONES_H */

