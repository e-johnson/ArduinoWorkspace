// this code connects the board to the wifi signal and turns an LED light 
// on and off through a wifi server

#include <ESP8266WiFi.h>

const char* ssid = "icehouse";
const char* password = "aggiepride";

int ledPin = 13; 
WiFiServer server(80); 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); 
  delay(10); 
  
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); 

  //Connect to Wifi network
  Serial.println();
  Serial.println(); 
  Serial.print("Connecting to"); 
  Serial.println(ssid); 

  WiFi.begin(ssid, password);
  while( WiFi.status() != WL_CONNECTED) { 
    delay(500); 
    Serial.print("."); 
  }
  Serial.println(""); 
  Serial.println("Wifi connected");

  //Start the Server
  server.begin(); 
  Serial.println("Server started"); 

  Serial.print("User this URL to connect: "); 
  Serial.print("http://"); 
  Serial.print(WiFi.localIP()); 
  Serial.println("/"); 

}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available(); 
  if (!client) {
    return; 
  }
  // Wait until the client sends some data 
  Serial.println("new client"); 
  while(!client.available()){
    delay(1); 
  }
  // Read the first line of the request
  String request = client.readStringUntil('\r'); 

  //Match the request

  int value = LOW; 
  if (request.indexOf("/LED=ON") != -1) {
    digitalWrite(ledPin, HIGH);
    value = HIGH; 
  }
  if (request.indexOf("/LED=OFF") != -1) {
    digitalWrite(ledPin, LOW); 
    value = LOW; 
  }

  // Set ledPin according to the request 
  //digitalWrite

  //
  client.println("HTTP/1.1 200 OK"); 
  client.println("Content-Type: text/html"); 
  client.println(""); // do not forget this one
  client.println("<!DOCTYPE HTML"); 
  client.println("</html>"); 

  client.print("Led pin is now: "); 

  if(value == HIGH) {
    client.print("ON"); 
  } else {
    client.print("Off"); 
  }

  client.println("<br><br>"); 
  client.println("<a href=\"/LED=ON\"\"><button> Turn On </button></a>"); 
  client.println("<a href=\"/LED=OFF\"\"><button>Turn Off </button></a><br />");  
  client.println("</html>");
 
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
  
  

}
