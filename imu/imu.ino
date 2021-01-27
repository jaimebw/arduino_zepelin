#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>


// PINES PARA LOS MOTORES
int IN1 = 2;    //Se definen pines de salida correspondientes al módulo de control
int IN2 = 3;   
int ENA = 5;    //Recomendable que ENA y ENB estén conectados a pines PWB para mayor eficiencia en los comandos
int IN3 = 7;
int IN4 = 8;
int ENB = 9; 

Adafruit_BNO055 bno = Adafruit_BNO055(55); // enciendo el IMU


int displayCalStatus(void){
  /* Get the four calibration values (0..3) */
  /* Any sensor data reporting 0 should be ignored, */
  /* 3 means 'fully calibrated" */
  uint8_t system, gyro, accel, mag;
  system = gyro = accel = mag = 0;
  bno.getCalibration(&system, &gyro, &accel, &mag);
  
  /* The data should be ignored until the system calibration is > 0 
  Serial.print("\t");*/
  if (!system)
  {
    Serial.print("! ");
  }
  
  // Display the individual values 
  Serial.println("^^^^^^^^^^^^^^^^");
  Serial.print("Sys:");
  Serial.print(system, DEC);
  Serial.print(" G:");
  Serial.print(gyro, DEC);
  Serial.print(" A:");
  Serial.print(accel, DEC);
  Serial.print(" M:");
  Serial.print(mag, DEC);
  Serial.println("");
  
  return accel, mag, gyro, system;
}

int cali =0;
int cal_gyro;
int cal_mag;
int cal_accel;
int cal_sys;
void setup(){
    Serial.begin(9600);
    Serial.println("Orientation Sensor Test"); Serial.println("");
  /* Initialise the sensor */
    if(!bno.begin())
    {
        Serial.print("No se detecta el sensor");
        while(1);
    }
  displayCalStatus();
  delay(1000);
  bno.setExtCrystalUse(true);  
  pinMode(IN1, OUTPUT);  //Se definen los mencionados pines como salidas
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

}
//#############################
// FUNCIONES PARA EL VOID LOOP
//#############################
float calStatus(){
  sensors_event_t event;
  
}
struct TRAMO {
  float coor_y;
  float coor_z;
  float giro;
  
};
// Declaracion de variables para acel, vel, pos y tiempo
float t0; float t; float diff_t;

float pos_x0; float pos_x;
float pos_y0; float pos_y;
float pos_z0; float pos_z;

float vel_x;  float vel_x0;
float vel_y;  float vel_y0;
float vel_z;  float vel_z0;

float acel_x; float acel_x0;
float acel_y; float acel_y0;
float acel_z; float acel_z0;

float mean_x; float mean_y; float mean_z;
float accul_x; float accul_y; float accul_z = 0;



float tol = 0.5; // tolerancia de un 1m/s^2
int contador = 0;

float filtro_accel(float antes,float ahora, float tol ){
  if (abs(antes-ahora)<tol){
    return 0;
  }
  else{
    return ahora;
  }
}
float filtro_simple(float previo, float acel){
  // Filtro sencillo para la acelaracion
  if (abs(acel - previo) < 0 )
  return acel-previo;
}
void printer(char nombre[],float x = 0,float y = 0,float z = 0){
  // Funcion para simplificar print por pantalla
    Serial.println("^^^^^^^^^^^^^^^^^^^^");
    Serial.println(nombre);
    Serial.println("^^^^^^^^^^^^^^^^^^^^");
    Serial.print("X: ");
    Serial.print(x, 2);
    Serial.print("\tY: ");
    Serial.print(y, 2);
    Serial.print("\tZ: ");
    Serial.print(z, 2);
    Serial.println("");
    Serial.println("####################");
  }


float angulo_x(){
  // Obtener el angulo en el eje X
  sensors_event_t event; 
    bno.getEvent(&event);
    return event.orientation.x;
}
  
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
    // Rotar a la dcha
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    
  }
  void rotarizq(void){
    // Rotar a la izquierda
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    
  }
