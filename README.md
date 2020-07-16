# ConéctateGT - ESP32 | Arduino Code
<p align="center">
  <img width="250" src="/imagenes/logo.png">
</p>
<br />

## Pre-requisitos - Hardware
1. Esp32
2. Sensor BMP180
3. RING LED

## Pre-requisitos - Software
1. Arduino IDE
2. Libreria BME085 Adafruit - Puedes descargarla <a href="https://learn.adafruit.com/bmp085/using-the-bmp085-api-v2" target="_blank">aquí <a/>
3. Libreria NeoPixel Adafruit - Puedes descargarla <a href="https://learn.adafruit.com/adafruit-neopixel-uberguide/arduino-library-installation" target="_blank">aquí <a/>
4. Entender como funciona MQTT, puedes entender más ingresando <a href="https://randomnerdtutorials.com/what-is-mqtt-and-how-it-works/" target="_blank">aquí <a/>

<br />

A continuación se explica los pines y código utilizado para poder enviar datos desde nuestro dispositivo a nuestro dashboard creado con Node-Red (puedes encontrar más información de Node-RED ingresando al <a href="https://nodered.org/" target="_blank"> Sitio oficial Node-RED<a />.

<br />

## Pines a utilizar

### Conectando sensor BMP180 con esp32
BMP180 | ESP32
--- | ---
SCL | 22
SDA | 21
VCC | 3V3
GND | GND


### Conectando RING LED con esp32
RING LED | ESP32
--- | ---
IN | 34
VCC | 5V
GND | GND

## Código Arduino
