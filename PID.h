/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PID.h
 * Author: str-har-pc
 *
 * Created on 13 de enero de 2017, 13:12
 */

#ifndef PID_H
#define PID_H

#include <stdlib.h>
#include "Variables.h"

class PID {
private:
    float filter;
    int Hz;
public:
    float sampleTime;

    PID();
    PID(const PID& orig);
    bool ResetPID(struct Var_PID* PID);
    void LowResetPID(struct Var_PID* PID);
    bool InitPID(struct Var_PID* PID, float kp, float ki, float kd, float setpoint, float imax, float outmax);
    void CalculatePID(struct Var_PID* PID, float SetPoint, double MyInput);
    virtual ~PID();
private:

};

#endif /* PID_H */

