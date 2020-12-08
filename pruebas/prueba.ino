// Autor: Alberto Gonzalez Viaña
//
#include <NewPing.h>
#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"

#define TRIGGER_PIN  5 // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     6  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
MPU6050 sensor;

// Variables para el girosocopo 
int i=0;
int gx, gy, gz;
int t=0;
long tiempo_prev, dt;
float girosc_ang_z;
float girosc_ang_z_prev;

// Variables para los pines
const int ledpinL = 10;
const int ledpinR = 9;


void setup() {
  
  Serial.begin(57600);    //Iniciando puerto serial
  Wire.begin();           //Iniciando I2C  
  sensor.initialize();    //Iniciando el sensor
  pinMode(ledpinL,OUTPUT);
  pinMode(ledpinR,OUTPUT);
  if (sensor.testConnection()) Serial.println("Sensor iniciado correctamente");
  else Serial.println("Error al iniciar el sensor");
  tiempo_prev=millis();
  
  //IMPLEMENTAR LA CALIBRACION Y EL GX,GY,GZ UNA VEZ PARA VER SI ESTA AL REDEDOR DEL 0.0
}

void loop() {
  int dist_sonar = sonar.ping_cm();
  if (i==0){
    while (dist_sonar >= 50 || dist_sonar == 0) {  
    // Estoy especificando que cuando sea mayor que 50 cm la distancia. Especificar posteriormente la que queremos. El || (o) es por si esta muy lejos 
    // sensor.getRotation(&gx, &gy, &gz)
    // lee la velocidad angular, no hace Falta
    digitalWrite (ledpinR,HIGH);
    digitalWrite (ledpinL,HIGH);
    Serial.print(dist_sonar);
    Serial.print('\n');
    Serial.print(angulos());
    Serial.print('\n');
    }

  while (dist_sonar <50)
  {
    //TURN OFF THE ENGINES
    Serial.print("apagado de motores");
    digitalWrite(ledpinL,LOW);
    digitalWrite(ledpinR,LOW);
    Serial.print(angulos());
    Serial.print('\n');
    Serial.print(sonar.ping_cm());
    Serial.print('\n');
    delay(50);
  
    
    temporizador (); // Temporizador para para el sistema
    
    //Accion de girar el Zeppellin hasta los 90 grados.
        
    if (angulos()>=-88){
      
      while (angulos()>= -88) { 
      //TURN ON THE ENGINE TO TURN. Hacerlo muy lento para evitar inercias.
      digitalWrite(ledpinL,HIGH); 
      Serial.print(angulos());
      Serial.print('\n');
      Serial.print("girando");
      Serial.print('\n');
      delay(50);
      //CALCULOS PARA DETERMINAR EN CAD AINSTANTE LO QUE VA GIRANDO}
      }

    else if (angulos()<-88){

      // TURN OF THE ENGINES
      digitalWrite(ledpinL,LOW);
      Serial.print(angulos());
      Serial.print('\n');
    }
  
  //Llama a la funcion de temporizador para reposar el sistema 
    temporizador ();
  
    
  Serial.print("finalizado el trayecto");
  Serial.print('\n');
  delay(2000);
    }
  }

  else if (i==1){

    while (sonar.ping_cm()>=100 || sonar.ping() == 0) {
    //TURN ON THE ENGINES
      Serial.print("Encendido de motores");
      Serial.print('\n');
      digitalWrite (ledpinR,HIGH);
      digitalWrite (ledpinL,HIGH);
      Serial.print(sonar.ping_cm());
      Serial.print('\n');
      Serial.print(angulos());
      Serial.print('\n');
      delay(50);   
    }

    while (sonar.ping_cm()<100){

    //TURN OFF THE ENGINES
        Serial.print("apagado de motores");
        Serial.print('\n');
        digitalWrite(ledpinL,LOW);
        digitalWrite(ledpinR,LOW);
        Serial.print(angulos());
        Serial.print('\n');
        Serial.print(sonar.ping_cm());
        Serial.print('\n');
        delay(50);

    //Llama a la funcion de temporizador para reposar el sistema 
      temporizador ();

    //Accion de girar el Zeppellin hasta los 90 grados.
        
      if (angulos()<=-2){
      
          while (angulos()<=-2) { 
      //TURN ON THE ENGINE TO TURN. Hacerlo muy lento para evitar inercias.
      Serial.print(angulos());
      Serial.print('\n');
      Serial.print("girando derechas");
      Serial.print('\n');
      digitalWrite(ledpinR,HIGH); 
      Serial.print(angulos());
      Serial.print('\n');
      delay(50);
    
      //CALCULOS PARA DETERMINAR EN CAD AINSTANTE LO QUE VA GIRANDO

    
          }
        }
        else if (angulos()>-2){

          // TURN OF THE ENGINES
          digitalWrite(ledpinR,LOW);
          Serial.print(angulos());
        }

    //Llama a la funcion de temporizador para reposar el sistema 
      temporizador ();
      
      }

      Serial.print("Finalizado tramo 2");
      delay(4000);
      }

  else if (i==2){

    while (sonar.ping_cm()>=50 || sonar.ping() == 0) {
  //TURN ON THE ENGINES
      Serial.print("Encendido de motores");
      Serial.print('\n');
      digitalWrite (ledpinR,HIGH);
      digitalWrite (ledpinL,HIGH);
      Serial.print(sonar.ping_cm());
      Serial.print('\n');
      Serial.print(angulos());
      Serial.print('\n');
    }

    while (sonar.ping_cm()<50){

  //TURN OFF THE ENGINES
      Serial.print("apagado de motores");
      digitalWrite(ledpinL,LOW);
      digitalWrite(ledpinR,LOW);
      Serial.print(angulos());
      Serial.print(sonar.ping_cm());
    
  //Llama a la funcion de temporizador para reposar el sistema 
    temporizador ();

  //Si le quisieramos meter otro giro mas serian volviendo a hacer lo mismo
  /*   
  //Accion de girar el Zeppellin hasta los 90 grados.
      
        if (angulos()>=88){
    
          while (angulos()>= -88) { 
    //TURN ON THE ENGINE TO TURN. Hacerlo muy lento para evitar inercias.
            Serial.print(angulos());
            Serial.print("girando derechas");
            digitalWrite(ledpinR,HIGH); 
            delay(50);
    //CALCULOS PARA DETERMINAR EN CAD AINSTANTE LO QUE VA GIRANDO

  
            }
          }
      else if(){
  // TURN OF THE ENGINES
        digitalWrite(ledpinR,LOW);
        Serial.print(angulos());      
        }
  */
      }
    Serial.print("Finalizado el tramo 3");
    // Espera un caracter para empezar seguir
    while (true){if (Serial.available()) break;} 
    }  
  i = i+1;
  Serial.print(i);
  delay (2000);
  }


  float angulos(){
  // Obtiene las angulos del girosocopo y devuelve 
    sensor.getRotation(&gx, &gy, &gz); //leer otra vez la velocidad angular
    dt = millis()-tiempo_prev;
    tiempo_prev= millis();
    girosc_ang_z = (gz/131)*dt/1000.0 + girosc_ang_z_prev;
    girosc_ang_z_prev=girosc_ang_z; //SACA EL ANGULO que deberia de dar alrededor de 0
    return girosc_ang_z; 
  }

  float temporizador(int t2 = 5000){
  // Generar un termporizador
    float tiempo_prev2 = millis();

    for (t=0; t<=t2;){
    t = millis()-tiempo_prev2;
    Serial.print(t);
    Serial.print('\n');

  }
}
  
 
