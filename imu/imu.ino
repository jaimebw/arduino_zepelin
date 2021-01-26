#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>


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
  /*
do{
   sensors_event_t event;
   bno.getEvent(&event);
   cal_accel, cal_mag, cal_gyro  = displayCalStatus();
  //Serial.print("g = ");Serial.println(cal_gyro);
 // Serial.print("a = ");Serial.println(cal_accel);
 // Serial.print("mag = ");Serial.println(cal_mag);
 // Serial.println("_____________");
  delay(100);
  }while((cal_gyro!= 3) && (cal_accel!= 3)&& (cal_mag!= 3));
  
  Serial.print("Pene");
*/


  
}

float calStatus(){
  sensors_event_t event;
  
}


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
  if (abs(acel - previo) < 0 )
  return acel-previo;
}
void printer(char nombre[],float x = 0,float y = 0,float z = 0){
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





void loop(){
  // Código de calibración y para ver que pasa exactamente en el vehículo
  imu::Vector<3> acel = bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
  if (contador == 0){
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
   
   
   acel_z = filtro_accel(mean_z,acel.z(),tol);
   accul_z = accul_z + acel.z();
   mean_z = accul_z/(contador);
   //printer("Loco",acel_z,accul_z,mean_z);
   
   //acel_z0 = acel_z;
   // 9.36
   acel_y = filtro_accel(mean_y,acel.y(),tol);
   accul_y = accul_y + acel.y();
   mean_y = accul_y/(contador);
   //acel_y0 = acel_y;
   // 0.45
   acel_x = filtro_accel(mean_x ,acel.x(),tol);
   accul_x = accul_x + acel.x();
   mean_x = accul_x/(contador);
   //acel_x0 = acel_x;
   // 0.33 
    // Código para obtener posicion
 
    
    
    vel_z = acel_z * diff_t + vel_z0;
    vel_y = acel_y* diff_t + vel_y0;
    
    
    pos_z = acel_z* pow(diff_t,2)*0.5+ vel_z0 * diff_t+ pos_z0;
    pos_y = acel_y * pow(diff_t,2)*0.5+vel_y0*diff_t + pos_y0;

    
    pos_y0 = pos_y;
    pos_z0 = pos_z;
    vel_z0 = vel_z;
    vel_y0 = vel_y;
    t0 = t;
  
    printer("Aceleracion",acel_x,acel_y,acel_z);
    printer("Aceleracion",acel.x(),acel.y(),acel.z());
    printer("Velocidad",0,vel_y,vel_z);
    printer("Posicion",0,pos_z,pos_y);
    Serial.println(contador);
    
    
    delay(2000);
    
  
  
  }