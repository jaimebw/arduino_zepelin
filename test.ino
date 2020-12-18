#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>




Adafruit_BNO055 bno = Adafruit_BNO055(55); // enciendo el IMU

void setup(){

    Serial.begin(9600);
    Serial.println("Orientation Sensor Test"); Serial.println("");
  /* Initialise the sensor */
    if(!bno.begin())
    {
        /* There was a problem detecting the BNO055 ... check your connections */
        Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
        while(1);
    }
    
  delay(1000);
    
  bno.setExtCrystalUse(true);
    
}


float vel_y;
int i = 0; 
float diff_t;
float t0 ;
float pos0_y;
float pos0_z;
float pos_y;
float pos_z;
float t;
float acel_z;
float acel_y ;
float giro_x ;
float vel0_z;
float vel0_y;
float vel_z;
float acel_cal_y;

void loop(){
  imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER); // vector de angulos de euler
  imu::Vector<3> acel = bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
// iterador 

  t = millis()/1000; // valor del tiempo
  if (i == 0){
    // primera iteracion
    t0 = 0;
    float acel_cal_y = acel.y();
    float acel_cal_z = acel.z();
    pos0_y = 0;
    pos0_z = 0;
    vel0_z = 0;
    vel0_y = 0;
    
  }
  if (acel.y() 
  diff_t = t - t0;
  /*
  Hay que añadir el filtro para las acelaraciones
  */
  vel_z = acel.z()* diff_t + vel0_z;
  vel_y = (acel.y()-acel_cal_y)* diff_t + vel0_y; 
  pos_z = vel_z * diff_t + pos0_z;
  pos_y = vel_y * diff_t + pos0_y;

  
  Serial.print("Acel_y: "); Serial.println(acel.y());
  Serial.print("Pos0_y: ");Serial.println(pos0_y);
  Serial.print("Pos_y: ");Serial.println(pos_y);
  Serial.println("-------------------------");
  pos0_y = pos_y;
  pos0_z = pos_z;
  vel0_y = vel_y;
  vel0_z = vel0_z;
  t0 = t;

 
 
  i = i +1;
  delay(1000);
}