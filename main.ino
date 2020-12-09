/*
autor: Jaime Bowen 

Script principal para el diribile

*/
#include <propulsion/prop.h>
#include <guiado/guide.h>
#include <NewPing.h>
#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"

int motor_dcha = 13;
int motor_izq = 12;

void setup(){
    pinMode(motor_izq, OUTPUT);
    pinMode(motor_dcha,OUTPUT);
    Serial.begin(57600);
    
}
 
void loop(){
    



}

bool mover_motor(str motor){
    // Funcion sin regulación de potencia
    int motor_dcha = 13;
    int motor_izq = 12;
    if (motor == "izq"){
        digitalWrite(motor_izq,HIGH);
    }
    else if (motor == "dcha")
    {
       digitalWrite(motor_dcha,HIGH);
    }
    
}