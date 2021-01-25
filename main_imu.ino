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
float x0;
float y0;
float z0;
float x;
float y;
float z;

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






float tol = 2; // tolerancia de un 1m/s^2
int contador = 0;
float filtro_accel(float antes,float ahora, float tol ){
  if (abs(antes-ahora)<tol){
    return 0;
  }
  else{
    return ahora;
  }
  
}
void printer(float y,float z){
    Serial.println("^^^^^^^^^^^^^^^^^^^^");
    Serial.println("####################");
    Serial.print("Y: ");
    Serial.print(y, 2);
    Serial.print("\tZ: ");
    Serial.print(z, 2);
    Serial.println("");
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
    acel_x0 = acel.x();
    acel_y0 = acel.y();
    acel_z0 = acel.z();
    
    }
    if (contador == 0){
      Serial.println("Calibrado!");
      t0 = millis()/1000;
    }
    
    contador = contador +1;
    
    sensors_event_t event; 
    bno.getEvent(&event);
    
    Serial.println("Detalles");
    Serial.println("ºººººººººººººººººººº");
    Serial.print("Xº: ");
    Serial.print(event.orientation.x, 4);
    Serial.print("\tYº: ");
    Serial.print(event.orientation.y, 4);
    Serial.print("\tZº: ");
    Serial.print(event.orientation.z, 4);
    Serial.println("");
    /*
    if (abs(acel.x()-acel_x0)>tol){
        Serial.print("X: ");
        Serial.print(acel.x(), 4);
        acel_x = acel.x();
    }
    else{
      Serial.print("X: ");
      Serial.print(0);
      acel_x = 0;
    }
    if (abs(acel.y()-acel_y0)>tol){
    
      Serial.print("\tY: ");
      Serial.print(acel.y(), 4);
      acel_y = acel.y();
    }
     else{
      Serial.print("\tY: ");
      Serial.print(0);
      acel_y = 0;
     }
     if (abs(acel.z()-acel_z0)>tol){
    
      Serial.print("\tZ: ");
      Serial.println(acel.z(), 4);
      acel_z = acel.z();
      }
     else{
      Serial.print("\tZ: ");
      Serial.println(0);
      acel_z = 0;
     }
     
     */
     acel_z = filtro_accel(acel_z0,acel.z(),tol);
     acel_y = filtro_accel(acel_y0,acel.y(),tol);
     acel_x = filtro_accel(acel_x0,acel.x(),tol);
     Serial.println("----------------");
     Serial.println("----------------");
    // Código para obtener posicion
    t = millis()/1000;
    diff_t = t-t0;
    vel_z = acel_z * diff_t + vel_z0;
    vel_z0 = vel_z;
    vel_y = acel_y* diff_t + vel_y0;
    vel_y0 = vel_y;
    pos_z = vel_z * pow(diff_t,2) + pos_z0;
    pos_y = vel_y * pow(diff_t,2) + pos_y0;
    pos_z0 = pos_z;
    pos_y0 = pos_y;
    t = t0;
    Serial.println("Velocidad");
    printer(vel_y,vel_z);
    Serial.println("Posicion");
    printer(pos_z,pos_y);
    
    
    delay(500);
    
  
  
  }





/*
int main(){
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
  return cal_accel;
}
  */
