# Repo con el código arudino para el dirigible del trabajao de 1º de MUIA de la UEM
(en desarrollo)
[Drive](https://drive.google.com/drive/folders/1aVQqiT-GZWuNmXhBgVc2obI3MjK_QTwS?usp=sharing)
## Proceso de desarrollo 
Para desarrollar este trabajo es necesario dividir todo en varios bloques:
1. Estructura 
2. Tracción
3. Guiado

En este repositorio se desarrollarán los dos últimos apartados.
## Tarjeta que se utilizará para el proceso
Para el desarrollo de este trabajo se va a usar el microcontrolador UNO R3 de ELEGOO.
## Librerias e info sobre los sensores

* [IMU](https://github.com/adafruit/Adafruit_BNO055)
* [Info de cómo usar el IMU](https://learn.adafruit.com/adafruit-bno055-absolute-orientation-sensor/arduino-code)
## 2. Tracción

Para conseguir que elrover se traslade es necesario incorporar una planta motor. En este caso se basará en unos 4 motores de corriente continua posicionados en el rover.

### 2.1 Control de los motores
Para realizarlo se necesitan 4 motores DC con un controlador que funcine con un transistor  

*[Control Motor](https://www.tutorialspoint.com/arduino/arduino_dc_motor.htm)

## 3. Guiado  

Para realizar el guiado del dirigible se usarán dos sensores:
* IMU : este proporcionará el guiado inercial
