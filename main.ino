/*
autor: Jaime Bowen 

Script principal para el diribile

*/
#include <propulsion/prop.h>
#include <guiado/guide.h>


int motor_dcha = 13;
int motor_izq = 12;

void setup(){
    pinMode(motor_izq, OUTPUT);
    pinMode(motor_dcha,OUTPUT);
    Serial.begin(57600);
    
}
 
void loop(){
    int i = 0;
    while (i <4){
        if(i ==0) {
            getPosition();
            lookforObstacles();
            mover_motor(motor = "t",time = 8) // se mueve durante 8s, y luego se para
            getPosition();
        }
        i = i+1;
        if (i==1){
            getPosition();
            lookforObstacles();
            mover_motor(motor = "d",time = 5); // gira a la izquierda
            mover_motor(motor = "t", time = 5); // se va recto
            getPosition();

        }
        i = i +1;
        if (i ==2){
            getPosition();
            lookforObstacles();
            mover_motor(motor = "i", time = 8);
            mover_motor(motor = "t",time = 5);
            getPosition();

        }
        i = i +1;
        if (i == 3){
            getPosition();
            lookforObstacles();
            mover_motor(motor = "d", time = 4);
            mover_motor(motor = "t",time = 5);
            getPosition();

        }
        i = i +1;


    }
    makeEndSound();

}

}
/*
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
*/