# Repo con el código arudino para el dirigible del trabajao de 1º de MUIA de la UEM
(en desarrollo)
## Proceso de desarrollo 
Para desarrollar este trabajo es necesario dividir todo en varios bloques:
1. Estructura y flotabildiad
2. Guiado
3. Propulsión

En este repositorio se desarrollarán los dos últimos apartados.
## Tarjeta que se utilizará para el proceso
Para el desarrollo de este trabajo se va a usar el microcontrolador UNO R3 de ELEGOO

## Guiado  

Para realizar el guiado del dirigible se usarán dos sensores:
* IMU : este proporcionará el guiado inercial
* Sensor de ultrasonidos: este proporcionará guiado en caso de que haya elementos obstruyendo el paso del dirigible


### Librerias e info sobre los sensores

* [IMU](https://github.com/adafruit/Adafruit_BNO055)
* [Info de cómo usar el IMU](https://learn.adafruit.com/adafruit-bno055-absolute-orientation-sensor/arduino-code)

## Propulsión  

Para conseguir que el dirigible se traslade es necesario incorporar una planta motor. En este caso se basará en unos motores de corriente continua posicionados a los lados del dirigle para poder crear momentos y poder propulsar de manera sencilla.

### Control de los motores
Para realizarlo se necesitan 4 motores DC con un controlador que funcine con un transistor
*[Control Motor](https://www.tutorialspoint.com/arduino/arduino_dc_motor.htm)

