


int mover_motor(str motor, int time){
    /*
    Funcion para mover el motor.
    
    :param motor: elige motor izq o derecho
    :param time: tiempos en segundos de actuaction
    */
    int motor_dcha = 13;
    int motor_izq = 12;
    if (motor == "izq"){
        digitalWrite(motor_izq,HIGH);
        delay(time*1000);
        digitalWrite(motor_izq,LOW);
    }
    else if (motor == "dcha")
    {
       digitalWrite(motor_dcha,HIGH);
       delay(time*1000);
       digitalWrite(motor_dcha,LOW);
    }
    
}