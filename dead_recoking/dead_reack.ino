int IN1 = 2;    //Se definen pines de salida correspondientes al módulo de control
int IN2 = 3;   
int ENA = 5;    //Recomendable que ENA y ENB estén conectados a pines PWB para mayor eficiencia en los comandos
int IN3 = 7;
int IN4 = 8;
int ENB = 9;    
int t = 1000 * 1;


void setup(){
  Serial.begin(9600);
  pinMode(IN1, OUTPUT);  //Se definen los mencionados pines como salidas
  pinMode(IN2, OUTPUT);
  //pinMode(ENA, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  //pinMode(ENB, OUTPUT);
}
int i = 0;
void adelante(void){
    // Hacia adelante
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  }
  void parar(void){
    // Parar el vehículo
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);

    
  }
  void adetras(void){
    // Hacia detras
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  }
  void rotardcha(void){
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    
  }
  void rotarizq(void){
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    
  }

int sec(float t){
  return t*1000;
}
void loop(){
  
  //Avance 
  //digitalWrite(ENA, HIGH);
  
  adelante();
  delay(sec(2));
  parar();
  delay(sec(1));
  rotardcha();
  delay(sec(1.2));
  parar();
  delay(1000);
  adelante();
  delay(sec(1));
  rotarizq();
  delay(sec(1.2));
  parar();
  delay(1000);
  adelante();
  delay(sec(1));
  parar();
  delay(5000);
}
  /*
  i = i+1;
  Serial.print("Loco ");
  Serial.print(i);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  delay(1000);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(1000);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  delay(1000);
  */
  
  
  

/*
  delay(t);               //El tiempo de avance quedaría por determinar, pues la velocidad angular es función de la tensión
                            //Unidades de tiempo: milisegundos
  //Frenado
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
  delay(t);               //Tiempo a determinar según pruebas
  
  //Rotación antihoraria (giro a izquierdas)
  digitalWrite(ENA, HIGH);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(ENB, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(t);               //El tiempo de rotación antihoraria quedaría por determinar, pues la velocidad angular es función de la tensión
  
  //Frenado
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
  delay(t);               //Tiempo a determinar según pruebas
  
  //Avance
  digitalWrite(ENA, HIGH);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(ENB, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(t);               //El tiempo de avance quedaría por determinar, pues la velocidad angular es función de la tensión
  
  //Frenado
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
  delay(t);               //Tiempo a determinar según pruebas

  //Rotación horaria (giro a derechas)
  digitalWrite(ENA, HIGH);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(ENB, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(t);               //El tiempo de rotación horaria quedaría por determinar, pues la velocidad angular es función de la tensión
  
  //Frenado
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
  delay(t);               //Tiempo a determinar según pruebas

  //Avance 
  digitalWrite(ENA, HIGH);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(ENB, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(t);               //El tiempo de avance quedaría por determinar, pues la velocidad angular es función de la tensión
  
  //Frenado
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
  delay(t);               //Tiempo a determinar según pruebas

  //Rotación 180 grados
  ;digitalWrite(ENA, HIGH);  //Colocación del rover para el segundo tramo
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(ENB, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(t);               //El tiempo de rotación horaria quedaría por determinar, pues la velocidad angular es función de la tensión
  
  //Frenado
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
  delay(t);               //Tiempo a determinar según pruebas

  exit(0);     //Instrucción para salir del bucle al completar el primer tramo (no es seguro que funcione, probar)
*/
