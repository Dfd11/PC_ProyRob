#include <SoftwareSerial.h>
#include "WiFiEsp.h"
SoftwareSerial ESPserial1(3, 2); // RX | TX
SoftwareSerial ESPserial2(4, 5); // RX | TX
SoftwareSerial ESPserial3(6, 7); // RX | TX

const char* ssid = "S20";
const char* pass = "internet!";
int status = WL_IDLE_STATUS;    

unsigned long lastConnectionTime = 0;         // last time you connected to the server, in milliseconds
const unsigned long postingInterval = 10000L; // delay between updates, in milliseconds
// Initialize the Ethernet client object
WiFiEspClient client;

void setup()
{ Serial.begin(9600);
  ESPserial1.begin(9600);
  //ESPserial2.begin(9600);
  //ESPserial3.begin(9600);
  Serial.println("");
  Serial.println("Remember to to set Both NL & CR in the serial monitor.");
  /*
  WiFi.init(&ESPserial1);
  //WiFi.init(&ESPserial2);
  //WiFi.init(&ESPserial3);

  // check for the presence of the shield
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue
    Serial.println("resetting");
    
  }

  // attempt to connect to WiFi network
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network
    status = WiFi.begin(ssid, pass);
  }

  Serial.println("You're connected to the network");
  
  printWifiStatus();*/
}

void loop()
{
  // listen for communication from the ESP8266 and then write it to the serial monitor

  if ( ESPserial3.available() ) { Serial.write( ESPserial3.read() ); }
  
  // listen for user input and send it to the ESP8266
  
  if ( Serial.available() ) { ESPserial3.write( Serial.read() ); }
  
  /*// print the received signal strength
  long rssi = WiFi.RSSI();
  Serial.print("Signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");*/
}

void printWifiStatus()
{
  // print the SSID of the network you're attached to
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength
  long rssi = WiFi.RSSI();
  Serial.print("Signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
