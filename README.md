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
1. Arduino IDE - Puedes descargar el IDE <a href="https://www.arduino.cc/en/Main/Software" target="_blank">aquí <a/>
2. Libreria BMP085 Adafruit - Puedes descargarla <a href="https://learn.adafruit.com/bmp085/using-the-bmp085-api-v2" target="_blank">aquí <a/>
3. Libreria NeoPixel Adafruit - Puedes descargarla <a href="https://learn.adafruit.com/adafruit-neopixel-uberguide/arduino-library-installation" target="_blank">aquí <a/>
4. Libreria PubSubClient - Puedes encontrarla en el manejador de librerias de Arduino
  <p align="center">
    <img  src="/imagenes/pubsubclient.png">
  </p>
5. Entender como funciona MQTT, puedes entender más ingresando <a href="https://randomnerdtutorials.com/what-is-mqtt-and-how-it-works/" target="_blank">aquí <a/>

<br />

## Instalación ESP32 en Arduino IDE
Para poder instalar nuestra tarjeta ESP32 en Arduino IDE, necesitamos seguir los siguientes pasos:

1. Teniendo abierto nuestro Arduino IDE, vamos a __*File > Preferences*__
<p align="center">
  <img  src="/imagenes/arduino-ide-open-preferences.png">
</p>

2. Debemos de ingresar lo siguiente: __*https://dl.espressif.com/dl/package_esp32_index.json*__ dentro del cuadro que dice *Additional Board Manager URLs* como se muestra en la siguiente figura, luego dar click en el botón de *OK*
<p align="center">
  <img  src="/imagenes/preferences.png">
</p>

__Nota:__ Si ya tienes algún link en este campo, puedes agregar el que te indicamos separandolo por una coma, como se muestra a continuación.

```
https://dl.espressif.com/dl/package_esp32_index.json, http://arduino.esp8266.com/stable/package_esp8266com_index.json
```

3. Abrimos nuestro Board Manager. Vamos a __*Tools > Board > Boards Manager*__ 
<p align="center">
  <img src="/imagenes/boardsManager.png">
</p>

4. En la ventana emergente buscamos __*ESP32*__ y damos click en el botón instalar para la tarjeta __*ESP32 by Espressif Systems*__ 
<p align="center">
  <img  src="/imagenes/installing.png">
</p>

5. Eso es todo lo necesario para instalar nuestra tarjeta __*ESP32*__ debe de estar lista luego de unos segundos.
<p align="center">
  <img  src="/imagenes/ESP32-Board-add-on-in-Arduino-IDE-installed.png">
</p>

6. Verificamos que nuestra tarjeta este instalada y lista para usar.
<p align="center">
  <img src="/imagenes/installation-verification.png">
</p>


<br />

## Pines a utilizar
A continuación se explica los pines y código utilizado para poder enviar datos desde nuestro dispositivo a nuestro dashboard creado con Node-Red (puedes encontrar más información de Node-RED ingresando al <a href="https://nodered.org/" target="_blank"> Sitio oficial Node-RED<a />.
<p align="center">
  <img src="/imagenes/esp32-pinout.jpg">
</p>

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
IN | 25
VCC | 5V
GND | GND

## Código ESP32

2. Lo que debemos de cambiar en nuestro código es lo siguiente:

```
// Constandes de conexión - Modificar al nombre que se te indique.
  #define TEAM_NAME "node1"
//////////////////////////////////////////////////////////////////
```
En donde sustituimos lo que esta como __*node1*__ por lo que se te indique en la charla.

3. Verificamos que la dirección de nuestro servidor (para esta demostración) sea __galiot.galileo.edu__
```
const char* mqtt_server = "galiot.galileo.edu";
```

4. Ingresamos los datos de nuestra conexión a Wi-Fi
```
/*//////////////////////////////////////
 * Modificar con los datos de tu WiFi 
 */
const char* ssid = "Nombre de tu internet";
const char* password = "Clave de tu internet";
////////////////////////////////////////
```
aquí debemos de colocar el nombre de nuestro internet y el password.

5. Verificamos __PIN. Número de Pixels y brillo__ de nuestro RING LED o LED STRIP
```

// ¿En cuál pin conectamos nuestro RING NeoPixels?
#define PIN        25 

// ¿Cuántos NeoPixels estan conectados?
#define NUMPIXELS 16 // NeoPixel RING tamaño regular
int brightness = 150; // Brillo de 0 a 255
```
6. Seleccionamos nuestra tarjeta __ESP32__ y el __PUERTO__ correcto
<p align="center">
  <img src="/imagenes/installation-verification.png">
</p>

Luego de verificar podemos darle a __*SUBIR / UPLOAD*__ a nuestro código.

7. Abrimos nuestro monitor serial y nos aseguramos de tener el baudaje en __115200__


