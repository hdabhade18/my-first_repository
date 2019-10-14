#include <ESP8266WiFi.h>
 
const char* ssid     = "AdityaGiradkar";          //enter your wifi name 
const char* password = "Aditya@123";                 // your wifi password
const char* host = "scriabin-searches.000webhostapp.com";  //website url


void setup() {
  Serial.begin(9600);
  delay(500);
  
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  randomSeed(10);
  WiFi.begin(ssid, password); 
  while (WiFi.status() != WL_CONNECTED) {
    delay(400);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi connected, well");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Netmask: ");          // range of total ip addresses that can be used in network 
  Serial.println(WiFi.subnetMask());
  Serial.print("Gateway: ");          // gateway ip is an access point which connected devices uses to
  Serial.println(WiFi.gatewayIP());       // send data to internet or other device connected on that network
}

void loop() {
  
  Serial.print("connecting to "); 
  Serial.println(host);

  WiFiClient client; 
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  int device_id=123;
  String time_stamp="12:32:40";
  int no_sensors=4;
  int s[]={21000,12222,54666,43332,75224};
  
  String url = "/api/upload/insert.php?dev_id="+String(device_id);
  
  for(int i=0;i<4;i++)
    url+="&s"+String(i+1)+"="+String(s[i]);
  url+="&time="+time_stamp+"@";  
  Serial.print("Requesting URL: ");
  Serial.println(url);
  
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");                  //uploading data to cloud
  delay(1000);
  
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  
  Serial.println();
  Serial.println("closing connection");
  delay(2000);
}