float posicion_y( float acel_y0,float vel_y0,float pos_y0 ,float diff_t){
  // Devuelve la posicion del vehiculo
  imu::Vector<3> acel = bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
  float acel_y;
  float vel_y;
  float pos_y;
  if (abs(acel.y()-acel_y0) < tol){
    acel_y = 0;
    
  }
  else{
    acel_y = acel.y();
  }
  vel_y = vel_y0 + acel_y* diff_t;
  pos_y = pos_y0 + vel_y*(diff_t) + 0.5*acel_y*(pow(diff_t,2));
  return acel_y,vel_y,pos_y;
}

  


void loop(){
  
  imu::Vector<3> acel = bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
  if (contador == 0){
    // Empieza la calibración del sensor
   do{
      sensors_event_t event;
      bno.getEvent(&event);
      cal_accel, cal_mag, cal_gyro,cal_sys  = displayCalStatus();
   }
   while((cal_sys != 3));
  //while((cal_gyro= 3) && (cal_accel= 3)&& (cal_mag= 3));
    
    }
    
    if (contador == 0){
      acel_x0 = acel.x();
      acel_y0 = acel.y();
      acel_z0 = acel.z();
      
      vel_z0 = 0;
      vel_y0 = 0;
      
      pos_z0 = 0;
      pos_y0 = 0;
    
      Serial.println("Calibrado!");
      //t0 = millis()/1000;
      t0 = 0;
    }
    
    contador = contador +1;
    
    sensors_event_t event; 
    bno.getEvent(&event);
    //printer("Orientacion",event.orientation.x,event.orientation.y,event.orientation.z);
   
    pos_y0 = pos_y;
    pos_z0 = pos_z;
    vel_z0 = vel_z;
    vel_y0 = vel_y;
    t0 = t;

    TRAMO AB;
    AB.coor_y = 1;
    AB.coor_z = 0;
    AB.giro = 0;
    TRAMO BC;
    BC.coor_y = 2;
    BC.coor_z = 1;
    BC.giro = 45;
    TRAMO CD;
    CD.coor_y = 3;
    CD.coor_z = 0;
    CD.giro = -45;
    TRAMO DE;
    DE.coor_y = 4;
    DE.coor_z = 0;
    DE.giro = 0;
// Recorrido
//posicion_y( float acel_y0,float vel_y0,float pos_y0 ,float diff_t)
while(pos_y < AB.coor_y){
  vel_y,pos_y = posicion_y(acel_y0,vel_y0,pos_y0 ,diff_t);
  pos_y0 = pos_y;
  vel_y0 = vel_y;
  acel_y0 = acel_y;
  diff_t = t-t0;
  adelante();
  if (pos_y > AB.coor_y){
    vel_y,pos_y = posicion_y(acel_y0,vel_y0,pos_y0 ,diff_t);
    pos_y0 = pos_y;
    vel_y0 = vel_y;
    acel_y0 = acel_y;
    diff_t = t-t0;
    parar();
  }
}
while((pos_y > AB.coor_y)&(pos_y  <BC.coor_y )){
    vel_y,pos_y = posicion_y(acel_y0,vel_y0,pos_y0 ,diff_t);
    pos_y0 = pos_y;
    vel_y0 = vel_y;
    acel_y0 = acel_y;
    diff_t = t-t0;
  rotardcha();
  if (BC.giro- angulo_x() >0 ){
        parar();
        adelante();
      }
}
while((pos_y>BC.coor_y)&(pos_y<CD.coor_y)){
  vel_y,pos_y = posicion_y(acel_y0,vel_y0,pos_y0 ,diff_t);
    pos_y0 = pos_y;
    vel_y0 = vel_y;
    acel_y0 = acel_y;
    diff_t = t-t0;
  parar();
  delay(500);
  rotarizq();
  delay(1000);
  if (abs(CD.giro) -angulo_x() <0 ){
    parar();
    delay(500);
    adelante();
      }
}
while((pos_y> CD.coor_y)){
  vel_y,pos_y = posicion_y(acel_y0,vel_y0,pos_y0 ,diff_t);
   pos_y0 = pos_y;
   vel_y0 = vel_y;
   acel_y0 = acel_y;
   diff_t = t-t0;
  parar();
  delay(500);
  adelante();
  delay(1000);
  parar();
  delay(10000); // parada final
}
  

  }