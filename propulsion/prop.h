


int mover_motor(char motor, int time){
    /*
    Funcion para mover el motor. Solo hay HIGH o LOW.

    :param motor: elige motor izq o derecho
    :param time: tiempos en segundos de actuaction
    */
    int motor_dcha = 13;
    int motor_izq = 12;
    if (motor == "i"){
        digitalWrite(motor_izq,HIGH);
        delay(time*1000);
        digitalWrite(motor_izq,LOW);
    }
    else if (motor == "d")
    {
       digitalWrite(motor_dcha,HIGH);
       delay(time*1000);
       digitalWrite(motor_dcha,LOW);
    }
    else{
        digitalWrite(motor_izq,HIGH);
        digitalWrite(motor_dcha,HIGH);
        delay(time*1000);
        digitalWrite(motor_izq,LOW);
        digitalWrite(motor_dcha,LOW);
    }
}