/****************
 * Código creado para ConéctateGT - 2020
 * Publicación de datos de temperatura a dashboard Node-Red con MQTT
 */

#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <Adafruit_BMP085.h>
#include <Adafruit_NeoPixel.h>

// Constandes de conexión - Modificar al nombre que se te indique.
#define TEAM_NAME "nodeyc"
//////////////////////////////////////////////////////////////////

/*////////////////////////////////////////
 * No modificar
 */
#define PUBLISH_PERIOD 60000
Adafruit_BMP085 bmp;
const char* mqtt_server = "galiot.galileo.edu";

#ifdef __AVR__
 #include <avr/power.h> // Requerido para 16 MHz Adafruit Trinket
#endif
//////////////////////////////////////////


/*//////////////////////////////////////
 * Modificar con los datos de tu WiFi 
 */
const char* ssid = "electronica-n";
const char* password = "elec2012";
////////////////////////////////////////



// ¿En cuál pin conectamos nuestro RING NeoPixels?
#define PIN        25 

// ¿Cuántos NeoPixels estan conectados?
#define NUMPIXELS 16 // NeoPixel RING tamaño regular
int brightness = 150; // Brillo de 0 a 255

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 500 // Tiempo (en milisegundos) para encender cada pixels

//Variables
int red=0;
int blue = 0;
int green = 0;

// data variables
int lastReadingTime = 0;
double temp = 0;

char msg[50];
char msg1[50];
char cnt[50];
char msg_r[50];
char topic_name[250];

// network variables
WiFiClient espClient;
PubSubClient mqtt_client(espClient);

void setupMQTT() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  mqtt_client.setServer(mqtt_server, 1883);
  mqtt_client.setCallback(callback);
}


void setup() {

    #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
      clock_prescale_set(clock_div_1);
    #endif
    pixels.begin(); // Inicializamos el objeto Pixels (REQUERIDO)
    pixels.setBrightness(brightness);
    pixels.clear(); // Colocamos todos los pixels en 'off'

    Serial.begin(115200);
    setupMQTT();
    if (!bmp.begin()) {
      Serial.println("Could not find a valid BMP085 sensor, check wiring!");
      while (1) {}
    }

}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    msg_r[i] = (char)payload[i];
  }
  msg_r[length] = 0;
  Serial.print("'");
  Serial.print(msg_r);
  Serial.println("'");
  if (strcmp("ON", msg_r) == 0) {
    Serial.println("SE MANDO ON");
  } else if(strcmp("OFF", msg_r) == 0) {
    Serial.println("SE MANDO OFF");
  }else{
    colorConverter(msg_r);
  }
}

void colorConverter(String hexValue)
{
    int number = (int) strtol( &hexValue[1], NULL, 16);
    int r = number >> 16;
    int g = number >> 8 & 0xFF;
    int b = number & 0xFF;

    Serial.print("red is ");
    Serial.println(r);
    Serial.print("green is ");
    Serial.println(g);
    Serial.print("blue is ");
    Serial.println(b);

     pixels.clear(); // Colocamos todos los pixels en 'off'

    for(int i=0; i<NUMPIXELS; i++) { // Para cada pixel...
  
      // pixels.Color() toma valores RGB, de 0,0,0 hasta 255,255,255
      // Para este ejemplo solo estamos usando el color verde.
      pixels.setPixelColor(i, pixels.Color((r+50), g, b));
    }
      pixels.show();   // Mandamos el update del color al hardware.
  
      delay(DELAYVAL); // Esperamos un tiempo para regresar al loop.

}

void reconnect() {
  // Loop until we're reconnected
  while (!mqtt_client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (mqtt_client.connect("node1/btn" )) {
      Serial.println("connected");
      mqtt_client.subscribe(getTopic("rgb"));
    }else {
      Serial.print("failed, rc=");
      Serial.print(mqtt_client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void publish(char* topic, char* payload) {
  Serial.println(topic_name);
  mqtt_client.publish(topic_name, payload);
}

char* getTopic(char* topic) {
  sprintf(topic_name, "/%s/%s", TEAM_NAME, topic);
  return topic_name;
}

void loop() {
  if (!mqtt_client.connected()) {
    reconnect();
  }
  mqtt_client.loop();

  int actualTime = millis();
  if (actualTime - lastReadingTime > PUBLISH_PERIOD) {
    lastReadingTime = actualTime;

    Serial.print("Temperature = ");
    Serial.print(bmp.readTemperature());
    Serial.println(" *C");
    
    
    Serial.println();
    delay(50);
    temp = bmp.readTemperature();
    String str(temp);
    str.toCharArray(msg, 50);
    mqtt_client.publish(getTopic("temp"), msg);     


//    String str2(bmp.readSealevelPressure());
//    str2.toCharArray(msg1, 50);
//    mqtt_client.publish(getTopic("press"), msg1);
  }
}
