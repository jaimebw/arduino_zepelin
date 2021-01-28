int IN1 = 2;    //Se definen pines de salida correspondientes al módulo de control
int IN2 = 3;   
int ENA = 5;    //Recomendable que ENA y ENB estén conectados a pines PWB para mayor eficiencia en los comandos
int IN3 = 7;
int IN4 = 8;
int ENB = 9;    
int pin_led = 12;
int t = 1000 * 1;


void setup(){
  Serial.begin(9600);
  pinMode(IN1, OUTPUT);  //Se definen los mencionados pines como salidas
  pinMode(IN2, OUTPUT);
  //pinMode(ENA, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(pin_led,OUTPUT);
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
  digitalWrite(pin_led, HIGH);   
  delay(500);                      
  digitalWrite(pin_led, LOW);    
  delay(500); 

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