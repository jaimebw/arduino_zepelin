#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

Adafruit_BNO055 bno = Adafruit_BNO055(55); 

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
}

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
  Serial.print("Sys:");
  Serial.print(system, DEC);
  Serial.println(" G:");
  Serial.print(gyro, DEC);
  Serial.println(" A:");
  Serial.print(accel, DEC);
  Serial.println(" M:");
  Serial.print(mag, DEC);
  
  return accel, mag, gyro;
}
void loop(){
    do {
        cal_accel, cal_mag, cal_gyro  = displayCalStatus();
        millis(10);
    }
    while((cal_gyro < 3) && (cal_accel< 3) && (cal_mag<3));
    Serial.println("FIN")
    exit(0);

}